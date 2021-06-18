/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2021/04/14
 * Version: 1.1
 *===========================================================================*/


/*==================[inclusions]=============================================*/
#include "TP4-Esteva.h"

sensor_data_t muestra;			// Variable global de biblioteca con los datos de las muestras
current_data_t corriente;		// Variable global de biblioteca con los datos de las muestras en corriente

/**
 * @brief Inicializa la variable global de medicion
 * @param void: no recibe parámetros
 * @return La función no tiene valores de retorno
 */ 
void measurementInit(){
	muestra.nmeasure=0;
	muestra.state=Empty;
}

/**
 * @brief Guarda en la estructura el dato extraido de la biblioteca externa del ADC
 * @param lectura: puntero del tipo sensor_data_t con los datos de la extructura a guardar el dato 
 * @return La función no tiene valores de retorno
 */ 
void get_data (sensor_data_t* lectura){
	lectura->data[lectura->nmeasure] = adcLecture( SENSOR_ID );
}

/**
 * @brief Realiza la extraccion de la medicion N (hasta NDATA) y actualizar el flag de estado de la estructura
 * @param data: puntero del tipo sensor_data_t con los datos de la extructura a guardar los datos extraidos 
 * @return La función no tiene valores de retorno
 */ 
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

/**
 * @brief Realiza la conversion de los datos extraidos al ADC a valores de corriente
 * @param measurements: puntero del tipo sensor_data_t con los datos de la extructura a convertir en valores de corriente 
 * @param current: puntero del tipo current_data_t con los datos de la extructura donde se guardan las mediciones convertidos a corriente
 * @return La función no tiene valores de retorno
 */ 
void convert_measurement(sensor_data_t* measurements, current_data_t * current){
	int i;

	measurements->state = Processing;

	for (i = 0; i < NDATA; i++){
		current->current_value[i] = measurements->data[i] * CURRENTSCALE;
	}
}

/**
 * @brief Procesa los datos de corriente para adquirir el valor maximo, minimo y el promedio
 * @param current: puntero del tipo current_data_t con los datos de corriente a procesar
 * @return La función no tiene valores de retorno
 */ 
void process_measurement(current_data_t * current){
	int i;
	int aux_avg = 0;
	int aux_max = 0;
	int aux_min = 0;

	aux_min = current->current_value[0];
	for (i = 0; i < NDATA; i++){
		aux_avg = aux_avg + current->current_value[i];
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
