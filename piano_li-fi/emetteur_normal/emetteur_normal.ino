int led = 12;
int bout[] = {4,5,6,7,8};
int state = 0;
int temp = 30;
int sortir = false;
int bout_choix = 0;

void setup() {
  pinMode(led, OUTPUT);
  for (int i=0; i<5; i++){
    pinMode(bout[i], INPUT);
    digitalWrite(bout[i], HIGH);
  }
  
  while (sort == false){
    for (int a=0; a<5; a++){
      if (digitalRead(bout[a]) == LOW){
        bout_choix = a;
        break;
      }
    }
    
  }
}

void loop() {
  send0();
  for (int a=0; a<5; a++){
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
  digitalWrite(led, LOW);
  delay(temp);
  digitalWrite(led, HIGH);
  delay(temp);
}

void send1 (){
  digitalWrite(led, HIGH);
  delay(temp);
  digitalWrite(led, LOW);
  delay(temp);
}
