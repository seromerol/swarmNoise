/*
  Perceptron.h - Librería para usar un arduino como un perceptron 
  permite conectar ardudinos en cascada para generar una red neuronal
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
    	Perceptron(uint8_t np, uint8_t i[], uint8_t o);//configura pines de entrada y salida
	uint8_t npines;
    	void setWeights(); //configura los pesos
	void read(); //lee los datos de entrada
    	float sumFunction(uint8_t in[], uint8_t w[]); // calcula la sumatoria ponderada total E(wx) + b
    	float activation(float sum); 
	void write(); //genera la salida de la neurona
	void printLine(String n, float b);
	String getWeights(); 
	void getInputs(uint8_t *array);
	void getWeights(uint8_t *array);
  private:
	uint8_t output_pin; // pin (PWM) de salida de la neurona
	//static const byte input_pins[];
	uint8_t *input_pins;//pines análogos de entrada
	float bias;
	uint8_t *input; //array para guardar datos de entrada
	float *weight; //array para guardar datos de los pesos de cada entrada
	float data; //almacena el valor de la suma de las entradas por el peso y bias
	uint8_t output;  //dato de salida de la funcion de activacion
};

#endif
