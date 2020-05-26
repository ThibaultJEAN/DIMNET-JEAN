
#include "mydevices.h"

using namespace std;

int luminosite_environnement = 200;
float debit_eau = 0;
int temperature_eau = 30;

AnalogActuatorElectrovanne::AnalogActuatorElectrovanne(int t): Device(),temps(t){
	ouverture = 0;
}

void AnalogActuatorElectrovanne::setOuverture(int o){
	ouverture = o;
}
int AnalogActuatorElectrovanne::getOuverture(){
	return ouverture;
}
void AnalogActuatorElectrovanne::run(){
	while(1){
		
    if(ptrmem!=NULL){
      ouverture=*ptrmem;
      debit_eau = (int)((10*ouverture)/255);
      cout << " La commande de la vanne est :" << ouverture << endl;
      sleep(5);
      }
}
}

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
  char Porte;
  while(1){
	
	scanf("%c",&Porte);
	if (Porte == 'o'){
		setPorte(true);
	} if (Porte == 'f'){
		setPorte(false);
	}
	*ptrmem = Porteouverte;
	}
}

AnalogSensorPressure :: AnalogSensorPressure(int t, float pres): Device(),val_pres(pres),temps(t){
//alea = 2;
}
void AnalogSensorPressure::run(){
  while(1){
	//alea = 2-rand()%2;
	 if(ptrmem!=NULL)
      	  *ptrmem=debit_eau;
	   val_pres = debit_eau;
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
DigitalActuatorLED::DigitalActuatorLED(int t,char c):Device(),state(LOW),temps(t){
	couleur = c;   
}

void DigitalActuatorLED::SetCouleurLED(char c){
	couleur =c;

}
char DigitalActuatorLED::getCouleurLED(){
	return couleur;

}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW)
      cout << "LED Rouge éteinte\n";
    else
      cout << "LED Rouge allumée\n";
    sleep(5);
    }
}

DigitalActuatorLEDBarre::DigitalActuatorLEDBarre(int t, int led) : Device(),state(LOW),temps(t){
    for(int i =0; i <led ; i++){
	LEDBarre.push_back(new DigitalActuatorLED(t,'R'));	
}
}
void DigitalActuatorLEDBarre::setBarreLED(char cLED){
 for (it=LEDBarre.begin();it != LEDBarre.end(); it++){
		(*it) -> SetCouleurLED(cLED);
}
}

void DigitalActuatorLEDBarre::run(){
  while(1){
	if(ptrmem!=NULL)
     	 state=*ptrmem;
    	if (state==LOW)
     	 cout << "Barre de LED éteinte\n";
        else {
	 setBarreLED('B');
	 it = LEDBarre.begin();
     	 cout << "Barre de LED allumée et de couleur "<< (*it)->getCouleurLED()<<endl;
	}
    	sleep(5);

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





