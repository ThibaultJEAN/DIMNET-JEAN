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
  AnalogActuatorElectrovanne electronvanne1(DELAY);
  DigitalActuatorLED led1(DELAY,'R');
  DigitalActuatorLEDBarre ledbarre1(DELAY,NB_LED);
  I2CActuatorScreen screen_temp;
  I2CActuatorScreen screen_lumi;

  // branchement des capteurs actionneurs
  esp8266.pin(PIN_CAPTEUR_PORTE,porte);
  esp8266.pin(PIN_CAPTEUR_PRESSION,debit);
  esp8266.pin(PIN_CAPTEUR_TEMP,temperature);
  esp8266.pin(PIN_CAPTEUR_LUM,luminosite);
  esp8266.pin(PIN_LED,led1);
  esp8266.pin(PIN_LEDBARRE,ledbarre1);
  esp8266.pin(PIN_ACTIONNEUR_ELECTROVANNE,electronvanne1);
  //esp8266.i2c(I2C_SCREEN_TEMP,screen_temp);
  //esp8266.i2c(I2C_SCREEN_LUM,screen_lumi);
  
  // allumage de la carte
  esp8266.run();
  return 0;
}


