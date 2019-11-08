#include <Perceptron.h>
#define ENTRADAS 4 //numero de entradas de la neurona
#define actData 9 //pin (PWM) donde conectar servo/actuador que transmite el dato input
#define senData 0 //pin (A?) donde conectar flexor/sensor que recibe el dato input
#define actWeight 11 //pin (PWM) donde conectar servo/actuador que transmite el peso del input
#define senWeight 1 //pin (A?) donde conectar flexor/sensor que recibe el peso del input

//pines analógicos de entrada
byte inpin[] = {2, 3, 4, 5};

//número de entradas, pines analógicos de entrada, pin de salida (pwm)
Perceptron neuron(ENTRADAS, inpin, 12);

//arrays que se usaran para obtener los valores de los inputs y los weights
byte datain[ENTRADAS];
byte weightin[ENTRADAS];

void setup() {
  Serial.begin(9600);
  pinMode(actData, OUTPUT);
  pinMode(actWeight, OUTPUT);

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

  //parte del codigo que se modifica para el protocolo de comunicacion
  for (byte i = 0; i < sizeof(datain); i++) {
    analogWrite(actData, datain[i]);
    analogWrite(actWeight, weightin[i]);
    delay(15); //tiempo de respuesta del actuador
    datain[i] = analogRead(senData) / 4; //se divide en 4 para redimensionar a 255
    weightin[i] = analogRead(senWeight) / 4; //se divide en 4 para redimensionar a 255
  }

  //calcula la sumatoria de los datos que entran E(input*weigth) + bias
  neuron.sumFunction(datain, weightin);

  //calcula y escribe el dato de salida n el pin output
  neuron.write();
}
