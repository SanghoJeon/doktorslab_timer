#include  <SPI.h>
#include "RF24.h"

/* radio */
#define PIPE_NUM 6  // there are 6 pipes in one channel
int msg[2];
RF24 radio(9,10);
#define CHANNEL 1   // Change this to set rf channel
#define PIPE 1      // Change this to set rf pipe
const uint8_t pipe[PIPE_NUM][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

/* switches */
#define SWITCH_NUM 3
const char sw[SWITCH_NUM] = {2, 3, 4};
char isPressed[SWITCH_NUM];


void setup(void) {
  Serial.begin(9600);
  radio.begin();
  radio.powerUp();
  radio.setChannel(CHANNEL);
  radio.openWritingPipe(pipe[PIPE]);

  for(int i=0; i<SWITCH_NUM; i++) {
    pinMode(sw[i], INPUT_PULLUP);
  }
}

void loop(void) {
  byte buf;
  for(int i=0; i<SWITCH_NUM; i++) {
    buf = digitalRead(sw[i]);
    
    if (buf == LOW && isPressed[i] == 0) {
      msg[0] = 'b';
      msg[1] = '0' + i;
      radio.write(msg, sizeof(msg));
      Serial.print(msg[0]);
      Serial.println(msg[1]);
      isPressed[i] = 1;
      delay(50);  // to prevent chattering
    } else if (buf == HIGH && isPressed[i] == 1) {
      isPressed[i] = 0;
      delay(50);  // to prevent chattering
    }
  }
}
