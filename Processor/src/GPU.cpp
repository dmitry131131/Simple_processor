/**
 * @file
 * @brief GPU sources
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <SFML/Graphics.hpp>

#include "Error.h"
#include "Stack.h"
#include "InputOutput.h"
#include "Processing.h"
#include "ProcessorUtils.h"
#include "GPU.h"

processorErrorCode graphics_draw(const softProcessorUnit* processor, sf::RenderWindow* window)
{
    assert(processor);

    sf::RectangleShape shape(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
    shape.setFillColor(sf::Color::Green);

    size_t rowSize = (size_t) sqrt(VRAM_SIZE);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();

        size_t row = 0;
        for (size_t i = 0; i < VRAM_SIZE; i++)
        {
            if (processor->RAM[VRAM_ADRESS + i] == 1 * DOUBLE_COEF)
            {
                window->draw(shape);
            }
            else 
            {
                
            }
            if ((i + 1) % rowSize == 0)
            {
                row++;
            }

        shape.setPosition((float) (PIXEL_SIZE * (i % rowSize)), (float) (PIXEL_SIZE*row));
        }

        window->display();
    }

    return NO_PROCESSOR_ERRORS;
}