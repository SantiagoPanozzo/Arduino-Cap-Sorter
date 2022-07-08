// Setup del sensor
#include "Adafruit_TCS34725.h"
#include "SafeString.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);

// Setup del motor
#include <Servo.h>
int pos = 0;
Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;

// Timings de los servos

unsigned long timerRojo[10] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL}; // 10 timers por color
unsigned long timerVerde[10] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL}; 
unsigned long timerAzul[10] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL}; 
unsigned long timerAmarillo[10] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL}; 

unsigned long millisRojo = 12000UL; // 210000 milisegundos para que la tapa llegue al destino rojo
unsigned long millisVerde = 21000UL; // 300000 milisegundos para que la tapa llegue al destino verde
unsigned long millisAzul = 33550UL; // 440000 milisegundos para que la tapa llegue al destino azul
unsigned long millisAmarillo = 40500UL;// 630000 milisegundos para que la tapa llegue al destino amarillo

// array de colores para medidas
int colores[7]={0};

void setup() {
 Serial.begin(9600);
 // servos a los puertos 9,10,11,12
  servo_1.attach(9, 500, 2500);
  servo_2.attach(10, 500, 2500);
  servo_3.attach(11, 500, 2500);
  servo_4.attach(12, 500, 2500);
}

// funcion para leer los colores y retornar el predominante
// los valores de estos "if" son los que se tienen que modificar para ajustar los colores
int lectura(){
  uint16_t R,G,B,C,colorTemp,lux; // valores de rojo, verde, azul, temperatura de color y luminosidad
  tcs.getRawData(&R,&G,&B,&C); // obtener r, g, b
  colorTemp = tcs.calculateColorTemperature(R, G, B); // obtener temperatura de color
  lux = tcs.calculateLux(R,G,B); // obtener luminosidad
  Serial.println(" R = "+String(R)+ "| G = "+String(G)+ "| B = "+String(B)+ "| Lux = "+String(lux)+"| Temp = "+ String(colorTemp)); // para ver los valores que se estan registrando
  if(R<=30 && G<=30 && B<=34 && lux <= 10  && lux > 3 && colorTemp < 18000){
    return 0;} //oscuro
  else{
    if(R>200 && G>200 && B>200){
      return 1;} //claro
    else if(R>G && R>B && colorTemp<6000){ // 
      //Serial.println("rojo");
      return 2;} //rojo
    else if(G > R && G > B && lux > R){ // 
      //Serial.println("verde");
      return 3;} //verde
    else if(B > R && B > G && G > lux && B > lux && colorTemp > 18000){ // && colorTemp > 10000
      //Serial.println("azul");
      return 4;} //azul
    else if(R > B && G > B && lux > B){ // && colorTemp>3000 && colorTemp<4500
      //Serial.println("amarillo");
      return 5;} //amarillo
    else {
      return 6;} //otro
  }
}

class servomotor{ // definimos la clase servomotor
  public:
    bool abierto = false;
    int posA = 40; // posicion inicial, grados en los que el servo esta "cerrado"
    int posB = 95; // posicion final, grados en los que el servo esta "abierto"
    Servo servo_x; // servo_x es un servo cualquiera
    servomotor(Servo servo_x){
      this->servo_x = servo_x;
      this->servo_x.write(posB); // al principio el servo tiene que estar en la posicion B
    }
    void abrir_servo(){
      if (!abierto){ // si el servo no esta abierto
        for (int pos = posA; pos <= posB; pos += 10) { // rotar desde posicion A a posicion B
          servo_x.write(pos);
          delay(100);
          }
      }}
    void cerrar_servo(){
      if (abierto){ // si el servo esta abierto
        for (int pos = posB; pos >= posA; pos -= 10){ // rotar desde posicion B a posicion A
          servo_x.write(pos);
          delay(15);
          }
        }
      }
    };
    

