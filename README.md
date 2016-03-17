#Technomag_tpe
dernière mise à jour du git : jeu. 17 mars 2016
## Vous trouverez dans ce dossier
 - les termes de la liscence GPL3.0
 - les schémas au format image (.png) ["schemas_montages/"]
 - les schémas au format fritzing (.fzz) ["schemas_montages/fritzing"]
 - les codes émetteur et récepteurs avec led addressable et led normale au format arduino (.ino) ["piano_li-fi/"]

##Matériel :
- 2 cartes arduinos
- 5 à 7 boutons poussoirs
- une led adressable (type ruban à led) OU une led normale
- une led normale supplémentaire
- autant de résistances (50 à 330 ohm) que de led
- une photodiode pouvant capter la lumière visible
- un haut-parleur
- (éventuellement une résistance ou un potentiomètre pour diminuer le volume du haut-parleur)

##Instructions :
 - ouvrez le dossier "schemas_montages"
 - avec une première carte arduino, réalisez le montage du récepteur
 - avec une deuxième carte arduino réaliser le montage "emetteur_ruban_led" si vous disposez d'une led addressable, sinon, réalisez le montage "emetteur_normal".
 - revenez à la racine et ouvrez le dossier "piano_li-fi"
 - mettez le dossier "Adafruit_NeoPixel" dans le dossier "librairies" de votre logiciel Arduino
 - ouvrez les codes correspondant à vos montages et téléversez les à chaque Arduino correspondantes
 - suivez les instructions se situant au début de chaque code

## À SAVOIR
 - Vous pouvez ensuite modifier les codes et partagez vos modifications librement
