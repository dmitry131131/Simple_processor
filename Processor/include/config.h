/**
 * @file 
 * @brief Processor constsnts
*/
#ifndef CONFIG_H
#define CONFIG_H

const int VERSION = 2;

const size_t RAM_SIZE       = 100;
const size_t VRAM_SIZE      = 2601;

const unsigned int PIXEL_SIZE = 15;
const unsigned int WINDOW_SIZE = 51*PIXEL_SIZE;

const int DOUBLE_COEF  = 10000;
const size_t STACK_SIZE     = 10;
const size_t RET_STACK_SIZE = 10;

#endif