#include "Arduino.h"
#include "Perceptron.h"

Perceptron::Perceptron(uint8_t np, uint8_t i[], uint8_t o) {
  bias = 1;
  debug=false;
  //semilla para pseudoaleatorio
  randomSeed(analogRead(0));
  input_pins = i;
  npines = np;
  output_pin = o;
  input = new uint8_t[np]; //array para guardar datos de entrada
  weight = new float[np];//array para guardar los pesos de cada entrada
}

void Perceptron::read() {
  //lee datos de las entradas
  for (uint8_t i = 0; i < npines; i++) {
    input[i] = ceil(analogRead(input_pins[i])/4);
    if(debug)printLine("input: ", input[i]);
  }
}
void Perceptron::setBias(float b) {
  bias = b;
}
void Perceptron::setDebug(uint8_t d) {
  debug = d;
}
void Perceptron::write() {
  //calcula la salida con la funcion de activacion
  output = activation(data);
  if(debug)printLine("Neuron value: ", output);
  if(debug)Serial.println();

  //escribe el dato de salida como PWM en el pin de salida
  analogWrite(output_pin, output * 255);
}

//funcion que carga la matriz de pesos con aleatorios entre -1 y 1
void Perceptron::setWeights() {
  for (uint8_t i = 0; i < npines; i++) {
    weight[i] =  random(-100, 100);
    weight[i] = weight[i] / 100;
    //w[i] = 1.0/sizeof(input_pins);
    String s1 = "Weight ";
    String s2 = ": ";
    String s = s1 + i + s2;
    if(debug)printLine(s + weight[i], output);
    if(debug)Serial.println();
  }
}

//funcion que imprime un dato con su etiqueta en la misma linea y separa con tab
void Perceptron::printLine(String n, float b) {
  Serial.print(n);
  Serial.print(b);
  Serial.print("\t");
}


//funcion que suma todos los productos del dato por el peso y le agrega el bias
void Perceptron::sumFunction(uint8_t in[], uint8_t w[]) {
  data = 0; //temporal para guardar la suma

  //suma cada entrada por el peso de la misma
  for (uint8_t i = 0; i < npines; i++) {
    //si se quiere redimensionar a mano (a veces falla el map
    //(valoraredimensionar - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    //float ang = ((in[i] + 1) * 180) / 2;
    float wt = ((w[i]+1.0)*2.0)/(254.0);//redimensionado de 0-255 a 1-(-1)

    data += (in[i] * wt);
  }

  //suma el bias	
  data += bias;
  if(debug)printLine("sum ax +b: ", data);

}

//funcion que recibe la suma de los datos de entrada y activa la neurona
float Perceptron::activation(float sum) {
  //sigmoid (devuelve valores entre 0 y 1)
  return (1 / (1 + exp(-1 * sum)));

  //tanh (devuelve valores entre -1 y 1)
  //return ((2 / (1 + exp(2 * sum)))-1);

  //ReLU (anula valores negativos volviendolos 0)
  //return ((sum<0)?0:sum);

  //Leaky ReLU  (mismo pero los negativos los "rectifica")
  //return ((sum<0)?(sum*0.01):sum);
}

void Perceptron::getInputs(uint8_t *array){
  for (uint8_t i = 0; i < npines; i++) {
    array[i] = input[i];
  }
}
void Perceptron::getWeights(uint8_t *array){ 
  for (uint8_t i = 0; i < npines; i++) {
	array[i]=ceil((weight[i]+1)*128);
  }
}
