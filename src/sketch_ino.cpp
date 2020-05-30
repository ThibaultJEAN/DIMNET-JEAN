#include <unistd.h>
#include "core_simulation.h"



// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(BAUD_RATE);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(PIN_CAPTEUR_LUM,INPUT);
  pinMode(PIN_CAPTEUR_TEMP,INPUT);
  pinMode(PIN_CAPTEUR_PORTE,INPUT);
  pinMode(PIN_CAPTEUR_PRESSION,INPUT);
  pinMode(PIN_LED,OUTPUT);
  pinMode(PIN_LEDBARRE,OUTPUT);
  pinMode(PIN_ACTIONNEUR_ELECTROVANNE,OUTPUT);
}

// la boucle de controle arduino
void Board::loop(){
  char buf[CARAC_MAX];
  int val_temp;
  //int val_lux;
  int debit;
  bool porte = false;
  static bool portetest = false;
  static bool personnedouche = false;
  static int cpt=0;
  static bool basculeLEDRouge = false;
  static bool basculeLEDBarre = false;
  static int commandevanne = 0;
  int i=0;
  for(i=0;i<NB_TOURS_BOUCLE_FOR;i++){
    
    /*
    val_lux=analogRead(PIN_CAPTEUR_LUM);
    sprintf(buf,"luminosite %d",val_lux);
    Serial.println(buf);
    */
    // lecture sur la pin 1 : capteur de temperature
    val_temp = analogRead(PIN_CAPTEUR_TEMP);
    // lecture sur la pin 3 : capteur de porte
    porte = analogRead(PIN_CAPTEUR_PORTE);
    // lecture sur la pin 4 : capteur de debit
    debit = analogRead(PIN_CAPTEUR_PRESSION);

    if(cpt%COMPTEUR_BOUCLE_FOR==0){
        // tous les 5 fois on affiche sur l ecran la temperature
      if (porte != portetest){ // on teste si l'etat de la porte et different de l'etat precedent
   	sprintf(buf,"PorteOuverte %d",porte);
    	Serial.println(buf);
      	sprintf(buf,"%d",porte);
      	bus.write(PIN_CAPTEUR_PORTE,buf,CARAC_MAX);
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
	sprintf(buf,"Débit %d",debit);
    	Serial.println(buf);
      	sprintf(buf,"%d",debit);
      	bus.write(PIN_CAPTEUR_PRESSION,buf,CARAC_MAX);
        sprintf(buf,"Température de l'eau %d",val_temp);
        Serial.println(buf);
        sprintf(buf,"%d",val_temp);
        bus.write(PIN_CAPTEUR_TEMP,buf,CARAC_MAX);
	sleep(DELAY);
	if(debit > DEBIT_VOULU){
 	   commandevanne = commandevanne-VANNE;
	 } else if (debit < DEBIT_VOULU){
	   commandevanne = commandevanne+VANNE;	
	}
	} 
    }
    cpt++;
  }
// on ecrit la valeur de la commande de debit sur le pin de sortie
  analogWrite(PIN_ACTIONNEUR_ELECTROVANNE,commandevanne);
// on eteint et on allume la LED Rouge de présence
  if(basculeLEDRouge == true)
    digitalWrite(PIN_LED,HIGH);
  else
    digitalWrite(PIN_LED,LOW);
// on eteint et on allume la barre de LED interieur  
  if(basculeLEDBarre == true)
    digitalWrite(PIN_LEDBARRE,HIGH);
  else
    digitalWrite(PIN_LEDBARRE,LOW);
  
}


