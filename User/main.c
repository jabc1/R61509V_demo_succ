/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"   
#include "tft.h"
#include "lcd.h"
int main(void)
{
	HAL_Init();
	SystemClock_Config();
	GPIO_init();
	//LCD_Init();
	TFT_GPIO();
	TFT_Init();
	while (1)
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,(GPIO_PinState)!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1));
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,(GPIO_PinState)!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5));
		HAL_Delay(1000);
	}
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
