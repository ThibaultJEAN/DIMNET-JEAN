
#include "mydevices.h"

using namespace std;

int luminosite_environnement = LUM_ENVIRONNEMENT;
float debit_eau = DEBIT_EAU_INIT;
int temperature_eau = TEMP_VOULU;

// classe pour la sortie sur la regulation du debit
AnalogActuatorElectrovanne::AnalogActuatorElectrovanne(int t): Device(),temps(t){
	ouverture = OUVERTURE_INIT;
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
      debit_eau = (int)((DEBIT_EAU_MAX*ouverture)/OUVERTURE_ELECTROVANNE_MAX);
      cout << "La commande de la vanne est :" << ouverture << endl;
      sleep(temps);
      }
}
}
// classe pour la detection de l'ouverture et fermeture de la porte
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
// classe sur le capteur de debit
AnalogSensorPressure :: AnalogSensorPressure(int t, float pres): Device(),val_pres(pres),temps(t){
}
void AnalogSensorPressure::run(){
  while(1){
	 if(ptrmem!=NULL)
      	  *ptrmem=debit_eau;
	   val_pres = debit_eau;
    	sleep(temps);
  }

}

//classe AnalogSensorLuminosity
AnalogSensorLuminosity::AnalogSensorLuminosity(int t,int l): Device(),val_lux(l),temps(t){
alea = ALEA_LUM;
}

void AnalogSensorLuminosity::run(){
  while(1){
    alea=ALEA_LUM-rand()%ALEA_LUM;
    if(ptrmem!=NULL)
      *ptrmem=val_lux+alea;
    sleep(temps);
  }
}

//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d,int t):Device(),val_temp(t),temps(d){
  alea=ALEA_TEMP;
}

void AnalogSensorTemperature::run(){
  while(1){
    alea=ALEA_TEMP-alea;
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
    sleep(temps);
    }
}
// classe DigitalActuatorLEDBarre, classe pour la barre de LED interieure
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
    	sleep(temps);

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
    sleep(DELAY);
    }
}





