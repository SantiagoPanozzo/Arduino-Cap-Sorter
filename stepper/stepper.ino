#include <Stepper.h>

// Defino el número de pasos
const int pasosCinta = 2500;
const int pasosTapas = 300;

// Conexiones
// Pin 8/4 to IN1 
// Pin 9/5 to IN2 
// Pin 10/6 to IN3 
// Pin 11/7 to IN4 

// Creamos el objeto
Stepper cinta = Stepper(pasosCinta, 4, 6, 5, 7);
Stepper tapitas = Stepper(pasosTapas,8,10,9,11);

void setup() {
  // rapidez de giro en rpm
  cinta.setSpeed(16);
  tapitas.setSpeed(16);
  // Comunicación serial
  Serial.begin(9600);
}

void loop() {
  // Paso horario
  //Serial.println("clockwise");
  //myStepper.step(stepsPerRevolution);
  //delay(500);
  
  // Paso antihorario
  //Serial.println("counterclockwise");
  cinta.step(-pasosCinta);
  tapitas.step(-pasosTapas);
  //delay(500);
}
