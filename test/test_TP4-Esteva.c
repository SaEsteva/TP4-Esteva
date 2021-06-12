#include "unity.h"
#include "TP4-Esteva.h"

#define MAX_VALUE_TEST  (ADC_LECTURE_TEST * CURRENTSCALE)
#define MIN_VALUE_TEST  (ADC_LECTURE_TEST * CURRENTSCALE)
#define AVG_VALUE_TEST  (ADC_LECTURE_TEST * CURRENTSCALE)

extern sensor_data_t muestra;
extern current_data_t corriente;
sensor_data_t muestra_test;
current_data_t corriente_test;

void setUp(void){
    muestra_test.nmeasure = 0;
    measurementInit();
    muestra_test.state = Empty;
}

void tearDown(void){
}

// Despues de la inicializacion del sistema la cantidad e muestras debe ser 0
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
    extract_measurement(&muestra);
    TEST_ASSERT_EQUAL_INT(muestra_test.state, muestra.state); //compruebo que el estado es leyendo
}

// El primer dato extraido se debe almacenar en muestra.data[0]
void test_FirstMeasureData(void){
    muestra_test.data[0] = ADC_LECTURE_TEST;
    extract_measurement(&muestra);
    TEST_ASSERT_EQUAL_INT(muestra_test.data[0], muestra.data[0]); //compruebo que el primer dato leído sea correcto
}

// AL finalizar la primera extracion del dato, se debe actualizar la variable nmeasure (número de medicion)
void test_NMeasureUpdate(void){
    muestra_test.nmeasure = 1;
    extract_measurement(&muestra);
    TEST_ASSERT_EQUAL_INT(muestra_test.nmeasure, muestra.nmeasure); //compruebo que aumenta el número de muestras
}

// Se extraen correctamente las NDATA muestras
void test_NDATAMeasureExtract(void){
    int i; // indice para recorrer los for
    // Se generan las NDAta muestras del test
    for (i = 0; i < NDATA; i++){
        muestra_test.data[i] = ADC_LECTURE_TEST;
    }
    muestra.nmeasure = 0; // se inicializa el indez de muestras
    // Se extraen las NDATA muestras
    for (i = 0; i < NDATA; i++){
        extract_measurement(&muestra);
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(muestra_test.data, muestra.data,NDATA); //comparo los array de NDATA muestras
}

// Una vez que se extraen NDATA muestras, el estado debe pasar a Full
void test_LastMeasureState(void){
    muestra_test.nmeasure = NDATA;
    muestra_test.state = Full;
    muestra.nmeasure = NDATA - 1;
    extract_measurement(&muestra);
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