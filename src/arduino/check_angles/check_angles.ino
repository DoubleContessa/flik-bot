/*
    === Arduino Ant Robot / Hexapod ===
    by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>
#include <SoftwareSerial.h>

// Create servo object
Servo myservo;

int pos = 0;    // variable to store the servo position
int myservo_angle = 0;

void setup() {
  Serial.begin(38400);
  delay(20);
  
  // Head
  myservo.attach(36, 600, 2400);
  // servo.attach(36);  // TO TEST
  delay(1000);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    myservo_angle = myservo.read();
    Serial.println(myservo_angle);
  }
}
