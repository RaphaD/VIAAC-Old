const unsigned LEDS(3);
const unsigned FISH(4);
const int MAX(11);
char res('A');

void setup(){
  Serial.begin(9600);
  pinMode(LEDS,OUTPUT);
  pinMode(FISH,OUTPUT);
  digitalWrite(FISH,HIGH);
}

void loop(){
  if (Serial.available()>0){
    res=Serial.read();
  }
  switch(res){
    case '0':
      analogWrite(LEDS,0);
      break;
    case '1':
      analogWrite(LEDS,25);
      break;
    case '2':
      analogWrite(LEDS,50);
      break;
    case '3':
      analogWrite(LEDS,75);
      break;
    case '4':
      analogWrite(LEDS,100);
      break;
    case '5':
      analogWrite(LEDS,125);
      break;
    case '6':
      analogWrite(LEDS,150);
      break;
    case '7':
      analogWrite(LEDS,175);
      break;
    case '8':
      analogWrite(LEDS,200);
      break;
    case '9':
      analogWrite(LEDS,225);
      break;
    case 'A':
      analogWrite(LEDS,255);
      break;
    }
}
