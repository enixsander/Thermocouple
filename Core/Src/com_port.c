#include "thermocouple.h"
#include "usbd_cdc_if.h"

extern float internal, external;
extern float temp1_C, temp2_C;

#define SEND_DELAY 500

__IO uint16_t timer_send = SEND_DELAY;

void send_data(void) 
{
	if(timer_send)
		return;

	timer_send = SEND_DELAY;	//500ms

	char str_int[20], str_ext[20], str_temp1[20], str_temp2[20];
	sprintf (str_int,   "%.6f ",    internal);
	sprintf (str_ext,   "%.6f   ",  external);
	sprintf (str_temp1, "%.4f ",    temp1_C);
	sprintf (str_temp2, "%.4f\r\n", temp2_C);

  CDC_Transmit_FS((uint8_t*)str_int,   strlen(str_int));
  HAL_Delay(1);
  CDC_Transmit_FS((uint8_t*)str_ext,   strlen(str_ext));
  HAL_Delay(1);
  CDC_Transmit_FS((uint8_t*)str_temp1, strlen(str_temp1));
  HAL_Delay(1);
  CDC_Transmit_FS((uint8_t*)str_temp2, strlen(str_temp2));
}
