## TP4 Tessting de Software en Sistemas Embebidos

El repositorio contiene los archivos necesarios para realizar el Trabajo práctico 4 "Testing unitario". Este trabajo pretende realizar un test unitario con ceedling sobre una biblioteca previamente generada del software para el Trabajo Práctico final de la carrera de especialización 

La biblioteca seleccionada corresponde a la extraccion, acondicionamiento y procesamiento de datos de corriente mediante un ADC del microprocesador. Para ello se desarrollaron funciones que realicen cada una de las acciones necesarias de la biblioteca y las diferentes estucturas de datos para encapsular las varibles en relacion a su funcion.

### Test Casess a implementar

Los casos de prueba deberán verificar las siguientes acciones:

- Test\-1: Despues de la inicializacion del sistema, la cantidad de muestras debe ser 0. 
linea 27: `void test_NmeasureInit(void)` - test\_TP4\-Esteva.c
- Test\-2: Despues de la inicializacion del sistema el estado debe ser Empty.
linea 31: `void test_MeasureStateInit(void)` - test\_TP4\-Esteva.c
- Test\-3: Al iniciar una medicion, el estado debe pasa a Reading.
linea 36: `void test_FirstMeasureState(void)` - test\_TP4\-Esteva.c
- Test\-4: El primer dato extraido se debe almacenar en muestra.data[0].
linea 44: `void test_FirstMeasureData(void)` - test\_TP4\-Esteva.c
- Test\-5: AL finalizar la primera extracion del dato, se debe actualizar la variable nmeasure  (número de medicion).
linea 52: `void test_NMeasureUpdate(void)` - test\_TP4\-Esteva.c
- Test\-6: Se extraen correctamente las NDATA muestras.
linea 60: `void test_NDATAMeasureExtract(void)` - test\_TP4\-Esteva.c
- Test\-7: Una vez que se extraen NDATA muestras, el estado debe pasar a Full.
linea 78: `void test_LastMeasureState(void)` - test\_TP4\-Esteva.c
- Test\-8: Las muestras extraídas se deben convertir a valores de corriente.
linea 83: `void test_ConvertMeasureData(void)` - test\_TP4\-Esteva.c
- Test\-9: Se debe procesar el array de muestras de corriente para extrar el máximo.
linea 97: `void test_MaxOfData(void)` - test\_TP4\-Esteva.c
- Test\-10: Se debe procesar el array de muestras de corriente para extrar el mínimo.
linea 104: `void test_MinOfData(void)` - test\_TP4\-Esteva.c
- Test\-11: Se debe procesar el array de muestras de corriente para extrar el promedio.
linea 110: `void test_AverageOfData(void)` - test\_TP4\-Esteva.c

### Descripcion de la biblioteca

La biblioteca se implementa para extraer un array de NDATA muestras de un ADC (otra biblioteca dependiendo la placa utilizada) utilizando la funcion `void extract_measurement(sensor_data_t* data)`. Cuenta con una funcion para acondicionar los datos extraidos a valores de corriente `void convert_measurement(sensor_data_t* , current_data_t * )` y otra para procesar el array de datos de corriente `void process_measurement(current_data_t * )` para extraer el valor máximo, mínimo y promedio del conjunto.

### Consideraciones

Dado que la biblioteca utiliza la funcion `int adcLecture(int adcChanel)` proveniente de la biblioteca del ADC en particular a utilizar, se debe implementar un mock para lograr realziar el test.
Primero se instancia la biblioteca ADC.h con dicha funcion y luego se define el array de datos int ADC_DATA[NDATA] = {6,1,3,4,5,6,3,8,9,15};. Para implementar el mock se realiza el llamado a la funcion adcLecture_ExpectAndReturn(SENSOR_ID,"data to return") por cada vez que el test llamará a la funcion del adc correspondinte. Esto permite indicar el valor que debe devolver la funcion cuando es llamada y luego realizar el test comparando ese valor con lo que devuelve cada funcion de la biblioteca bajo test.

Se agrega un script simple de python que realiza el cálculo de maximo, minimo y promedio para un array de datos requerido. Esto nos permite extraer los nuevos valores a comparar en el test si se modifican los valores de array ADC_DATA