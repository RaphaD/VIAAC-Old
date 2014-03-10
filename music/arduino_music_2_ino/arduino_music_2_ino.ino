// I/O Devices
const unsigned LEDS(3);
const unsigned RED_LED(4);
const unsigned GREEN_LED(8);
const unsigned BLUE_LED(12);

// Buffers
char res('A'); // main buffer
char led_blink('A'); // led blinking buffer
char color('N'); // led color buffer

void red_handler();
void green_handler();
void blue_handler();
void yellow_handler();
void lightBlue_handler();
void purple_handler();
void white_handler();
void none_handler();

void setup(){
  Serial.begin(9600);
  pinMode(LEDS,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);

  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(BLUE_LED,HIGH);
}

void loop(){
  if (Serial.available()>0){
    res=Serial.read();
    if(res=='0' || res=='1' || res=='2' || res=='3' || res=='4' ||
    res=='5' || res=='6' || res=='7' || res=='8' || res=='9' || 
    res=='A'){
      led_blink=res;
    }else if(res=='R' || res=='G' || res=='B' || res=='Y' || 
    res=='L' || res=='P' || res=='W' || res=='N'){
      color=res;
    }
  }
  switch(led_blink){
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
  switch(color){
    case 'R':
      red_handler();
      break;
    case 'G':
      green_handler();
      break;
    case 'B':
      blue_handler();
      break;
    case 'Y':
      yellow_handler();
      break;
    case 'L':
      lightBlue_handler();
      break;
    case 'P':
      purple_handler();
      break;
    case 'W':
      white_handler();
      break;
    case 'N':
      none_handler();
      break;
  }
}

void red_handler(){
  if(digitalRead(RED_LED)==HIGH)
    digitalWrite(RED_LED,LOW);
  if(digitalRead(GREEN_LED)==LOW)
    digitalWrite(GREEN_LED,HIGH);
  if(digitalRead(BLUE_LED)==LOW)
    digitalWrite(BLUE_LED,HIGH);
}

void green_handler(){
  if(digitalRead(RED_LED)==LOW)
    digitalWrite(RED_LED,HIGH);
  if(digitalRead(GREEN_LED)==HIGH)
    digitalWrite(GREEN_LED,LOW);
  if(digitalRead(BLUE_LED)==LOW)
    digitalWrite(BLUE_LED,HIGH);  
}

void blue_handler(){
  if(digitalRead(RED_LED)==LOW)
    digitalWrite(RED_LED,HIGH);
  if(digitalRead(GREEN_LED)==LOW)
    digitalWrite(GREEN_LED,HIGH);
  if(digitalRead(BLUE_LED)==HIGH)
    digitalWrite(BLUE_LED,LOW);
}

void yellow_handler(){
  if(digitalRead(RED_LED)==HIGH)
    digitalWrite(RED_LED,LOW);
  if(digitalRead(GREEN_LED)==HIGH)
    digitalWrite(GREEN_LED,LOW);
  if(digitalRead(BLUE_LED)==LOW)
    digitalWrite(BLUE_LED,HIGH);
}

void lightBlue_handler(){
  if(digitalRead(RED_LED)==LOW)
    digitalWrite(RED_LED,HIGH);
  if(digitalRead(GREEN_LED)==HIGH)
    digitalWrite(GREEN_LED,LOW);
  if(digitalRead(BLUE_LED)==HIGH)
    digitalWrite(BLUE_LED,LOW);
}

void purple_handler(){
  if(digitalRead(RED_LED)==HIGH)
    digitalWrite(RED_LED,LOW);
  if(digitalRead(GREEN_LED)==LOW)
    digitalWrite(GREEN_LED,HIGH);
  if(digitalRead(BLUE_LED)==HIGH)
    digitalWrite(BLUE_LED,LOW);
}

void white_handler(){
  if(digitalRead(RED_LED)==HIGH)
    digitalWrite(RED_LED,LOW);
  if(digitalRead(GREEN_LED)==HIGH)
    digitalWrite(GREEN_LED,LOW);
  if(digitalRead(BLUE_LED)==HIGH)
    digitalWrite(BLUE_LED,LOW);
}

void none_handler(){
  if(digitalRead(RED_LED)==LOW)
    digitalWrite(RED_LED,HIGH);
  if(digitalRead(GREEN_LED)==LOW)
    digitalWrite(GREEN_LED,HIGH);
  if(digitalRead(BLUE_LED)==LOW)
    digitalWrite(BLUE_LED,HIGH);
}
