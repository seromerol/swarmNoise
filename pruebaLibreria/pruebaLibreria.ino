#include <Perceptron.h>
#define ENTRADAS 4

//pines analógicos de entrada
byte inpin[]= {2,3,4,5};

//número de entradas, pines analógicos de entrada, pin de salida (pwm)
Perceptron neuron(ENTRADAS, inpin, 12);

//arrays que se usaran para obtener los valores de los inputs y los weights
byte datain[ENTRADAS]; 
byte weightin[ENTRADAS];

void setup() {
  Serial.begin(9600);
  //configura aleatoriamente los pesos
  neuron.setWeights();
  //configura el bias. (opcional bias predeterminado=1)
  neuron.setBias(-200);
  //configura la impresión de datos por serial (1 imprime 0 no);
  neuron.setDebug(1);
}

void loop() {
  //lee los valores de entrada
  neuron.read();

  //carga los arrays con los datos entrada y pesos
  neuron.getInputs(datain);
  neuron.getWeights(weightin);

 

  //calcula la sumatoria de los datos que entran E(input*weigth) + bias
  neuron.sumFunction(datain, weightin);

  //calcula y escribe el dato de salida n el pin output
  neuron.write();
}
