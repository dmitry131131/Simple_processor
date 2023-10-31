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

struct threadStruct{    
        processorErrorCode error;
        softProcessorUnit processor;
    };

void* thread_function(void* threadData);

int main(int argc, char* argv[])
{   
    #define RETURN(error) do{                                   \
        if (processor_dtor(&(threadStructData.processor)))      \
        {                                                       \
            return DTOR_ERROR;                                  \
        }                                                       \
        return error;                                           \
    }while(0)

    #ifdef USE_GRAPHICS

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Graphics window");

    #endif

    threadStruct threadStructData = {NO_PROCESSOR_ERRORS, {}};

    char* filename = NULL;

    pthread_t processorThread;     // flow ID

    if ((threadStructData.error = filename_getter(argc, argv, &filename)))
    {
        print_processor_error(stderr, threadStructData.error, 0);

        return 0;
    }

    if ((threadStructData.error = prepare(filename, &(threadStructData.processor))))
    {
        print_processor_error(stderr, threadStructData.error, 0);
        
        RETURN(0);
    }

    pthread_create(&processorThread, NULL, thread_function, &threadStructData);

    pthread_join(processorThread, NULL);

    

    #ifdef USE_GRAPHICS

    graphics_draw(&(threadStructData.processor), &window);
    
    #endif

    RETURN(0);
}

#undef RETURN

void* thread_function(void* threadData)
{
    #define RETURN(error) do{                                   \
        if (processor_dtor(&(threadStructData->processor)))     \
        {                                                       \
            return NULL;                                        \
        }                                                       \
    }while(0)

    threadStruct* threadStructData = (threadStruct*) threadData;

    if ((threadStructData->error = processing(&(threadStructData->processor))))
    {
        print_processor_error(stderr, threadStructData->error, threadStructData->processor.IP);
        processor_dump(&(threadStructData->processor), FULL_DUMP);
        
        RETURN(0);
    }

    return NULL;

    #undef RETURN
}
