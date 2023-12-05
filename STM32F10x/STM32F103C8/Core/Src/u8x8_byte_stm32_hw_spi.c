#include "spi.h"
#include "u8x8.h"
#include <stdio.h>

#define U8X8_HAVE_HW_SPI

#ifdef U8X8_USE_PINS


void spi_transmit(uint8_t * buf,uint16_t len){
	HAL_StatusTypeDef ret = HAL_OK;
	if(len){
		ret = HAL_SPI_Transmit(&hspi1,buf,len,200);
	}
	if(ret != HAL_OK){
		printf("spi_transmit hal_error:%d\r\n",ret);
	}
	while(HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX);
	if(ret != HAL_OK){
		printf("spi_transmit failed %d !\r\n",ret);
	}
}

uint8_t u8x8_byte_stm32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
#ifdef U8X8_HAVE_HW_SPI
	
  // uint8_t *data;
  // uint8_t internal_spi_mode;
 
  switch(msg)
  {
    case U8X8_MSG_BYTE_SEND:
      // 1.6.5 offers a block transfer, but the problem is, that the
      // buffer is overwritten with the incoming data
      // so it can not be used...
      // SPI.transfer((uint8_t *)arg_ptr, arg_int);
//			SPI_Transmit((uint8_t *)arg_ptr,arg_int);
			spi_transmit((uint8_t *)arg_ptr,arg_int);

      break;
    case U8X8_MSG_BYTE_INIT:
      if ( u8x8->bus_clock == 0 ) 	/* issue 769 */
	    u8x8->bus_clock = u8x8->display_info->sck_clock_hz;
      /* disable chipselect */
      u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
      
      /* no wait required here */
//			SPI_Init();
			
      break;
      
    case U8X8_MSG_BYTE_SET_DC:
      u8x8_gpio_SetDC(u8x8, arg_int);
      break;
      
    case U8X8_MSG_BYTE_START_TRANSFER:
      u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);  
      u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->post_chip_enable_wait_ns, NULL);
      break;
      
    case U8X8_MSG_BYTE_END_TRANSFER:      
      u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->pre_chip_disable_wait_ns, NULL);
      u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
      break;
    default:
      return 0;
  }
#endif	/* U8X8_HAVE_HW_SPI */
  return 1;
}

#endif
