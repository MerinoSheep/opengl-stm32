#include "stm32f4xx_hal.h"

#define DMA_TIMEOUT 10

int dma2dDrawHorizLine(uint32_t color, uint32_t LayerIndex, uint32_t x, uint32_t y, uint32_t length, uint32_t width);