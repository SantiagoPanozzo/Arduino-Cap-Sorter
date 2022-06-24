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

void loop() {
  uint16_t r, g, b, c, colorTemp, lux;
  
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  Serial.println(" R = "+String(r)+ "| G = "+String(g)+ "| B = "+String(b)+ "| Lux = "+String(lux)+"| Temp = "+ String(colorTemp));
}