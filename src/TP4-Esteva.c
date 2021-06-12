/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2021/04/14
 * Version: 1.1
 *===========================================================================*/


/*==================[inclusions]=============================================*/
#include "TP4-Esteva.h"

sensor_data_t muestra;
current_data_t corriente;

void measurementInit(){
	muestra.nmeasure=0;
	muestra.state=Empty;
}

void get_data (sensor_data_t* lectura){
	lectura->data[lectura->nmeasure] = ADC_LECTURE_TEST;//adcRead( SENSOR_ID );
}

void extract_measurement(sensor_data_t* data){

	if (data->nmeasure == 0)
		data->state = Reading;

	//Extae el dato 
	get_data (data);
	data->nmeasure++;
	
	if (data->nmeasure >= NDATA){// actualiza el estado del buffer cuando tiene las N muestras
		data->state = Full;
	}
}

void convert_measurement(sensor_data_t* measurements, current_data_t * current){
	int i;

	measurements->state = Processing;

	for (i = 0; i < NDATA; i++){
		current->current_value[i] = measurements->data[i] * CURRENTSCALE;
	}
}

void process_measurement(current_data_t * current){
	int i;
	double aux_avg = 0;
	double aux_max = 0;
	double aux_min = 0;

	aux_min = current->current_value[0];
	for (i = 0; i < NDATA; i++){
		aux_avg += current->current_value[i];
		if (aux_max < current->current_value[i])// busca el máximo
			aux_max = current->current_value[i];
		if (aux_min > current->current_value[i])// busca el minimo
			aux_min = current->current_value[i];
	}
	aux_avg = aux_avg/NDATA;
	current->average = aux_avg;
	current->max_value = aux_max;
	current->min_value = aux_min;
}
