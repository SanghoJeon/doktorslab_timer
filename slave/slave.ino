#include <SoftwareSerial.h>

#define RX 2
#define TX 3
#define BUTTON 4

SoftwareSerial btSerial(RX, TX);

boolean isPressed = false;

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);
  pinMode(BUTTON, INPUT);
}

void loop() {
  while (Serial.available() > 0) {
    byte buf = Serial.read();
    Serial.write(buf);
    btSerial.write(buf);
  }

  if (digitalRead(BUTTON) > 0 && isPressed) {
    btSerial.println("Off");
    isPressed = false;
  } else if (digitalRead(BUTTON) == 0 && !isPressed) {
    btSerial.println("On");
    isPressed = true;
  }
}
