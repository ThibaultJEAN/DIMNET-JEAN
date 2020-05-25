#include <unistd.h>
#include "core_simulation.h"

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(2,INPUT);
  pinMode(1,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(0,OUTPUT);
}

// la boucle de controle arduino
void Board::loop(){
  char buf[100];
  int val_temp;
  //int val_lux;
  float debit;
  bool porte = false;
  static bool portetest = false;
  static bool personnedouche = false;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  for(i=0;i<10;i++){
    // lecture sur la pin 1 : capteur de temperature
    /*val=analogRead(1);
    sprintf(buf,"temperature %d",val);
    Serial.println(buf);
    val_lux=analogRead(2);
    sprintf(buf,"luminosite %d",val_lux);
    Serial.println(buf);
    porte = analogRead(3);
    sprintf(buf,"PorteOuverte %d",porte);
    Serial.println(buf);*/
    val_temp = analogRead(1);
    porte = analogRead(3);
    debit = analogRead(4);

    if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la temperature
      
      /*sprintf(buf,"%d",val);
      bus.write(1,buf,100);
      sprintf(buf,"%d",val_lux);
      bus.write(2,buf,100);*/
      if (porte != portetest){
   	sprintf(buf,"PorteOuverte %d",porte);
    	Serial.println(buf);
      	sprintf(buf,"%d",porte);
      	bus.write(3,buf,100);
      	portetest = porte;
	if (porte == true && personnedouche == false) {
		personnedouche= true;
		}else if(porte == true && personnedouche == true){
		personnedouche = false;
		}
	}
     
     if (personnedouche == true){
        
	sprintf(buf,"Débit %f",debit);
    	Serial.println(buf);
      	sprintf(buf,"%f",debit);
      	bus.write(3,buf,100);
        sprintf(buf,"Température de l'eau %d",val_temp);
        Serial.println(buf);
        sprintf(buf,"%d",val_temp);
        bus.write(1,buf,100);
	sleep(3);
	} 
    }
    cpt++;
      //sleep(0.01);
  }
  
// on eteint et on allume la LED
  if(bascule)
    digitalWrite(0,HIGH);
  else
    digitalWrite(0,LOW);
  bascule=1-bascule;
  
}


