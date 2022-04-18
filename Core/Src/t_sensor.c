#include "thermocouple.h"

extern I2C_HandleTypeDef hi2c2;

//TMP112AIDRLR - Digital Temperature Sensors
#define D4_ADDR 0x49
#define D5_ADDR 0x48

float temp1_C = 0.0, temp2_C = 0.0;

void init_TMP112(void) 
{
	// Select configuration register(0x01)
	// Continous Conversion mode, 12-Bit Resolution, Fault Queue is 1(0x60)
	// Polarity low, Thermostat in Comparator mode, Disables Shutdown mode(0xA0)
	uint8_t conf[3] = {0};
	conf[0] = 0x01;
	conf[1] = 0x60;
	conf[2] = 0xA0;

	if(HAL_I2C_Master_Transmit(&hi2c2, D4_ADDR << 1, conf, 3, 10) != HAL_OK)
	{
		;	//fault handler
	}
	if(HAL_I2C_Master_Transmit(&hi2c2, D5_ADDR << 1, conf, 3, 10) != HAL_OK)
	{
		;	//fault handler
	}
	HAL_Delay(1);

	conf[0] = 0x00;	//Temperature Register (Read Only)
	HAL_I2C_Master_Transmit(&hi2c2, D4_ADDR << 1, conf, 1, 10);
	HAL_I2C_Master_Transmit(&hi2c2, D5_ADDR << 1, conf, 1, 10);
	HAL_Delay(1);
}

//Read 2 bytes of data from register(0x00)
void read_TMP112(void) 
{
	uint8_t data[2] = {0};
	//D4
	if(HAL_I2C_Master_Receive(&hi2c2, D4_ADDR << 1, data, 2, 10) == HAL_OK)
	{
		// Convert the data to 12-bits
		int16_t temp = ((data[0] << 8) | data[1]) >> 4;
		if(temp > 2047)
		{
			temp -= 4096;
		}
		temp1_C = temp * 0.0625;
		//float fTemp = (cTemp * 1.8) + 32;	//Temperature in Fahrenheit
	}
	else
	{
		//printf("Error : Input/Output error \n");
	}

	//D5
	if(HAL_I2C_Master_Receive(&hi2c2, D5_ADDR << 1, data, 2, 10) == HAL_OK)
	{
		// Convert the data to 12-bits
		int16_t temp = ((data[0] << 8) | data[1]) >> 4;
		if(temp > 2047)
		{
			temp -= 4096;
		}
		temp2_C = temp * 0.0625;
	}
	else
	{
		//printf("Error : Input/Output error \n");
	}
	HAL_Delay(2);
}