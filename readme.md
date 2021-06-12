## TP4 Tessting de Software en Sistemas Embebidos

El repositorio contiene los archivos necesarios para realizar el Trabajo práctico 4 "Testing unitario". Este trabajo pretende realizar un test unitario con ceedling sobre una biblioteca previamente generada del software para el Trabajo Práctico final de la carrera de especialización 

La biblioteca seleccionada corresponde a la extraccion, acondicionamiento y procesamiento de datos de corriente mediante un ADC del microprocesador. Para ello se desarrollaron funciones que realicen cada una de las acciones necesarias de la biblioteca y las diferentes estucturas de datos para encapsular las varibles en relacion a su funcion.

### Test Casess a implementar

Los casos de prueba deberán verificar las siguientes acciones:

- Test\-1: Despues de la inicializacion del sistema, la cantidad de muestras debe ser 0. 
linea 23: `void test_NmeasureInit(void)` - test\_TP4\-Esteva.c
- Test\-2: Despues de la inicializacion del sistema el estado debe ser Empty.
linea 27: `void test_MeasureStateInit(void)` - test\_TP4\-Esteva.c
- Test\-3: Al iniciar una medicion, el estado debe pasa a Reading.
linea 32: `void test_FirstMeasureState(void)` - test\_TP4\-Esteva.c
- Test\-4: El primer dato extraido se debe almacenar en muestra.data[0].
linea 39: `void test_FirstMeasureData(void)` - test\_TP4\-Esteva.c
- Test\-5: AL finalizar la primera extracion del dato, se debe actualizar la variable nmeasure  (número de medicion).
linea 46: `void test_NMeasureUpdate(void)` - test\_TP4\-Esteva.c
- Test\-6: Se extraen correctamente las NDATA muestras.
linea 53: `void test_NDATAMeasureExtract(void)` - test\_TP4\-Esteva.c
- Test\-7: Una vez que se extraen NDATA muestras, el estado debe pasar a Full.
linea 68: `void test_LastMeasureState(void)` - test\_TP4\-Esteva.c
- Test\-8: Las muestras extraídas se deben convertir a valores de corriente.
linea 77: `void test_ConvertMeasureData(void)` - test\_TP4\-Esteva.c
- Test\-9: Se debe procesar el array de muestras de corriente para extrar el máximo.
linea 91: `void test_MaxOfData(void)` - test\_TP4\-Esteva.c
- Test\-10: Se debe procesar el array de muestras de corriente para extrar el mínimo.
linea 98: `void test_MinOfData(void)` - test\_TP4\-Esteva.c
- Test\-11: Se debe procesar el array de muestras de corriente para extrar el promedio.
linea 104: `void test_AverageOfData(void)` - test\_TP4\-Esteva.c