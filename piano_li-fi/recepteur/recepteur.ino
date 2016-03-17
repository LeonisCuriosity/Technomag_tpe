 /*  ########################################
 *   # Code RÉCEPTEUR Li-fi musique Arduino #
 *   ########################################
 *   
 *   connectez une photodiode comme ceci :
 *           
 *               -   +(plus grande patte)
 *      Gnd ______|/|_____ pin A0
 *                |\|
 *  
 *   connectez le haut parleur comme ceci 
 *   
 *                -              +(indiqué sur le haut-parleur)
 *        Gnd -----(haut-parleur)------ pin 12
 *    
 *       => vous pouvez ajoutez une petite résistance ou un 
 *       potentiomètre pour éviter que le son ne soit trop fort.
 *       
 *   Téléversez le code sur votre arduino Uno.
 *     => veillez à ce que l'émetteur soit éteint
 *     => lorsque le "bip" est émit, vous pouvez allumer l'émetteur
 *     => suivez les instruction dans le code de l'émetteur
 *  
 */
 
 #include "notes.h"
 #include "lettres.h"

//déclaration des entrées/sorties
int buzz = 12;
int led = 7;

//variables utiles à setMoy()
int moy=0;
int proba_calibration = 150; //modifier la valeur du tableau "values[]"
unsigned int values[150];

//variables utiles à calibration()
unsigned long temps1 = 0, temps2 = 0; //variables contenant le temps en millisec ou en microsec depuis le lancement de l'arduino
const int proba_tmp_unit_moy = 50;
unsigned long tmp_unit_moy[50]; //tableau servant à faire la moyenne du temps entre deux clignotement
unsigned long tmp_unit = 0; //unité de temps correspondant à une variation du codage manchester


//constantes
const int seuil = 3; //seuil de détection de la led
const int sensib_temps = 10;
const int vitesse = 0; //0: millis; 1: micros

//variables
unsigned long dif_moy = 0; //différence par rapport à la moyenne
int sortir = false;
int detection = 0; //récupère la val de la lumière
int test_erreur = true;
char Bit = '0';
String octet = "00000000";

void setup() {
  pinMode(led,OUTPUT);
  setMoy();
  calibration();
  init_detect();
}

void loop() {
  Bit = detect();
  if (Bit == '1'){
    Bit = detect();
    if (Bit == '0'){
      for (int b = 0; b<8; b++){
        octet[b] = detect();
      }
      
      if (octet == C){
        buzzSignal(500, Do);
      } else if (octet == D){
        buzzSignal(500, Re);
      } else if (octet == E){
        buzzSignal(500, Mi);
       } else if (octet == F){
        buzzSignal(500, Fa);
       } else if (octet == G){
        buzzSignal(500, Sol);
       } else if (octet == A){
        buzzSignal(500, La);
       } else if (octet == B){
        buzzSignal(500, Si);
       }
       
    }
  }
}

void setMoy(){
//moyenne de la luminosité
  for (int i=0; i<proba_calibration; i++){
    values[i]=analogRead(A0);
  }
  int somme = 0;
  for (int i=0; i<proba_calibration; i++){
    somme += values[i];
  }
  moy = somme/proba_calibration;
  buzzSignal(200, La);
}



void calibration(){
//moyenne du temps
  buzzSignal(200, Fa);
  int ref=test_calib();
  buzzSignal(200, Sol);
  
  for (int i=0; i<proba_tmp_unit_moy; i++){
    tmp_unit_moy[i]=test_calib();
    if(tmp_unit_moy[i] > 6){
      if (tmp_unit_moy[i] >= tmp_unit_moy[0] + 4 || tmp_unit_moy[i] <= tmp_unit_moy[0] - 4){ //si trop dif de la ref
      i=-1;
      buzzSignal(10, Do);
      digitalWrite(led, HIGH);
      }
      digitalWrite(led, LOW);
    } else {
      i-=1;
      digitalWrite(led, HIGH);
      }
  }//END FOR
  
  int somme = 0;
  for (int i=0; i<proba_tmp_unit_moy; i++){
    somme += tmp_unit_moy[i];
  }
  tmp_unit = somme/proba_tmp_unit_moy;

  buzzSignal(200, La);
  
}

unsigned long test_calib(){
  while(analogRead(A0)<moy+seuil){
    //attend
  }
  
  if (vitesse == 0){ //test du mode (haute/basse précision)
    temps1 = millis(); //basse précision
  } else {
    temps1 = micros(); //haute précision
  }
// #####################################  
  while(analogRead(A0)>moy+seuil){
      //attend
    }
    
  if (vitesse == 0){ //test du mode (haute/basse précision)
      temps2 = millis(); //basse précision
   } else {
      temps2 = micros(); //haute précision
   }
   return(temps2-temps1);
}



void buzzSignal(int duree, int note){
  tone(buzz, note, duree);
}

int init_detect(){
  while(sortir == false){
    detection = analogRead(A0);
    if(detection > moy+seuil){
      while (detection > moy+seuil){
        detection = analogRead(A0);
      }
      sortir = true;
      buzzSignal(200, Si);
    }
  }
}

char detect(){
  detection = analogRead(A0);

//#### détection d'un 0 ####//
  test_erreur = true;
  if (detection <= moy+seuil){
    delay(tmp_unit-2);
    
    for (int z=0; z<7; z++){
      if (detection > moy+seuil){
        test_erreur = false;
        break;
      } else {
        detection = analogRead(A0);
        delay(1);
      }
    }
    
    delay(tmp_unit+1);
    
    if (test_erreur == true){
      //erreur();
      return('1');
    }else{
      return('0');
    }
  }//Fin de la détection d'un 0

//#### détection d'un 1 ####//
  else if (detection > moy+seuil){
    delay(tmp_unit-2);
    for (int z=0; z<7; z++){
      if (detection <= moy+seuil){
        test_erreur = false;
        break;
        detection = analogRead(A0);
        delay(1);
      }
    }
    
    delay(tmp_unit+1);
    
    if (test_erreur == true){
      //erreur();
      return('1');
    }else{
      return('0');
    }
  }//Fin de la détection d'un 1
  
}

void erreur(){
  buzzSignal(50, Do);
}

