/*  #######################################
 *  # Code ÉMETTEUR Li-fi musique Arduino #
 *  #######################################
 *  
 *  connectez au moins 5 boutons poussoirs comme ceci :    
 *
 *                     pin  Gnd
 *                       | |            ________________________
 *                       ---           | la résistance pull-off |
 *                      | O |          |est activée. On a donc  |
 *                       ---           |pas besoin de connecter |
 *                       | |           |le bouton au +5V        |
 *                                     |________________________|
 *                                     
 *       => Par défaut, connectez 5 boutons sur les pins 4,5,6,7,8.
 *       
 *       => N'oubliez pas, si vous mettez plus de 5 boutons, de
 *       de configurer "nb_bouton" et de déclarer les pins dans 
 *       "bout[]".
 *  
 *  connectez la led du ruban à led :
 *    -Le + : sur le +5V
 *    -Le - : sur le Gnd
 *    -le data (celui du milieu) : sur la pin 9
 *    => vous pouvez modifiez le numéro de la pin du data
 *    en remplaçant le 9 de "#define PIN 9" par le numéro souhaité
 *    
 *  Téléversez le code sur votre arduino Uno.
 *    =>attendez le "bip" du récepteur
 *    =>mettez sous tention l'émetteur
 *    =>La led s'allume en rouge :
 *      sélectionner l'intensité : plus le numéro du bouton est petit, plus c'est faible
 *    =>La led s'allume en bleu :
 *      attendre
 *    =>La led s'allume en vert :
 *      sélectionnez la vitesse de clignottement :
 *        __________________________
 *       |bouton n°  |1 |2 |3 |4 |5 |
 *       |___________|__|__|__|__|__|
 *       |vitesse(ms)|70|50|30|20|10|
 *       |___________|__|__|__|__|__|
 *  
 *    => placez la led devant la photodiode pendant un certain temps.
 *        - si vous entendez un bip grave et long, c'est que vous n'êtes pas bien placé, ou qu'il y a trop de lumière
 *        - si vous entendez un petit bip court, vous pouvez éloigner la led du photorécepteur, et appuyer sur les boutons pour produire des notes
 *        
 *  Pour redémarrer le programme, appuyez sur reset (le bouton à côté du port USB sur l'arduino)
 * 
 */



//nécessaire à l'utilisation des leds//
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 9
#define NUMPIXELS 1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//déclaration des variables
int nb_bouton = 5;       //nombre de boutons
int bout[] = {4,5,6,7,8}; //numéro des pins des boutons
int state = 0;            //
int temp = 30;            //delai entre led allumée et led éteinte
int sortir = false;       //utile dans le setup()
int bout_choix = 0;       //utile dans le setup()
int intense = 100;         //intensité lumineuse

void setup() {
  pixels.begin(); //initialisation de la librairie NeoPixel
  
  for (int i=0; i<nb_bouton; i++){       //déclarer pour chaque bouton
    pinMode(bout[i], INPUT);     //un pin en tant que sortie
    digitalWrite(bout[i], HIGH); //activer la résistance pull-up
  }
  
  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color prends une couleur au format (rouge, vert, bleu) comprit entre (0,0,0) et (255,255,255)
    pixels.setPixelColor(i, pixels.Color(5,0,0));
  }
  pixels.show();

  // ####### Régler l'intensité ####### //
  sortir = false;
  while (sortir == false){         
    for (int a=0; a<nb_bouton; a++){
      if (digitalRead(bout[a]) == LOW){
        sortir = true;
        bout_choix = a;
        intense = map(nb_bouton-bout_choix, 1, nb_bouton, 20, 255);
      }// Fin du if
    } //Fin du for
  } //Fin du while

  
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,5));
  }
  pixels.show();

    delay(1000); //pour ne pas perturber les deux event

  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,5,0));
  }
  pixels.show();

  // ####### Régler la vitesse ####### //
  sortir = false;
  while (sortir == false){         
    for (int a=0; a<nb_bouton; a++){
      if (digitalRead(bout[a]) == LOW){
        sortir = true;
        bout_choix = a;
/*      on regarde quel bouton a été choisi      */
        switch (bout_choix){
          case 0:
            temp = 70;
            break;
          case 1:
            temp = 50;
            break;
          case 2:
            temp = 30;
            break;
          case 3:
            temp = 20;
            break;
          case 4:
            temp = 10;
            break;
        }
      }// Fin du if
    } //Fin du for
  } //Fin du while
} //Fin void setup()

void loop() {
  send0();
  for (int a=0; a<nb_bouton; a++){
    if (digitalRead(bout[a]) == LOW){
      blinker(a);
    }
  }
}

void blinker(int num){
  switch (num){
    case 0:
      envoyer("01000011"); // C
      break;
    case 1:
      envoyer("01000100"); // D
      break;
    case 2:
      envoyer("01000101"); // E
      break;
    case 3:
      envoyer("01000110"); // F
      break;
    case 4:
      envoyer("01000111"); // G
      break;
  }
}

void envoyer(String carac){
  send1();
  send0();
  for(int i=0; i<8; i++){
    if (carac[i] == '1'){
      send1();
    }else{
      send0();
    }
  }
}

void send0 (){
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }
  pixels.show();
  delay(temp);

  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(intense,intense,intense));
    }
  pixels.show();
  delay(temp);
}

void send1 (){
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(intense,intense,intense));
    }
  pixels.show();
  delay(temp);

  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }
  pixels.show();
  delay(temp);
}
