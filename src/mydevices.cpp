
#include "mydevices.h"

using namespace std;

int luminosite_environnement = 200;
float debit_eau = 2;
int temperature_eau = 30;

AnalogSensorPorte::AnalogSensorPorte(bool Porte):Device(){
	Porteouverte = Porte;
}
bool AnalogSensorPorte::getPorte(){
	return Porteouverte;
}
void AnalogSensorPorte::setPorte(bool porte){
	Porteouverte = porte;
}

void AnalogSensorPorte::run(){
  char toto;
  while(1){
	
	scanf("%c",&toto);
	if (toto == 'o'){
		setPorte(true);
	} if (toto == 'f'){
		setPorte(false);
	}
	*ptrmem = Porteouverte;
	}
}

AnalogSensorPressure :: AnalogSensorPressure(int t, float pres): Device(),val_pres(pres),temps(t){
alea = 2;
}
void AnalogSensorPressure::run(){
  while(1){
	alea = 2-rand()%2;
	 if(ptrmem!=NULL)
      	  *ptrmem=val_pres+alea;
    	sleep(temps);
  }

}

//classe AnalogSensorLuminosity
AnalogSensorLuminosity::AnalogSensorLuminosity(int t,int l): Device(),val_lux(l),temps(t){
alea = 20;
}

void AnalogSensorLuminosity::run(){
  while(1){
    alea=20-rand()%20;
    if(ptrmem!=NULL)
      *ptrmem=val_lux+alea;
    sleep(temps);
  }
}

//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d,int t):Device(),val_temp(t),temps(d){
  alea=1;
}

void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val_temp+alea;
    sleep(temps);
  }
}

//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    /*if (state==LOW)
      cout << "((((eteint))))\n";
    else
      cout << "((((allume))))\n";
    sleep(temps);*/
    }
}

// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){
  }

void I2CActuatorScreen::run(){
  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :"<< buf << endl;
    }
    sleep(1);
    }
}





