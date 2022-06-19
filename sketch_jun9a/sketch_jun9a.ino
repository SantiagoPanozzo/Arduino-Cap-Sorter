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
void loop() {
  //uint16_t Adafruit_TCS34725::calculateColorTemperature(uint16_t r, uint16_t g, uint16_t b);
  int oscuro,claro,rojo,azul,verde,amarillo,otro;
  oscuro = 0;
  claro = 0;
  rojo = 0;
  azul = 0;
  verde = 0;
  amarillo = 0;
  otro = 0;
  int R,G,B;
  /* for(int i = 0; i < 5; i+=1){
    int lect = lectura();
    switch(lect){
      case 0:{oscuro = oscuro+1;
      Serial.println("oscuro"+String(oscuro));}
      case 1:{claro = claro+1;
      Serial.println("Claro"+String(claro));}
      case 2:{rojo = rojo+1;
      Serial.println("Rojo"+String(rojo));}
      case 3:{verde = verde+1;
      Serial.println("Verde"+String(verde));}
      case 4:{azul = azul+1;
      Serial.println("Azul"+String(azul));}
      case 5:{amarillo = amarillo+1;
      Serial.println("Amarillo"+String(amarillo));}
      case 6:{otro = otro+1;
      Serial.println("Otro"+String(otro));}
    }
  }*/
  int i = 0;
  while(i < 5){
    int lect = lectura();
    switch(lect){
      case 0:{oscuro = oscuro+1;
      //Serial.println("oscuro"+String(oscuro));
      i += 1;
      break;}
      case 1:{claro = claro+1;
      //Serial.println("Claro"+String(claro));
      i += 1;
      break;}
      case 2:{rojo = rojo+1;
      //Serial.println("Rojo"+String(rojo));
      i += 1;
      break;}
      case 3:{verde = verde+1;
      //Serial.println("Verde"+String(verde));
      i += 1;
      break;}
      case 4:{azul = azul+1;
      //Serial.println("Azul"+String(azul));
      i += 1;
      break;}
      case 5:{amarillo = amarillo+1;
      //Serial.println("Amarillo"+String(amarillo));
      i += 1;
      break;}
      case 6:{otro = otro+1;
      //Serial.println("Otro"+String(otro));
      i += 1;
      break;}
    Serial.println(i);
  }}
  if ((oscuro>=claro) && (oscuro>=rojo) && (oscuro>=verde) && (oscuro>=azul) && (oscuro>=amarillo) && (oscuro>=otro)){
    Serial.println("--Oscuro R = "+String(R)+ " G = "+String(G)+ " B = "+String(B));
    R=0;
    G=0;
    B=0;}
  else if ((claro>=oscuro) && (claro>=rojo) && (claro>=verde) && (claro>=azul) && (claro>=amarillo) && (claro>=otro)){
    Serial.println("--Claro");
    R=255;
    G=255;
    B=255;}
  else if ((rojo>=oscuro) && (rojo>=claro) && (rojo>=verde) && (rojo>=azul) && (rojo>=amarillo) && (rojo>=otro)){
    Serial.println("--Rojo");
    R=255;
    G=0;
    B=0;}
  else if ((azul>=oscuro) && (azul>=claro) && (azul>=verde) && (azul>=rojo) && (azul>=amarillo) && (azul>=otro)){
    Serial.println("--Azul");
    R=0;
    G=0;
    B=255;}
  else if ((verde>=oscuro) && (verde>=claro) && (verde>=rojo) && (verde>=azul) && (verde>=amarillo) && (verde>=otro)){
    Serial.println("--Verde");
    R=0;
    G=255;
    B=0;}
  else if ((amarillo>=oscuro) && (amarillo>=claro) && (amarillo>=rojo) && (amarillo>=azul) && (amarillo>=verde) && (amarillo>=otro)){
    Serial.println("--Amarillo");
    R=255;
    G=80;
    B=0;}
  else {//if ((otro>=oscuro) && (otro>=claro) && (otro>=rojo) && (otro>=azul) && (otro>=verde) && (otro>=amarillo)){
  Serial.println("--Otro R = "+String(R)+ " G = "+String(G)+ " B = "+String(B));}


  analogWrite(11,R);
  analogWrite(10,G);
  analogWrite(9,B);

// Serial.println(" R = "+String(R)+ " G = "+String(G)+ " B = "+String(B));
 //delay(300);

}