#include <Stepper.h>

// Defino el número de pasos
const int stepsPerRevolution = 2048;

// Conexiones
// Pin 8 to IN1 
// Pin 9 to IN2 
// Pin 10 to IN3 
// Pin 11 to IN4 

// Creamos el objeto
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // rapidez de giro en rpm
  myStepper.setSpeed(5);
  
  // Comunicación serial
  Serial.begin(9600);
}

void loop() {
  // Paso horario
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);
  
  // Paso antihorario
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
}
