const int RED_LED(2);
const int LIGHT(3);
const int MAX(11);
char res;

void wait_0(const int led);
void wait_1(const int led);
void wait_2(const int led);
void wait_3(const int led);
void wait_4(const int led);
void wait_5(const int led);
void wait_6(const int led);
void wait_7(const int led);
void wait_8(const int led);
void wait_9(const int led);
void wait_10(const int led);

void setup(){
   pinMode(RED_LED, OUTPUT);
   pinMode(LIGHT, OUTPUT);
   Serial.begin(9600);
   delay(200);
}

void loop(){
  if (Serial.available()>0){
    res=Serial.read();
    long time(millis());    
    while (millis()-time<MAX+2){
      switch(res){
      case '0':
        wait_0(RED_LED);
        break;
      case '1':
        wait_1(RED_LED);
        break;
      case '2':
        wait_2(RED_LED);
        break;
      case '3':
        wait_3(RED_LED);
        break;
      case '4':
        wait_4(RED_LED);
        break;
      case '5':
        wait_5(RED_LED);
        break;
      case '6':
        wait_6(RED_LED);
        break;
      case '7':
        wait_7(RED_LED);
        break;
      case '8':
        wait_8(RED_LED);
        break;
      case '9':
        wait_9(RED_LED);
        break;
      case 'A':
        wait_10(RED_LED);
        break;
      }
    }
  }else{
    wait_0(RED_LED);
  }
}

void wait(const int led,int up,int down){
  long time=millis();
  digitalWrite(led,LOW);
  delay(up);
  digitalWrite(led,HIGH);
  delay(down);
}

void wait_0(const int led){
  wait(RED_LED,MAX,0);
}

void wait_1(const int led){
  wait(RED_LED,MAX-1,2);
}

void wait_2(const int led){
  wait(RED_LED,MAX-3,4);
}

void wait_3(const int led){
  wait(RED_LED,MAX-4,6);
}

void wait_4(const int led){
  wait(RED_LED,MAX-5,7);
}

void wait_5(const int led){
  wait(RED_LED,MAX-6,8);
}

void wait_6(const int led){
  wait(RED_LED,MAX-7,9);
}

void wait_7(const int led){
  wait(RED_LED,MAX-8,11);
}

void wait_8(const int led){
  wait(RED_LED,1,MAX-7);
}

void wait_9(const int led){
  wait(RED_LED,1,MAX-6);
}

void wait_10(const int led){
  wait(RED_LED,0,MAX);
}
