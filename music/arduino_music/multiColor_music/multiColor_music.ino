const int LIGHT(2);
const int R_LED(3);
const int G_LED(4);
const int B_LED(5);

void changeColor(int pin);
void handleColor(char res);

void wait(const int led,int up,int down);
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
    pinMode(R_LED,OUTPUT);
    pinMode(G_LED,OUTPUT);
    pinMode(B_LED,OUTPUT);

    Serial.begin(9600);
}

void loop(){
    if(Serial.available()>0){
        res=Serial.read();
        if (res==RED || res==GREEN || res==BLUE ){
            changeColor(res);
        }else{
            long int time(milis());
            while(milis()-time<MAX+2){
                switch(res){
                    case '0':
                        wait_0(RED_LED); break;
                    case '1':
                        wait_1(RED_LED); break;
                    case '2':
                        wait_2(RED_LED); break;
                    case '3':
                        wait_3(RED_LED); break;
                    case '4':
                        wait_4(RED_LED); break;
                    case '5':
                        wait_5(RED_LED); break;
                    case '6':
                        wait_6(RED_LED); break;
                    case '7':
                        wait_7(RED_LED); break;
                    case '8':
                        wait_8(RED_LED); break;
                    case '9':
                        wait_9(RED_LED); break;
                    case 'A':
                        wait_10(RED_LED); break;
                }
            }
        }
   }
}


