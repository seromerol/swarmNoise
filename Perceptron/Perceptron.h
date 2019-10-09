/*
  Perceptron.h - Librería para usar un arduino como un perceptron 
  permite conectar acrudinos en cascada para generar una red neuronal
  Creada por Tecnopoéticas UN - 2019
  Sergio Romero
  Proyecto Swarm Noise
*/
#ifndef Perceptron_h
#define Perceptron_h

#include "Arduino.h"

class Perceptron
{
  public:
    	Perceptron(byte actD, byte actW, byte senD, byte senW);
    	void setWeights(float w[]);
	String getWeights();
    	void printLine(String n, float b);
    	float sumFunction(float in[], float w[], float b);
    	float activation(float sum);
	void update();
  private:
    	byte actData; //pin (PWM) donde conectar servo/actuador que transmite el dato input
	byte senData; //pin (A?) donde conectar flexor/sensor que recibe el dato input
	byte actWeight; //pin (PWM) donde conectar servo/actuador que transmite el peso del input
	byte senWeight; //pin (A?) donde conectar flexor/sensor que recibe el peso del input
	byte output_pin; // pin (PWM) de salida de la neurona
	//static const byte input_pins[];
	byte *input_pins;
	float bias;
	float *input; //array para guardar datos de entrada
	float *weight; //array para guardar datos de los pesos de cada entrada
	float data; //almacena el valor de la suma de las entradas por el peso y bias
	float output;  //dato de salida de la funcion de activacion
};

#endif
