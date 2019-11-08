#include <Perceptron.h>

byte inpin[]= {2,3,4,5};
//número de entradas, pines analógicos de entrada, pin de salida
Perceptron neuron(4, inpin, 12);

byte datain[4]; 
byte weightin[4];

void setup() {
  Serial.begin(9600);
  neuron.setWeights();
  String w = neuron.getWeights();
  Serial.println(w);
}

void loop() {
  neuron.read();
  neuron.getInputs(datain);
  neuron.getWeights(weightin);
  neuron.sumFunction(datain, weightin);
  neuron.write();
}
