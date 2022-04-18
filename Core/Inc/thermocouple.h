#ifndef __THERMOCOUPLE_H
#define __THERMOCOUPLE_H
#include "main.h"

void MAX31856_read(void);
void MAX31856_config(void);

void init_TMP112(void); 
void read_TMP112(void); 

void send_data(void);

//MAX31856MUD	Precision Thermocouple to Digital Converter with Linearization

#define CR0_AUTOCONVERT 0x80 		///< Conversion Mode, 1 = Auto convert flag, 0 = Normally Off mode (default)
#define CR0_1SHOT 			0x40    ///< One-Shot Mode, 0 = No conversions requested (default)
#define CR0_OCFAULT1 		0x20    ///< open circuit fault 1 flag
#define CR0_OCFAULT0 		0x10    ///< open circuit fault 0 flag
#define CR0_CJ 					0x08    ///< Cold-Junction Sensor Disable, 0 = Cold-junction temperature sensor enabled (default)
#define CR0_FAULT 			0x04    ///< Fault Mode, 1 = Interrupt Mode, 0 = Comparator Mode.(default)
#define CR0_FAULTCLR 		0x02    ///< Fault Status Clear, 0 = Default
#define NOISE_FILTER		0x01    ///< 50Hz/60Hz Noise Rejection Filter Selection, 0 = 60Hz and its harmonics(default),	1 = 50Hz

//Register 01h/81h: Configuration 1 Register (CR1)
#define CR1_AVG_1_SAMP  0x00
#define CR1_AVG_2_SAMP  0x10
#define CR1_AVG_4_SAMP  0x20
#define CR1_AVG_8_SAMP  0x30
#define CR1_AVG_16_SAMP 0x40
#define CR1_TYPE_B      0x00
#define CR1_TYPE_E      0x01
#define CR1_TYPE_J      0x02
#define CR1_TYPE_K      0x03
#define CR1_TYPE_N      0x04
#define CR1_TYPE_R      0x05
#define CR1_TYPE_S      0x06
#define CR1_TYPE_T      0x07
#define CR1_GAIN_8  	  0x08
#define CR1_GAIN_32 	  0x0C


// Register 0x02: MASK
#define MASK_CJ_HIGH_FAULT	0x20
#define MASK_CJ_LOW_FAULT 	0x10
#define MASK_TC_HIGH_FAULT 	0x08
#define MASK_TC_LOW_FAULT  	0x04
#define MASK_OV_UV_FAULT		0x02
#define MASK_TC_OPEN_FAULT 	0x01

//Register Memory Map
#define CR0_REG 	 0x00   ///< Config 0 register
#define CR1_REG 	 0x01  	///< Config 1 register
#define MASK_REG 	 0x02 	///< Fault Mask register
#define CJHF_REG 	 0x03 	///< Cold junction High temp fault register, 1 degC/bit
#define CJLF_REG 	 0x04 	///< Cold junction Low temp fault register, 1 degC/bit
#define LTHFTH_REG 0x05 	///< Linearized Temperature High Fault Threshold Register, MSB, 0.0625 degC/bit
#define LTHFTL_REG 0x06 	///< Linearized Temperature High Fault Threshold Register, LSB
#define LTLFTH_REG 0x07 	///< Linearized Temperature Low Fault Threshold Register, MSB, 0.0625 degC/bit
#define LTLFTL_REG 0x08 	///< Linearized Temperature Low Fault Threshold Register, LSB
#define CJTO_REG 	 0x09  	///< Cold-Junction Temperature Offset Register, 0.0625 degC/bit
#define CJTH_REG 	 0x0A  	///< Cold-Junction Temperature Register, MSB, 0.015625 deg C/bit (2^-6)
#define CJTL_REG 	 0x0B  	///< Cold-Junction Temperature Register, LSB
#define LTCBH_REG  0x0C 	///< Linearized TC Temperature, Byte 2, 0.0078125 decC/bit
#define LTCBM_REG  0x0D 	///< Linearized TC Temperature, Byte 1
#define LTCBL_REG  0x0E 	///< Linearized TC Temperature, Byte 0
#define SR_REG 		 0x0F   ///< Fault Status Register

//Register 0Fh: Fault Status Register (SR)
#define SR_FAULT_CJRANGE 	0x80	///< Fault status Cold Junction Out-of-Range flag
#define SR_FAULT_TCRANGE 	0x40	///< Fault status Thermocouple Out-of-Range flag
#define SR_FAULT_CJHIGH  	0x20	///< Fault status Cold-Junction High Fault flag
#define SR_FAULT_CJLOW   	0x10	///< Fault status Cold-Junction Low Fault flag
#define SR_FAULT_TCHIGH  	0x08	///< Fault status Thermocouple Temperature High Fault flag
#define SR_FAULT_TCLOW   	0x04	///< Fault status Thermocouple Temperature Low Fault flag
#define SR_FAULT_OVUV    	0x02	///< Fault status Overvoltage or Undervoltage Input Fault flag
#define SR_FAULT_OPEN    	0x01	///< Fault status Thermocouple Open-Circuit Fault flag

// Errors
#define	FAULT_OPEN                              10000   // No thermocouple
#define	FAULT_VOLTAGE                           10001   // Under/over voltage error.  Wrong thermocouple type?
#define NO_MAX31856                             10002   // MAX31856 not communicating or not connected
#define IS_MAX31856_ERROR(x)                    (x == FAULT_OPEN && x <= NO_MAX31856)

#define CELSIUS                                 0
#define FAHRENHEIT                              1


/*#define CR0_INIT  (CR0_AUTOMATIC_CONVERSION + CR0_OPEN_CIRCUIT_FAULT_TYPE_K + CR0_NOISE_FILTER_50HZ)
#define CR1_INIT  (CR1_AVERAGE_2_SAMPLES + CR1_THERMOCOUPLE_TYPE_K)
#define MASK_INIT (~(MASK_VOLTAGE_UNDER_OVER_FAULT + MASK_THERMOCOUPLE_OPEN_FAULT))
*/
#endif /* __THERMOCOUPLE_H */