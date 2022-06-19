/*ALGOBACK YOUTUBE CHANNEL*/
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);


void setup() {
 Serial.begin(9600);
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


int contador = 0;

void loop() {
  uint16_t R,G,B,C;
  tcs.getRawData(&R,&G,&B,&C);
  //uint16_t Adafruit_TCS34725::calculateColorTemperature(uint16_t r, uint16_t g, uint16_t b);
  contador = contador + 1;
  Serial.println(contador);
  if(contador == 500){return;}
  if(R>255){R=255;}
  if(G>255){G=255;}
  if(B>255){B=255;}
  if(R<10 && G<10 && B<10){
    Serial.println("Oscuro");
    R=0;
    G=0;
    B=0;}
  else if(R>200 && G>200 && B>200){
    Serial.println("Claro");
    R=255;
    G=255;
    B=255;}
  else if(R> (G+(G/5)) && R >(B+(B/5))){
    Serial.println("Rojo");
    R=255;
    G=0;
    B=0;}
  else if(B> (G+(G/5)) && B >(R+(R/5))){
    Serial.println("Azul");
    R=0;
    G=0;
    B=255;}
  else if((R<35 || R>55) && (G<100 || G>120)&& (G>(R+15) && G>(B+(+B/5)))){ // && (B<30 || B>50) 
    Serial.println("Verde");
    R=0;
    G=255;
    B=0;}
  else if((R<35 || R>55) && (G<100 || G>120) && (R>B && G>B)){ //(B<30 || B>50)
    Serial.println("Amarillo R = "+String(R)+ " G = "+String(G)+ " B = "+String(B));
    R=255;
    G=80;
    B=0;}
  else {
    Serial.println("Otro R = "+String(R)+ " G = "+String(G)+ " B = "+String(B));
  }

 analogWrite(11,R);
 analogWrite(10,G);
 analogWrite(9,B);
 
 //Serial.println(" R = "+String(R)+ " G = "+String(G)+ " B = "+String(B));
 delay(300);



}

