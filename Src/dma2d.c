#include "dma2d.h"

static DMA2D_HandleTypeDef hdma2d;

/*

In the perspective of the screen param length would be the width of the screen while the width of the line would be height of the screen.
*/
int dma2dDrawHorizLine(uint32_t color, uint32_t LayerIndex, uint32_t x, uint32_t y, uint32_t length, uint32_t width)
{
    hdma2d.Instance = DMA2D;
    hdma2d.Init.Mode         = DMA2D_R2M;
    hdma2d.Init.ColorMode    = DMA2D_ARGB8888;
    hdma2d.Init.OutputOffset = 0;
    hdma2d.LayerCfg[LayerIndex].InputOffset = 0;


  /* DMA2D Initialization */
  if (HAL_DMA2D_Init(&hdma2d) == HAL_OK)
  {
    if (HAL_DMA2D_ConfigLayer(&hdma2d, LayerIndex) == HAL_OK)
    {
        x = 239 - x;
        uint32_t offset = 0xD0000000 + (y * 240 + x) * 4;
      if (HAL_DMA2D_Start(&hdma2d, color, offset, length, width) == HAL_OK)
      {
        HAL_DMA2D_PollForTransfer(&hdma2d, DMA_TIMEOUT);
      }
    }
  }
  return 0;
}
