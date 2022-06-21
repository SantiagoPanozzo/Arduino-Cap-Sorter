// Setup del sensor
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);

// Setup del motor
#include <Servo.h>
int colores[7]={0};
int pos = 0;
Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;

// Setup del stepper
#include <Stepper.h>
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 4, 5, 6, 7);

void setup() {
 Serial.begin(9600);
// set the stepper speed |  at 60 rpm:
  myStepper.setSpeed(60);
 // servos a los puertos 9,10,11,12
  servo_1.attach(9, 500, 2500);
  servo_2.attach(10, 500, 2500);
  servo_3.attach(11, 500, 2500);
  servo_4.attach(12, 500, 2500);

 //comprobar conexiones 
 if (tcs.begin()){
   Serial.println("Inicializando");
   delay(2000);
 }
 else{
   Serial.println("Error");
   Serial.println("Debe revisar las conexiones");
   while(1)delay(500);
 }
}

// funcion para leer los colores y retornar el predominante
// los valores de estos "if" son los que se tienen que modificar para ajustar los colores
int lectura(){
  uint16_t R,G,B,C;
  tcs.getRawData(&R,&G,&B,&C);
  if(R<10 && G<10 && B<10){
    return 0;} //oscuro
  else if(R>200 && G>200 && B>200){
    return 1;} //claro
  else if(R> (G+(G/5)) && R >(B+(B/10))){
    return 2;} //rojo
  else if((R<35 || R>55) && (G<100 || G>120)&& (G>(R+(R/5)) && G>(B+(B/10)))){ // && (B<30 || B>50) 
    return 3;} //verde
  else if(B> (G+(G/5)) && B >(R+(R/5))){
    return 4;} //azul
  else if((R<35 || R>55) && (G<100 || G>120) && (R>(B+(B/5))) && G>(B+(B/10))){ //(B<30 || B>50)
    return 5;} //amarillo
  else {
    return 6;} //otro
}

class servomotor{
  public:
    bool abierto = false;
    int posA = 40;
    int posB = 95;
    Servo servo_x;
    servomotor(Servo servo_x){
      this->servo_x = servo_x;
      this->servo_x.write(95);
    }
    void abrir_servo(){
      if (!abierto){
        for (int pos = posA; pos <= posB; pos += 10) {
          servo_x.write(pos);
          delay(100);}
      }}
    void cerrar_servo(){
      if (abierto){
        for (int pos = posB; pos >= posA; pos -= 10){
          servo_x.write(pos);
          delay(15);}
        }
      }
    };

servomotor servo_rojo = servomotor(servo_1);
servomotor servo_verde = servomotor(servo_2);
servomotor servo_azul = servomotor(servo_3);
servomotor servo_amarillo = servomotor(servo_4);

int direccion = 0;

int R,G,B;
void loop() {
  if (direccion < 50){
    myStepper.step(stepsPerRevolution);}
  else{
    myStepper.step(-stepsPerRevolution);}
  direccion += 1;
  memset(colores, 0, sizeof colores);
  int posA = 90;
  int posB = 160;

  // bucle que lee 5 veces los colores y los va contando
  int lect;
  int maximo, maxI;
  maximo = 0;
  for(int i = 0; i < 5; i++){
    lect = lectura();
    colores[lect] += 1;
    if (colores[lect]> maximo){
        maxI = lect;
        maximo = colores[lect];
      }
    }
  // dependiendo de cual color aparece mas veces en las 5 lecturas, ese es el elegido
  switch(maxI){
      case 0:{
        Serial.println("--Oscuro");
        R=0;
        G=0;
        B=0;
        break;
      }
      case 1:{
        Serial.println("--Claro");
        R=255;
        G=255;
        B=255;
        break;
      }
      case 2:{
        Serial.println("--Rojo");
        R=255;
        G=0;
        B=0;
        
        servo_rojo.abrir_servo();
        delay(100);
        servo_rojo.cerrar_servo();
        break;
      }
      case 3:{
        Serial.println("--Azul");
        R=0;
        G=0;
        B=255;

        servo_azul.abrir_servo();
        delay(100);
        servo_azul.cerrar_servo();
        break;
      }
      case 4:{
        Serial.println("--Verde");
        R=0;
        G=255;
        B=0;

        servo_verde.abrir_servo();
        delay(100);
        servo_verde.cerrar_servo();
        break;
      }
      case 5:{
        Serial.println("--Amarillo");
        R=255;
        G=80;
        B=0;

        servo_amarillo.abrir_servo();
        delay(100);
        servo_amarillo.cerrar_servo();
        break;
      }
      case 6:{
        Serial.println("--Otro R = "+String(R)+ " G = "+String(G)+ " B = "+String(B));
        break;
      }
    }
  // escribimos el color al pin para la luz led
  analogWrite(11,R);
  analogWrite(10,G);
  analogWrite(9,B);

  // esperar 2 segundos
  delay(200);

  // debug:
  // Serial.println(" R = "+String(R)+ " G = "+String(G)+ " B = "+String(B));
}