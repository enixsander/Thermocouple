#include "thermocouple.h"
//MAX31856MUD	Precision Thermocouple to Digital Converter with Linearization

extern SPI_HandleTypeDef hspi2;

uint8_t data[10] = {0};
uint8_t fault_status = 0;
float internal = 0.0, external = 0.0;

void MAX31856_config()
{
	//read default config
	HAL_Delay(5); //1-2 ms to init MAX31856
	data[0] = CR0_REG | 0x00;
	SPI2_NSS_GPIO_Port->BRR = (uint32_t)SPI2_NSS_Pin;
	HAL_SPI_Receive(&hspi2, data, 10, 50);
	SPI2_NSS_GPIO_Port->BSRR = (uint32_t)SPI2_NSS_Pin;
	//data[0] = 0xFF - в нулевом байте передаеся регистр, в первом и далее идут данные
	//0x00 0x03 0xFF 0x7F 0xC0 0x7F 0xFF 0x80 0x00 --- FACTORY CONFIG DEFAULT
	

	data[0] = CR0_REG | 0x80;	//0x80 - WRITE
	data[1] = CR0_AUTOCONVERT | NOISE_FILTER;
	SPI2_NSS_GPIO_Port->BRR = (uint32_t)SPI2_NSS_Pin;	//CS LOW
	HAL_SPI_Transmit(&hspi2, data, 2, 20);
	SPI2_NSS_GPIO_Port->BSRR = (uint32_t)SPI2_NSS_Pin;

/*	
	//check config
	data[0] = CR0_REG | 0x00;
	SPI2_NSS_GPIO_Port->BRR = (uint32_t)SPI2_NSS_Pin;
	HAL_SPI_Receive(&hspi2, data, 10, 50);
	SPI2_NSS_GPIO_Port->BSRR = (uint32_t)SPI2_NSS_Pin;
*/
}

void MAX31856_read()
{
	int16_t cj = 0;	//Cold-Junction
	int32_t ltc = 0;	//Linearized TC

	data[0] = CJTH_REG | 0x00;	//0x00 - READ
	SPI2_NSS_GPIO_Port->BRR = (uint32_t)SPI2_NSS_Pin;
	HAL_SPI_Receive(&hspi2, data, 7, 20);
	SPI2_NSS_GPIO_Port->BSRR = (uint32_t)SPI2_NSS_Pin;

	//Cold-Junction Temperature, ////////////////////////
	cj = ((int16_t)data[1] << 8) | data[2];	
	cj >>= 2;	//2 младших бита пустые
	if(cj >= (1U << 13))	//13 bit --- sign
		cj -= (1UL << 14);
  internal = cj * 0.015625; //0.015625 deg C/bit (2^-6)
  /////////////////////////////////////////////////////

  //Linearized TC Temperature, Byte 0 - 2, //////////////////////////
  ltc = ((int32_t)data[3] << 16) | ((int32_t)data[4] << 8) | data[5];
  ltc >>= 5;
  if(ltc >= (1UL << 18))
  	ltc -= (1UL << 19);
  external = ltc * 0.0078125;	//0.0078125 decC/bit
  ///////////////////////////////////////////////////////////////////

  fault_status = data[6];	//Fault Status Register
}
