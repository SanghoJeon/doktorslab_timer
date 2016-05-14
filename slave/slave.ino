#include  <SPI.h>
#include "RF24.h"

int msg[1];
RF24 radio(7,8);
#define CHANNEL 1
const uint8_t pipe[][6] = {"1Node", "2Node"};
int SW1 = 7;

void setup(void) {
  //Serial.begin(9600);
  radio.begin();
  radio.powerUp();
  //Serial.println(radio.getDataRate(), DEC);
  radio.openWritingPipe(pipe[CHANNEL]);
}

void loop(void) {
  //if (digitalRead(SW1) == HIGH){
  msg[0] = 111;
  radio.write(msg, sizeof(int));
  
  delay(1000);
  //}
}
