#include <SPI.h>
#include "RF24.h"
#include <SoftwareSerial.h> // for bluetooth

/* radio */
#define PIPE_NUM 6
int msg[2];
RF24 radio1(7,8);
RF24 radio2(9,10);
const uint8_t pipe[PIPE_NUM][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};
int LED1 = 3;

/* bluetooth */
#define BT_NUM 2
SoftwareSerial bt[BT_NUM] = {SoftwareSerial(4, 3), SoftwareSerial(6, 5)};

void setup(void){
  radio1.begin();
  radio2.begin();
  radio1.powerUp();
  radio2.powerUp();
  radio1.setChannel(1);
  radio2.setChannel(2);
  for(int i=0; i<PIPE_NUM; i++) {
   radio1.openReadingPipe(i,pipe[i]);
   radio2.openReadingPipe(i,pipe[i]);
  }
  radio1.startListening();
  radio2.startListening();
 
  Serial.begin(9600);
  Serial.println("Start Serial");
  for(int i=0; i<BT_NUM; i++) {
   bt[i].begin(9600);
  }
}

void loop(void){
  uint8_t pipe;
  if (radio1.available(&pipe)){
    radio1.read(msg, sizeof(msg));
    processMessage(0, pipe, msg);
  }
  if (radio2.available(&pipe)) {
    radio2.read(msg, sizeof(msg));
    processMessage(1, pipe, msg);
  }
}

void processMessage(int radio, uint8_t pipe, int* msg) {
  int id = radio * PIPE_NUM + pipe;

  for(int i=0; i<BT_NUM; i++) {
    bt[i].print(id, DEC);
    bt[i].print("|");
    bt[i].write(msg[0]);
    bt[i].write(msg[1]);
    bt[i].println("");
  }

  Serial.print(id, DEC);
  Serial.print("|");
  Serial.println(msg[1]);
}

