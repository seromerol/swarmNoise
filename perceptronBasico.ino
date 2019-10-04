#define output_pin 13 //pin de salida de la neurona
#define pot 5 //pin del potenciometro que gradua el bias

//pines analogos de entrada 
byte input_pins[] = {0, 1, 2, 3}; 

//data
float input[sizeof(input_pins)]; //input data
float weight[sizeof(input_pins)]; //weight of each output
float bias;
float data; //sum function processed value
float output;  //activation output data

void setup() {
  Serial.begin(9600);
  pinMode(output_pin, OUTPUT);

  //asigna los pesos
  setWeights(weight);
  
}

void loop() {
  //configura el bias con el potenciometro
  bias = analogRead(pot)-512;
  printLine("bias: ", bias);
  
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
  Serial.println("");
}

//configura pesos manualmente
void setWeights(float w[]){
  w[0] = 0.25;
  printLine("peso 0: ", w[0]);
  w[1] = -0.25;
  printLine("peso 1: ", w[1]);
  w[2] = 0.25;
  printLine("peso 2: ", w[2]);
  w[3] = -0.25;
  printLine("peso 3: ", w[3]);
  Serial.print("\r\n");
}

float sumFunction(float in[], float w[], float b){
  float d = 0; //temporal para guardar la suma
  
  //suma cada entrada por el peso de la misma
  for (byte i = 0; i < sizeof(input_pins); i++) {
    d += (in[i] * w[i]);
  }
  //suma el bias
  d += bias;
  return d;
}

float activation(float sum){
  //sigmoid (devuelve valores entre 0 y 1)
  return (1 / (1 + exp(-1 * sum)));
  
  //tanh (devuelve valores entre -1 y 1)
  //return ((2 / (1 + exp(2 * sum)))-1);
  
  //ReLU (anula valores negativos volviendolos 0)
  //return ((sum<0)?0:sum);

  //Leaky ReLU  (mismo pero los negativos los "rectifica")
  //return ((sum<0)?(sum*0.01):sum);
}

//funcion que imprime un dato con su etiqueta en la misma linea y separa con tab
void printLine(String n, float b){
  Serial.print(n);
  Serial.print(b);
  Serial.print("\t");
}


