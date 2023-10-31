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
};

struct GPUThreadStruct{
    softProcessorUnit* processorPtr;
    sf::RenderWindow*  windowPtr;
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

    processorThreadStruct processorThreadStructData = {NO_PROCESSOR_ERRORS, {}};

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
    if (processorThreadStructData.error)
    {
        return 0;
    }
    
    #ifdef USE_GRAPHICS
    pthread_join(GPUThread, NULL);
    #endif

    RETURN(0);
}

#undef RETURN

void* processor_thread_function(void* threadData)
{
    #define RETURN do{                                                      \
        if (processor_dtor(&(threadStructData->processor)))                 \
        {                                                                   \
            threadStructData->error = DTOR_ERROR;                           \
            return NULL;                                                    \
        }                                                                   \
    }while(0)

    processorThreadStruct* threadStructData = (processorThreadStruct*) threadData;

    if ((threadStructData->error = processing(&(threadStructData->processor))))
    {
        print_processor_error(stderr, threadStructData->error, threadStructData->processor.IP);
        processor_dump(&(threadStructData->processor), FULL_DUMP);
        
        RETURN;
    }

    return NULL;
    #undef RETURN
}

void* GPU_thread_function(void* threadData)
{
    processorThreadStruct* threadStructData = (processorThreadStruct*) threadData;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Graphics window");

    graphics_draw(&(threadStructData->processor), &window);

    return NULL;
}
