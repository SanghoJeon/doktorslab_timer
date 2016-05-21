#include <SPI.h>
#include "RF24.h"
int msg[1];
RF24 radio1(7,8);
RF24 radio2(5,6);
const uint8_t pipe[][6] = {"1Node", "2Node"};
int LED1 = 3;

void setup(void){
 Serial.begin(9600);
 radio1.begin();
 radio1.powerUp();
 radio2.begin();
 radio2.powerUp();
 radio1.setChannel(1);
 radio2.setChannel(2);
 radio1.openReadingPipe(1,pipe[1]);
 radio2.openReadingPipe(1,pipe[1]);
 radio1.startListening();
 radio2.startListening();
 //pinMode(LED1, OUTPUT);
 }

void loop(void){
  uint8_t pipeNum;
  if (radio1.available(&pipeNum)){
    bool done = false;
    radio1.read(msg, sizeof(int));
    Serial.print("Radio1 | ");
    Serial.print("pipe: ");
    Serial.print(pipeNum);
    Serial.print(" | msg: ");
    Serial.println(msg[0], DEC);
    //if (msg[0] == 111){delay(10);digitalWrite(LED1, HIGH);}
    //else {digitalWrite(LED1, LOW);}
  }
  if (radio2.available(&pipeNum)){
    bool done = false;
    radio2.read(msg, sizeof(int));
    Serial.print("Radio2 | ");
    Serial.print("pipe: ");
    Serial.print(pipeNum);
    Serial.print(" | msg: ");
    Serial.println(msg[0], DEC);
    //if (msg[0] == 111){delay(10);digitalWrite(LED1, HIGH);}
    //else {digitalWrite(LED1, LOW);}
  }
}
