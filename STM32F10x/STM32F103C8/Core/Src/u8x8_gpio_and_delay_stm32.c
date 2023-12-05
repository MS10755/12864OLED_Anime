#include "u8x8.h"
#include "main.h"

#ifdef U8X8_USE_PINS
uint8_t u8x8_gpio_and_delay_stm32(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, U8X8_UNUSED void *arg_ptr)
{
  // uint8_t i;
  switch(msg)
  {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:
      break;

#ifndef __AVR__	
    /* this case is not compiled for any AVR, because AVR uC are so slow */
    /* that this delay does not matter */
    case U8X8_MSG_DELAY_NANO:
//			if(arg_int!=0){
//				HAL_Delay(1);
//			}
      break;
#endif
    
    case U8X8_MSG_DELAY_10MICRO:
      /* not used at the moment */
      break;
    
    case U8X8_MSG_DELAY_100NANO:
      /* not used at the moment */
      break;
   
    case U8X8_MSG_DELAY_MILLI:
    HAL_Delay(arg_int);
      break;
    case U8X8_MSG_DELAY_I2C:
      /* arg_int is 1 or 4: 100KHz (5us) or 400KHz (1.25us) */
//      HAL_Delay(1);
      break;
    case U8X8_MSG_GPIO_I2C_CLOCK:
    case U8X8_MSG_GPIO_I2C_DATA:
      break;
		case U8X8_MSG_GPIO_CS:
      HAL_GPIO_WritePin(OLED_CS_GPIO_Port,OLED_CS_Pin,(GPIO_PinState)arg_int);
			break;
		case U8X8_MSG_GPIO_DC:
      HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,(GPIO_PinState)arg_int);
			break;
		case U8X8_MSG_GPIO_RESET:
      HAL_GPIO_WritePin(OLED_RST_GPIO_Port,OLED_RST_Pin,(GPIO_PinState)arg_int);
			break;
    default:
	break;
      return 0;
  }
  return 1;
}
#endif // U8X8_USE_PINS