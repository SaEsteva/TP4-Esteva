/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2021/04/14
 * Version: 1.1
 *===========================================================================*/


/*==================[inclusions]=============================================*/


/*==================[macros]=================================================*/
#define SENSOR_ID		CH1 // adc input
#define NDATA			10
#define SAMPLETIME		1 //ms
#define SENSORSCALE		50 //50 A sensor scale
#define ADCFULLSCALE	1024 // full scale ADC value
#define CURRENTSCALE	SENSORSCALE/ADCFULLSCALE
#define FLAGDATA		1

enum sensor_state{ Empty ,Reading , Full ,Processing ,DataProcessed , Error , Sending};


#define ADC_LECTURE_TEST    40
/*==================[typedef]================================================*/

typedef struct{
	int data[NDATA];
	int nmeasure;
	int state;
}sensor_data_t;


typedef struct{
	float current_value[NDATA];
	float average;
	float max_value;
	float min_value;
}current_data_t;

/*==================[external functions declaration]=========================*/

void SensorInit();
void measurementInit();
void get_data (sensor_data_t* );
void extract_measurement(sensor_data_t* );
void convert_measurement(sensor_data_t* , current_data_t * );
void process_measurement(current_data_t * );