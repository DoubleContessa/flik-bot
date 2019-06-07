/*
    === Arduino Ant Robot / Hexapod ===
    by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>
#include <SoftwareSerial.h>

// Create servo object
Servo s15;
Servo s14;
Servo s13;

Servo s5;
Servo s6;

Servo s18;
Servo s17;
Servo s16;

Servo s21;
Servo s20;
Servo s19;

Servo s24;
Servo s23;
Servo s22;

Servo s7;
Servo s8;
Servo s9;

Servo s10;
Servo s11;
Servo s12;

Servo s1;
Servo s2;
Servo s4;

int pos = 0;    // variable to store the servo position
int myservo_angle = 0;

void setup() {
  Serial.begin(38400);
  delay(20);
  
  // Head
  s15.attach(36, 600, 2400);
  s14.attach(35, 600, 2400);
  //s13.attach(34, 600, 2400); //grip
  // Tail
  s5.attach(26, 600, 2400); // Tail

  // Leg 1
  s18.attach(39, 600, 2400);
  s17.attach(38, 600, 2400);
  s16.attach(37, 600, 2400); //rot

   // Leg 2
  s21.attach(42, 600, 2400);
  s20.attach(41, 600, 2400);
  s19.attach(40, 600, 2400); //rot

    // Leg 3
  s24.attach(45, 600, 2400);
  s23.attach(44, 600, 2400);
  s22.attach(43, 600, 2400); //rot

  // Leg 4
  s10.attach(31, 600, 2400);
  s11.attach(32, 600, 2400);
  s12.attach(33, 600, 2400); //rot
  // Leg 5
  s7.attach(28, 600, 2400);
  s6.attach(27, 600, 2400);
  s8.attach(29, 600, 2400);
  s9.attach(30, 600, 2400); //rot
  // Leg 6
  s1.attach(22, 600, 2400);
  s2.attach(23, 600, 2400);
  s4.attach(25, 600, 2400); //rot
  
  s15.write(90);
  s14.write(140);
  //s13.write(90);
  s5.write(45);
  s16.write(20);
  s17.write(115);
  s18.write(0);
  s19.write(50);
  s20.write(70);
  s21.write(140);
  s22.write(100);
  s23.write(25);
  s24.write(120);
  
  s12.write(110);
  s11.write(175);
  s10.write(93);
  s8.write(80);
  s7.write(0);
  s6.write(0);
  s1.write(165);
  s2.write(180);
  s4.write(120);
  
  delay(1000);
}

void loop() {
  myservo_angle = s18.read();
  
  //s18.write(myservo_angle - 1);
  //Serial.println(myservo_angle - 1);
  delay(700);   
}
