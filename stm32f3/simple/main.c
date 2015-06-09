#include <stdio.h>
#include "common.h"


volatile unsigned long _ticks = 0;

void SysTick_Handler(void)
{
    _ticks++;
}

int main(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
   
  GPIO_WriteBit(GPIOE, GPIO_Pin_All, Bit_SET);

  SysTick_Config(SystemCoreClock / 1000);
  
  int state = 1;
  
  /* Infinite loop */
  while (1)
  {
    if(_ticks >= 500)
    {
      GPIO_WriteBit(GPIOE, GPIO_Pin_All, state ? Bit_SET  : Bit_RESET);
      _ticks = 0;
      state = !state;
      
      
    }
  }
}
