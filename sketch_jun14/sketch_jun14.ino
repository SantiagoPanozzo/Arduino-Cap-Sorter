// Setup del sensor
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);

// Setup del motor
#include <Servo.h>
// declaro variables de los colores
//            oscuro,claro,rojo,azul,verde,amarillo,otro;
int colores[7]={0};
Servo servo_9;
Servo servo_10;

void setup() {
 Serial.begin(9600);
 // servo al puerto 9
 servo_9.attach(9, 500, 2500);
 // comprobar que este bien conectado el sensor
 if(tcs.begin()){
   Serial.println("Inicializando");
   delay(2000);
 }
 else{
  Serial.println("Error");
  Serial.println("Debe de revisar las conexiones e iniciar nuevamente");
  while(1)delay(500);
  }
}

// funcion para leer los colores y retornar el predominante
int lectura(){
  uint16_t R,G,B,C;
  tcs.getRawData(&R,&G,&B,&C);
  if(R>255){R=255;}
  if(G>255){G=255;}
  if(B>255){B=255;}
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
    void abiertocerrado(){}
};
int R,G,B;
void loop() {
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
        // si el color es rojo, mover el servo de 0 al punto deseado de 5 en 5
        for (int pos = posA; pos <= posB; pos += 2){
          servo_9.write(pos);}
        break;
      }
      case 3:{
        Serial.println("--Azul");
        R=0;
        G=0;
        B=255;
        break;
      }
      case 4:{
        Serial.println("--Verde");
        R=0;
        G=255;
        B=0;
        break;
      }
      case 5:{
        Serial.println("--Amarillo");
        R=255;
        G=80;
        B=0;
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
  //reseteo el servo a la posición inicial: va desde el punto al que se mueve, hasta cero, de 5 en 5
  for (int pos = posB; pos >= posA; pos -= 2){
      servo_9.write(pos);}

  // Serial.println(" R = "+String(R)+ " G = "+String(G)+ " B = "+String(B));
}
