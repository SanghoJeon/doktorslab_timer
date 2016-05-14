#include <SPI.h>
#include "RF24.h"
int msg[1];
RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int LED1 = 3;

void setup(void){
 Serial.begin(9600);
 radio.begin();
 radio.powerUp();
 radio.openReadingPipe(1,pipe);
 radio.startListening();
 //pinMode(LED1, OUTPUT);
 }

void loop(void){
 if (radio.available()){
   bool done = false;    
   radio.read(msg, sizeof(int));      
   Serial.println(msg[0], DEC);
   //if (msg[0] == 111){delay(10);digitalWrite(LED1, HIGH);}
   //else {digitalWrite(LED1, LOW);}
 }
}
