import math

SENSORSCALE =   50.0
ADCFULLSCALE =	1024
CURRENTSCALE =	SENSORSCALE/ADCFULLSCALE
print("Los valores son : " + str(CURRENTSCALE) + "\n")
ADC_LECTURE_TEST = 40
VALUE = ADC_LECTURE_TEST*CURRENTSCALE
print("Los valores son : " + str(VALUE) + "\n")
ADC_DATA = (6*VALUE,1*VALUE,3*VALUE,4*VALUE,5*VALUE,6*VALUE,3*VALUE,8*VALUE,9*VALUE,15*VALUE)

print("Los valores son : " + str(ADC_DATA) + "\n")

num_max = max(ADC_DATA)
num_min = min(ADC_DATA)
num_avg = sum(ADC_DATA)/len(ADC_DATA)

print("El max: " + str(num_max) + "  El min: " + str(num_min) +"  El avg: " + str(num_avg))