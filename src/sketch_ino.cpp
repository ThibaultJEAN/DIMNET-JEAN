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
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
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
  static bool basculeLEDRouge = false;
  static bool basculeLEDBarre = false;
  static int commandevanne = 0;
  int i=0;
  for(i=0;i<10;i++){
    
    /*
    val_lux=analogRead(2);
    sprintf(buf,"luminosite %d",val_lux);
    Serial.println(buf);
    */
    // lecture sur la pin 1 : capteur de temperature
    val_temp = analogRead(1);
    // lecture sur la pin 3 : capteur de porte
    porte = analogRead(3);
    // lecture sur la pin 4 : capteur de debit
    debit = analogRead(4);

    if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la temperature
      if (porte != portetest){ // on teste si l'etat de la porte et different de l'etat precedent
   	sprintf(buf,"PorteOuverte %d",porte);
    	Serial.println(buf);
      	sprintf(buf,"%d",porte);
      	bus.write(3,buf,100);
      	portetest = porte;
	if (porte == true && personnedouche == false) { // si on ouvre la porte et que personne etait dans la douche alors quelqu'un rentre
		personnedouche= true;
		}else if(porte == true && personnedouche == true){ //si on ouvre la porte et que quelqu'un etait dans la douche alors la personne sort, on eteint dans le même temps les differentes LED
		personnedouche = false;
		basculeLEDRouge = false;
		basculeLEDBarre = false;
		commandevanne =0;
		}
	}
     
     if (personnedouche == true){
	
	basculeLEDRouge = true;
 	basculeLEDBarre = true;
	// on ecrit ici les differentes valeurs des capteurs de temperature, pression
	sprintf(buf,"Débit %f",debit);
    	Serial.println(buf);
      	sprintf(buf,"%f",debit);
      	bus.write(3,buf,100);
        sprintf(buf,"Température de l'eau %d",val_temp);
        Serial.println(buf);
        sprintf(buf,"%d",val_temp);
        bus.write(1,buf,100);
	sleep(3);
	if(debit > 3){
 	   commandevanne = commandevanne-10;
	 } else if (debit <3){
	   commandevanne = commandevanne+10;	
	}
	} 
    }
    cpt++;
  }
// on ecrit la valeur de la commande de debit sur le pin de sortie
  analogWrite(6,commandevanne);
// on eteint et on allume la LED Rouge de présence
  if(basculeLEDRouge == true)
    digitalWrite(0,HIGH);
  else
    digitalWrite(0,LOW);
// on eteint et on allume la barre de LED interieur  
  if(basculeLEDBarre == true)
    digitalWrite(5,HIGH);
  else
    digitalWrite(5,LOW);
  
}


