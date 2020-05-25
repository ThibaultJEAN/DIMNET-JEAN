#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include "core_simulation.h"

extern int luminosite_environnement;
extern float debit_eau;
extern int temperature_eau;

class AnalogSensorPorte : public Device {
private : 
	bool Porteouverte;
public :
	AnalogSensorPorte(bool Porte);
	bool getPorte();
	void setPorte(bool porte);
	virtual void run();
};

class AnalogSensorPressure : public Device {
private : 
	float alea;
	float val_pres;
	int temps;
public : 
	AnalogSensorPressure(int t, float pres);
	virtual void run();
};

class AnalogSensorLuminosity : public Device {
private : 
	int alea;
	int val_lux;
	int temps;

public : 
	AnalogSensorLuminosity(int t, int l);
	virtual void run();
};
// exemple de capteur analogique de temperature, ne pas oublier d'heriter de Device
class AnalogSensorTemperature: public Device {
private:
  // fait osciller la valeur du cpateur de 1
  int alea;
  // valeur de temperature mesuree
  int val_temp;
  // temps entre 2 prises de valeurs
  int temps;
  
public:
  //constructeur ne pas oublier d'initialiser la classe mere
  AnalogSensorTemperature(int d,int  t);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

// exemple d'actionneur digital : une led, ne pas oublier d'heriter de Device
class DigitalActuatorLED: public Device {
private:
  // etat de la LED
  int state;
  // temps entre 2 affichage de l etat de la led
  int temps;
  char couleur;
  
public:
    // initialisation du temps de rafraichiisement
  DigitalActuatorLED(int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};

// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorScreen : public Device{
protected:
    // memorise l'affichage de l'ecran
  char buf[I2C_BUFFER_SIZE];
  
public:
  // constructeur
  I2CActuatorScreen ();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

#endif
