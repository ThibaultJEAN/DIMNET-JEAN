#ifndef CORE_SIMULATEUR_H
#define CORE_SIMULATEUR_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#define DELAY 3
#define TEMP 22
#define HIGH 1
#define LOW 0
#define MAX_I2C_DEVICES 4
#define I2C_BUFFER_SIZE 1024
#define MAX_IO_PIN 6

using namespace std;

enum typeio {OUTPUT, INPUT};

// exceptions gerees
enum excep {SPEED, INOUT, ADDRESS, SIZE, EMPTY};
class BoardException{
protected:
    // numero de l'exception
  int num;
public:
  BoardException(int i):num(i){}
    // recuperation du numero d'exception
    int get();
    // chaine expliquant l'exception
    string text();
};

// gestion de la liaison terminal
class Terminal {
    public :
    // fonction arduino : initialisation de la liaison
    void begin(int speed);
    // fonction arduino : affichage sur le terminal
    void println(string s);
};

// representatoin du bus I2C
class I2C{
protected:
    // zone memoire d'echange pour chaque element connecte sur le bus
  char * registre[MAX_I2C_DEVICES];
    // etat de la zone memoire d'echange pour chaque element vide ou pas
  bool vide[MAX_I2C_DEVICES];
    // outil pour eviter les conflits en lecture ecriture sur le bus
  mutex tabmutex[MAX_I2C_DEVICES];
public:
    // constructeur des différents attributs: memoire, etat et synchonisation
    I2C();
  // est ce qu il y a quelque chose a lire pour le device numero addr
    bool isEmptyRegister(int addr);
   // ecriture d'un ensemble d'octets dansle registre du device numero addr
    int write(int addr, char* bytes, int size);
   // lecture d'un ensemble d'octets dans le registre du device numero addr
    int requestFrom(int addr, char* bytes, int size);
    // recuperation de la zone memoire du registre du device numero addr
    char * getRegistre(int addr);
  // est ce que le registre du device numero addr EST VIDE
    bool* getVide(int addr);
};

// representation generique d'un capteur ou d'un actionneur numerique, analogique ou sur le bue I2C
class Device{
protected:
    // lien avec la carte pour lire/ecrire une valeur
  unsigned short *ptrmem;
    // lien avec la carte pour savoir si c'est une pin en entree ou en sortie
  enum typeio *ptrtype;
    // numero sur le bus i2c
  int i2caddr;
    // lien sur l'objet representant le bus I2C
  I2C *i2cbus;
public:
    // constructeur initialisant le minimum
    Device();
    // boucle simulant l'equipement
    virtual void run();
    // lien entre le device et la carte arduino
    void setPinMem(unsigned short* ptr,enum typeio *c);
    // lien entre le device I2C et la carte arduino
    void setI2CAddr(int addr, I2C * bus);
};

// classe representant une carte arduino
class Board{
public:
 // valeur sur les pin
  unsigned short io[MAX_IO_PIN];
    // pin d'entree ou de sortie
  enum typeio stateio[MAX_IO_PIN];
    // threads representant chaque senseur/actionneur sur le pins analogique et digitale
  thread *tabthreadpin[MAX_IO_PIN];
    // representation du bus I2C
  I2C bus;
    // representation de la liaison terminal
  Terminal Serial;
    // threads representant chaque senseur/actionneur sur le bus I2C
  thread *tabthreadbus[MAX_I2C_DEVICES];
    
// simulation de la boucle de controle arduino
    void run();
  // accroachage d'un senseur/actionneur à une pin
    void pin(int p, Device& s);
    // accroachage d'un senseur/actionneur à une adresse du bus I2C
      void i2c(int addr,Device& dev);
 // fonction arduino : configuration d'une pin en entree ou en sortie
    void pinMode(int p,enum typeio t);
  // fonction arduino : ecriture HIGH ou LOW sur une pin
    void digitalWrite(int i, int l);
    // fonction arduino : lecture digital sur une pin
    int digitalRead(int i);
     // fonction arduino : lecture analogique sur une pin
    void analogWrite(int i, int l);
   // fonction arduino : ecriture analogique sur une pin
    int analogRead(int i);
  // fonction arduino : initialisation de la carte arduino
  void setup();
    // fonction arduino : boucle de controle de la carte arduino
  void loop();
};

#endif


