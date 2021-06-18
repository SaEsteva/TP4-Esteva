#include "unity.h"
#include "TP4-Esteva.h"
#include "ADC.h"
#include "mock_ADC.h"

int ADC_LECTURE_TEST = 40;

int ADC_DATA[NDATA] = {6,1,3,4,5,6,3,8,9,15};

// Valores extraidos con la funcion de python Calculos.py (redondeados)
#define MAX_VALUE_TEST  29
#define MIN_VALUE_TEST  1
#define AVG_VALUE_TEST  11

extern sensor_data_t muestra;
extern current_data_t corriente;
sensor_data_t muestra_test;
current_data_t corriente_test;

void setUp(void){
    muestra_test.nmeasure = 0;
    measurementInit();
    muestra_test.state = Empty;
}

// Despues de la inicializacion del sistema la cantidad de muestras debe ser 0
void test_NmeasureInit(void){
    TEST_ASSERT_EQUAL_INT(muestra_test.nmeasure, muestra.nmeasure); // compruebo la cantidad de muestras es cero
}
// Despues de la inicializacion del sistema el estado debe ser Empty
void test_MeasureStateInit(void){
    TEST_ASSERT_EQUAL_INT(muestra_test.state, muestra.state); //compruebo que el estado es vacio
}

// Al iniciar una medicion, el estado debe pasa a Reading
void test_FirstMeasureState(void){
    muestra_test.state = Reading;
    adcLecture_ExpectAndReturn(SENSOR_ID,ADC_DATA[0]*ADC_LECTURE_TEST);
    extract_measurement(&muestra);
    TEST_ASSERT_EQUAL_INT(muestra_test.state, muestra.state); //compruebo que el estado es leyendo
}

// El primer dato extraido se debe almacenar en muestra.data[0]
void test_FirstMeasureData(void){
    adcLecture_ExpectAndReturn(SENSOR_ID,ADC_DATA[2]*ADC_LECTURE_TEST);
    muestra_test.data[0] = ADC_DATA[2]*ADC_LECTURE_TEST;
    extract_measurement(&muestra);
    TEST_ASSERT_EQUAL_INT(muestra_test.data[0], muestra.data[0]); //compruebo que el primer dato leído sea correcto
}

// AL finalizar la primera extracion del dato, se debe actualizar la variable nmeasure (número de medicion)
void test_NMeasureUpdate(void){
    muestra_test.nmeasure = 1;
    adcLecture_ExpectAndReturn(SENSOR_ID,ADC_DATA[1]);
    extract_measurement(&muestra);
    TEST_ASSERT_EQUAL_INT(muestra_test.nmeasure, muestra.nmeasure); //compruebo que aumenta el número de muestras
}

// Se extraen correctamente las NDATA muestras
void test_NDATAMeasureExtract(void){
    int i; // indice para recorrer los for
    // Se generan las NDAta muestras del test
    for (i = 0; i < NDATA; i++){
        muestra_test.data[i] = ADC_DATA[i]*ADC_LECTURE_TEST;
    }
    muestra_test.nmeasure = NDATA;
    muestra_test.state = Full;
    muestra.nmeasure = 0; // se inicializa el index de muestras
    // Se extraen las NDATA muestras
    for (i = 0; i < NDATA; i++){
        adcLecture_ExpectAndReturn(SENSOR_ID,ADC_DATA[i]*ADC_LECTURE_TEST);
        extract_measurement(&muestra);
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(muestra_test.data, muestra.data,NDATA); //comparo los array de NDATA muestras
}

// Una vez que se extraen NDATA muestras, el estado debe pasar a Full
void test_LastMeasureState(void){
    TEST_ASSERT_EQUAL_INT(muestra_test.state, muestra.state); //compruebo que el estado sea Full
}

// Las muestras extraídas se deben convertir a valores de corriente
void test_ConvertMeasureData(void){
    int i; // indice para recorrer los for
    // Se generan las NDATA muestas de corriente_test
    for (i = 0; i < NDATA; i++){
        corriente_test.current_value[i] = muestra_test.data[i] * CURRENTSCALE;
    }
    // Se extraen las NDATA muestras
    for (i = 0; i < NDATA; i++){
        convert_measurement(&muestra,&corriente);
    }   
    TEST_ASSERT_EQUAL_INT_ARRAY(corriente_test.current_value, corriente.current_value,NDATA); //comparo los array de corriente 
}

// Se debe procesar el array de muestras de corriente para extrar el máximo
void test_MaxOfData(void){
    corriente_test.max_value = MAX_VALUE_TEST;
    process_measurement(&corriente);
    TEST_ASSERT_EQUAL_INT(corriente_test.max_value, corriente.max_value); //Verifico el valor del maximo
}

// Se debe procesar el array de muestras de corriente para extrar el mínimo
void test_MinOfData(void){
    corriente_test.min_value = MIN_VALUE_TEST;
    TEST_ASSERT_EQUAL_INT(corriente_test.min_value, corriente.min_value); //Verifico el valor del minimo
}

// Se debe procesar el array de muestras de corriente para extrar el promedio
void test_AverageOfData(void){
    corriente_test.average = AVG_VALUE_TEST;
    TEST_ASSERT_EQUAL_INT(corriente_test.average, corriente.average); //Verifico el valor del promedio
}