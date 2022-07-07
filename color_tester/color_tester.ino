#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);

void setup() {
  Serial.begin(9600);
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

int mayR = 0;
int mayG = 0;
int mayB = 0;
int mayL = 0;
int mayT = 0;

void loop() {
  uint16_t r, g, b, c, colorTemp, lux;
  
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  //Serial.println(" R = "+String(r)+ "| G = "+String(g)+ "| B = "+String(b)+ "| Lux = "+String(lux)+"| Temp = "+ String(colorTemp));

  if (r > mayR){mayR = r;}
  if (g > mayG){mayG = g;}
  if (b > mayB){mayB = b;}
  if (colorTemp > mayT){mayT = colorTemp;}
  if (lux > mayL){mayL = lux;}
  Serial.println(" R = "+String(mayR)+ "| G = "+String(mayG)+ "| B = "+String(mayB)+ "| Lux = "+String(mayL)+"| Temp = "+ String(mayT));
}