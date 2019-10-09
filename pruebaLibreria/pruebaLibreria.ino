#include <Perceptron.h>

Perceptron neuron(9,11,0,1);

void setup() {
  Serial.begin(9600);
  String w = neuron.getWeights();
  Serial.println(w);
}

void loop() {
  // put your main code here, to run repeatedly:

}
