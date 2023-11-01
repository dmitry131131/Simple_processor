#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <SFML/Graphics.hpp>

#include "Error.h"
#include "Stack.h"
#include "Processing.h"
#include "Read.h"
#include "ProcessorUtils.h"
#include "GPU.h"

struct processorThreadStruct{    
    processorErrorCode error;
    softProcessorUnit processor;
    bool GPU_call;
};

void* processor_thread_function(void* threadData);
void* GPU_thread_function(void* threadData);

int main(int argc, char* argv[])
{   
    #define RETURN(error) do{                                               \
        if (processor_dtor(&(processorThreadStructData.processor)))         \
        {                                                                   \
            return DTOR_ERROR;                                              \
        }                                                                   \
        return error;                                                       \
    }while(0)

    processorThreadStruct processorThreadStructData = {NO_PROCESSOR_ERRORS, {}, 0};

    char* filename = NULL;

    pthread_t processorThread;     // Processor 
    pthread_t GPUThread;           // GPU

    if ((processorThreadStructData.error = filename_getter(argc, argv, &filename)))
    {
        print_processor_error(stderr, processorThreadStructData.error, 0);

        return 0;
    }

    if ((processorThreadStructData.error = prepare(filename, &(processorThreadStructData.processor))))
    {
        print_processor_error(stderr, processorThreadStructData.error, 0);
        
        RETURN(0);
    }

    pthread_create(&processorThread, NULL, processor_thread_function, &processorThreadStructData);
    #ifdef USE_GRAPHICS
    pthread_create(&GPUThread,       NULL, GPU_thread_function,       &processorThreadStructData);
    #endif

    pthread_join(processorThread, NULL);

    processorThreadStructData.GPU_call = 1;   // close GPU thread
    
    #ifdef USE_GRAPHICS
    pthread_join(GPUThread, NULL);
    #endif

    if (processorThreadStructData.error)
    {
        RETURN(0);
    }

    RETURN(0);
}

#undef RETURN

void* processor_thread_function(void* threadData)
{
    processorThreadStruct* threadStructData = (processorThreadStruct*) threadData;

    if ((threadStructData->error = processing(&(threadStructData->processor))))
    {
        print_processor_error(stderr, threadStructData->error, threadStructData->processor.IP);
        processor_dump(&(threadStructData->processor), FULL_DUMP);
        
        return NULL;
    }

    return NULL;
}

void* GPU_thread_function(void* threadData)
{
    processorThreadStruct* threadStructData = (processorThreadStruct*) threadData;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Graphics window");

    while (window.isOpen())
    {
        if (threadStructData->error || threadStructData->GPU_call)
        {
            threadStructData->GPU_call = 0;
            window.close();
            return NULL;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        graphics_draw(&(threadStructData->processor), &window);

        window.display();
    }
    return NULL;
}
