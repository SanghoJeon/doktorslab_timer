#include <SPI.h>
#include "RF24.h"
int msg[1];
RF24 radio(7,8);
const uint8_t pipe[][6] = {"1Node", "2Node"};
int LED1 = 3;

void setup(void){
 Serial.begin(9600);
 radio.begin();
 radio.powerUp();
 radio.openReadingPipe(1,pipe[0]);
 radio.openReadingPipe(2,pipe[1]);
 radio.startListening();
 //pinMode(LED1, OUTPUT);
 }

void loop(void){
  uint8_t pipeNum;
  if (radio.available(&pipeNum)){
    bool done = false;
    radio.read(msg, sizeof(int));
    Serial.print("pipe: ");
    Serial.print(pipeNum);
    Serial.print(" | msg: ");
    Serial.println(msg[0], DEC);
    //if (msg[0] == 111){delay(10);digitalWrite(LED1, HIGH);}
    //else {digitalWrite(LED1, LOW);}
  }
}