servomotor servo_rojo = servomotor(servo_1);       // el rojo es el servo 1
servomotor servo_verde = servomotor(servo_2);      // el verde es el servo 2
servomotor servo_azul = servomotor(servo_3);       // el azul es el servo 3
servomotor servo_amarillo = servomotor(servo_4);   // el amarillo es el servo 4

int R,G,B;

unsigned long timear(unsigned long* timerColor, unsigned long millisColor){      // funcion para empezar los timers cuando pasa una tapa
  for (int i = 0; i < 10; i++){                                                  // timers del 1 al 10
    if (timerColor[i] < millis()){                                               // si la hora actual es > que la hora del timer, lo podemos sobreescribir
      timerColor[i] = millis()+millisColor;                                      // el timer es la hora actual + lo que tarda la tapa
      break;
      }
    }
  } 

bool itsTIME(int i, unsigned long timerColor[10]){ // funcion para ver si el timer esta terminando
    if ((millis() > (timerColor[i] - 150UL)) && (millis() < (timerColor[i] + 150UL))){ // si la hora actual es la misma hora que el timer +- 150 ms
      return true;
    }
  return false;
  }

void loop() {
  memset(colores, 0, sizeof colores); // establecer memoria para el detector de colores

  for(int i = 0; i < 10; i++){ // timers del 1 al 10
    if (itsTIME(i,timerRojo)){ // si algun timer esta en hora, abrir el servo correspondiente
      servo_rojo.abrir_servo();
      servo_rojo.cerrar_servo();}}

  for(int i = 0; i < 10; i++){
    if (itsTIME(i,timerVerde)){ // x2
        servo_verde.abrir_servo();
        servo_verde.cerrar_servo();}}

  for(int i = 0; i < 10; i++){
    if (itsTIME(i,timerAzul)){ // x3
        servo_azul.abrir_servo();
        servo_azul.cerrar_servo();}}

  for(int i = 0; i < 10; i++){
    if (itsTIME(i,timerAmarillo)){ // x4
        servo_amarillo.abrir_servo();
        servo_amarillo.cerrar_servo();}}

  // bucle que lee 5 veces los colores y los va contando
  int lect;
  int maximo, maxI;
  maximo = 0;
  lect = lectura(); // lect es el numero que representa un color en lectura()
  //Serial.println(lect);
  if (lect == 0){Serial.println("Negro");} // si es 0, es negro, pasamos
  else {Serial.println(lect); // si no es 0, es porque paso una tapita, ejecutamos lo siguiente:
    for(int i = 0; i < 5; i++){ // 5 veces:
      lect = lectura(); // leemos el color
      colores[lect] += 1; // sumamos 1 al color que hayamos leido
      if (colores[lect]> maximo){ // si el color que detectamos es el color que mas veces va apareciendo
          maxI = lect; // el maximo total es el color que detectamos (este es el que importa despues)
          Serial.println(maxI);
          maximo = colores[lect]; // el maximo relativo es el color que detectamos tambien
        }
      }
    
  
  // dependiendo de cual color aparece mas veces en las 5 lecturas, ese es el elegido
  switch(maxI){
      case 0:{ // 0 es negro, solo lo mostramos
        Serial.println("--Negro");
        break;
      }
      case 1:{ // 1 es claro/blanco, solo lo mostramos
        Serial.println("--Claro");
        break;
      }
      case 2:{
        Serial.println("--Rojo"); // 2 es rojo, iniciamos un timer rojo
        timear(timerRojo,millisRojo);
        break;
      }
      case 3:{
        Serial.println("--Verde"); // 3 es verde, iniciamos un timer verde
        timear(timerVerde,millisVerde);
        break;
      }
      case 4:{
        Serial.println("--Azul"); // 4 es azul, iniciamos un timer azul
        timear(timerAzul,millisAzul);
        break;
      }
      
      case 5:{
        Serial.println("--Amarillo"); // 5 es amarillo, iniciamos un timer amarillo
        timear(timerAmarillo,millisAmarillo);
        break;
      }
      case 6:{ // 6 es si es otro color, solo lo mostramos
        Serial.println("--Otro R");
        break;
      }
    }
  }
}