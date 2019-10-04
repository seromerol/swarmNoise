# swarmNoise

## perceptronBasico.ino
El archivo tiene un codigo que funciona con unos datos de entrada analógica (probado con fotoceldas) y la salida la da por PWM en un pin digital (probado con un led), los pesos son establecidos manualmente y tiene el funcionamiento completo de una neurona con activacion con funcion sigmoid y NO TIENE NADA DE LA PARTE ANALÓGICA DE PROCESAMIENTO CON EL ACOPLE SENSOR/ACTUADOR, es simplemente para ver como opera la información internamente.

## sensibleNeuronDosServos.ino
El archivo parte del perceptron básico pero le integra una funcion para generar los pesos aleatorios y, lo más importante, integra la parte analógica con dos servos y dos flexores: una pareja que se encarga de comunicar los datos de la entrada y otra que se encarga de comunicar los datos de los pesos de cada entrada. La activacion funciona igual que el perceptron por sigmoid.
