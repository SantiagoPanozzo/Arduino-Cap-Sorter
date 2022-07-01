#include <Stepper.h>

// Defino el número de pasos
const int stepsPerRevolution = 2048;

// Conexiones
// Pin 8/4 to IN1 
// Pin 9/5 to IN2 
// Pin 10/6 to IN3 
// Pin 11/7 to IN4 

// Creamos el objeto
Stepper myStepper = Stepper(stepsPerRevolution, 4, 6, 5, 7);

void setup() {
  // rapidez de giro en rpm
  myStepper.setSpeed(16);
  
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
  myStepper.step(-stepsPerRevolution);
  //delay(500);
}
