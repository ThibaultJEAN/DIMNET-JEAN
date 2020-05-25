#include "core_simulation.h"
#include "mydevices.h"


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorPorte porte(PORTE);
  AnalogSensorPressure debit(DELAY,debit_eau);
  AnalogSensorTemperature temperature(DELAY,temperature_eau);
  AnalogSensorLuminosity luminosite(DELAY,luminosite_environnement);
  DigitalActuatorLED led1(DELAY);
  I2CActuatorScreen screen_temp;
  I2CActuatorScreen screen_lumi;

  // branchement des capteurs actionneurs
  esp8266.pin(3,porte);
  esp8266.pin(4,debit);
  esp8266.pin(1,temperature);
  esp8266.pin(2,luminosite);
  esp8266.pin(0,led1);
  //esp8266.i2c(1,screen_temp);
  //esp8266.i2c(2,screen_lumi);
  
  // allumage de la carte
  esp8266.run();
  return 0;
}


