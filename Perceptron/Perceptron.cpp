#include "Arduino.h"
#include "Perceptron.h"

Perceptron::Perceptron(byte actD, byte actW, byte senD, byte senW) {
  actData = actD;
  actWeight = actW;
  senData = senD;
  senWeight = senW;

  //const byte Perceptron::input_pins[] = {2, 3, 4, 5};
  input_pins = new byte[4];
  input_pins[0] = 2;
  input_pins[1] = 3;
  input_pins[2] = 4;
  input_pins[3] = 5;
  output_pin = 12;
  bias = 1;
  input = new float[sizeof(input_pins)]; //array para guardar datos de entrada
  weight = new float[sizeof(input_pins)];

  //configuracion pines PWM como salidas
  pinMode(actData, OUTPUT);
  pinMode(actWeight, OUTPUT);
  pinMode(output_pin, OUTPUT);

  //semilla para pseudoaleatorio
  randomSeed(analogRead(0));

  //asigna los pesos
  setWeights(weight);
}

void Perceptron::update() {

  //lee datos de las entradas
  for (byte i = 0; i < sizeof(input_pins); i++) {
    input[i] = analogRead(input_pins[i]);
    printLine("input: ", input[i]);
  }

  //suma ponderada de las entradas + bias
  data = sumFunction(input, weight, bias);
  printLine("sum ax +b: ", data);

  //calcula la salida con la funcion de activacion
  output = activation(data);
  printLine("Neuron value: ", output);

  //escribe el dato de salida como PWM en el pin de salida
  analogWrite(output_pin, output * 255);

}

//funcion que carga la matriz de pesos con aleatorios entre -1 y 1
void Perceptron::setWeights(float w[]) {
  for (byte i = 0; i < sizeof(input_pins); i++) {
    w[i] =  random(-100, 100);
    w[i] = w[i] / 100;
    //w[i] = 1.0/sizeof(input_pins);
  }
}

String Perceptron::getWeights(){
  String out;
  for (byte i = 0; i < sizeof(input_pins); i++) {
    String s1 = "Weight ";
    String s2 = ": ";
    String s = s1 + i + s2;
    out+= s + weight[i];
  }
  return out;
}

//funcion que imprime un dato con su etiqueta en la misma linea y separa con tab
void Perceptron::printLine(String n, float b) {
}


//funcion que suma todos los productos del dato por el peso y le agrega el bias
float Perceptron::sumFunction(float in[], float w[], float b) {
  float d = 0; //temporal para guardar la suma

  //suma cada entrada por el peso de la misma
  for (byte i = 0; i < sizeof(input_pins); i++) {
    //si se quiere redimensionar a mano (a veces falla el map
    //(valoraredimensionar - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    //float ang = ((in[i] + 1) * 180) / 2;

    //se redimensionan los valores leidos de la entrada y el peso para un angulo
    float angD = map(in[i], 0, 1024, 0, 255);
    float angW = ((w[i] + 1) * 255) / 2;

    //para imprimir los angulos en serial
    String s1 = "ang servoData ";
    String s2 = "ang servoWeight ";
    String s3 = ": ";
    String sD = s1 + i + s3;
    String sW = s2 + i + s3;
    printLine(sD, angD);
    printLine(sW, angW);

    //se ubican los servos en el angulo
    analogWrite(actData, angD);
    analogWrite(actWeight, angW);
    delay(15); //tiempo de respuesta del servo

    //multiplica el valor leido por el sensor del dato de entrada por el sensor del peso y los suma a d
    d += (analogRead(senData) * analogRead(senWeight));
  }

  //suma el bias
  d += bias;

  //devuelve el resultado de la suma de cada (input*weight) mas el bias
  return d;
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
