/*
    === Arduino Ant Robot / Hexapod ===
    by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>
#include <SoftwareSerial.h>
#include <stdlib.h>

#define trigPin 7
#define echoPin 6
#define ledB 10

SoftwareSerial Bluetooth(12, 9); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)

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

int i0H1 = 0;
int i1H1 = 0;
int i2H1 = 0;
int i3H1 = 0;
int i4H1 = 0;
int i5H1 = 0;
int i6H1 = 0;
int i7H1 = 0;
int i8H1 = 0;

int i0T1 = 0;
int i1T1 = 0;
int i2T1 = 0;
int i3T1 = 0;
int i4T1 = 0;
int i5T1 = 0;
int i6T1 = 0;

int i1L1 = 0;
int i2L1 = 0;
int i3L1 = 0;
int i4L1 = 0;
int i5L1 = 0;
int i6L1 = 0;

int i1L2 = 0;
int i2L2 = 0;
int i3L2 = 0;
int i4L2 = 0;
int i5L2 = 0;
int i6L2 = 0;

int s15Init = 85;   // Head Roll
int s14Init = 120;  // Head Pitch
int s5Init = 30;    // Tail

// RED side
// Right
int s16Init = 45;
int s17Init = 75;
int s18Init = 15;

// Left
int s19Init = 30;
int s20Init = 90;
int s21Init = 173;

// Black side
// Right
int s22Init = 95;
int s23Init = 35;
int s24Init = 75;

// Left
int s12Init = 105;
int s11Init = 140;
int s10Init = 135;

// Yellow side
// Right
int s8Init = 58;
int s7Init = 39;
int s6Init = 5;

// Left
int s4Init = 138;
int s2Init = 150;
int s1Init = 160;

boolean l1status = LOW;
boolean l2status = LOW;
boolean aStatus = LOW;
boolean attStatus = LOW;
int k = 0;
int a = 0;
int aa = 0;
int period = 1000;
unsigned long time_now = 0;

float distance;
long duration;
int dataIn;
int m = 0;
int h = 0;
int t = 0;
int att = 0;
int speedV = 20;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello HUMAN");
  Bluetooth.begin(9600); // Default baud rate of the Bluetooth module
  Bluetooth.setTimeout(1);
  delay(20);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ledB, OUTPUT);
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
  
  initialPosition();
  delay(3000);
}
void loop() {

  // Check for incoming data
  if (Bluetooth.available()){
    Serial.print("data Bluetooth received: ");
    //Serial.println(Bluetooth.read());
    int number;
    Bluetooth.readBytes((char*)&number, sizeof(number));
    Serial.println(number);
    dataIn = number;
  }
  
  if (Serial.available() > 0) {
    dataIn = Serial.readString().toInt();  // Read the data
    Serial.print("data Serial received: ");
    Serial.println(dataIn);
  }
  if (dataIn == -1) {
    Serial.println("Rebooting");
    m = -1;
  }
  if (dataIn == 0) {
    Serial.println("dataIn 0 -- STOPPING");
    m = 0;
  }
  if (dataIn == 2) {
    Serial.println("dataIn 2");
    m = 2;
  }
  if (dataIn == 3) {
    Serial.println("dataIn 3");
    m = 3;
  }
  if (dataIn == 4) {
    Serial.println("dataIn 4");
    m = 4;
  }
  if (dataIn == 5) {
    Serial.println("dataIn 5");
    m = 5;
  }
  if (dataIn == 10) {
    Serial.println("dataIn 10");
    t = 10;
  }
  if (dataIn == 11) {
    Serial.println("dataIn 11");
    h = 11;
  }
  
  /*if (dataIn >= 15) {
    Serial.println("dataIn 15");
    Serial.println(dataIn);
    speedV = dataIn;
  }*/


  

  //return;
  /*Serial.print("m: ");
    Serial.println(m);

    Serial.print("t: ");
    Serial.println(t);


    Serial.print("h: ");
    Serial.println(h);*/
  if (m == -1) {
    initialPosition();
    dataIn = 0;
  }

  // Move forward
  if (m == 2) {
    moveLeg1Simple();
    moveLeg4Simple();
    moveLeg5Simple();
      if (l1status == HIGH) {
        moveLeg2Simple();
        moveLeg3Simple();
        moveLeg6Simple();
      }
  }
  // Rotate left
  if (m == 3) {
    moveHeadLeft();
    moveLeg1Simple();
    moveLeg5Simple();
    moveLeg4LeftSimple();
    if (l1status == HIGH) {
      moveLeg3Simple();
      moveLeg2LeftSimple();
      moveLeg6LeftSimple();
    }
  }
  // Rotate right
  if (m == 4) {
    moveHeadRight();
    moveLeg1RightSimple();
    moveLeg5RightSimple();
    moveLeg4Simple();
    if (l1status == HIGH) {
      moveLeg3RightSimple();
      moveLeg2Simple();
      moveLeg6Simple();
    }
  }
  // Move reverse
  if (m == 5) {
    moveLeg1Rev();
    moveLeg3Rev();
    moveLeg5Rev();
    if (l1status == HIGH) {
      moveLeg2Rev();
      moveLeg4Rev();
      moveLeg6Rev();
    }
  }
  // Bite
  /*/if (dataIn == 6) {
    bite();
  }
  // Attack
  if (dataIn == 7) {
    prepareAttack();
    if (aStatus == HIGH) {
      while (a == 0) {
        delay(1000);
        a = 1;
      }
      attack();
      if (attStatus == HIGH) {
        while (aa == 0) {
          delay(2000);
          aa = 1;
        } attStatus = LOW;
      }
    }
  }*/
  // Grab
  if (dataIn == 8) {
    grab();
  }
  // Drop
  if (dataIn == 9) {
    drop();
  }

  // Tail
  if (t == 10) {
    tail();
  }
  // Head
  //if (h == 11) {
  //  moveHead();
  //}

  if (dataIn == 12) {
    initialPosTail();
  }
  if (dataIn == 13) {
    initialPosHead();
  }
  // Initial and resting position
  if (dataIn == 0) {
    //initialPosition();

    // Get the distance from the ultrasonic sensor
    /*if (getDistance() > 40) {
      att = 0;
      }
      if (getDistance() <= 40) {
      att = 1;
      dataIn = 99;
      }*/
    // Monitor the battery voltage
    /*int sensorValue = analogRead(A3);
      float voltage = sensorValue * (5.00 / 1023.00) * 2.9; // Convert the reading values from 5v to suitable 12V i
      Serial.print("Voltage: ");
      Serial.println(voltage);
      // If voltage is below 11V turn on the LED
      if (voltage < 11) {
      digitalWrite(ledB, HIGH);
      }
      else {
      digitalWrite(ledB, LOW);
      }*/
  }
  
  // If there is an object in front of the sensor prepare for attack
  /*/if (att == 1) {
    prepareAttack();
    if (aStatus == HIGH) {
      while (a == 0) {
        delay(2000);
        a = 1;
      }
      if (getDistance() > 30) {
        att = 2;
        a = 0;
        aStatus = LOW;
        initialPosHead();
      }
      if (getDistance() < 30) {
        att = 3;
        a = 0;
        aStatus = LOW;
        initialPosHead();
      }
    }
  }
  // If there is no longer object in front, dismiss the attack
  if (att == 2) {
    dismissAttack();
    if (aStatus == HIGH) {
      dataIn = 0;
      att = 0;
    }
  }
  // If there is closer to the sensor attack
  if (att == 3) {
    attack();
    if (attStatus == HIGH) {
      while (aa == 0) {
        delay(2000);
        aa = 1;
      } attStatus = LOW;
    }
    if (aStatus == HIGH) {
      while (a == 0) {
        delay(2000);
        a = 1;
      }
      dataIn = 0;
      att = 0;
      initialPosHead();
    }
  }*/
  
  delay(speedV);
}

void moveHeadLeft() {
  if (i0H1 <= 35) {
    s14.write(s14Init - i0H1);
    s15.write(s15Init - i0H1);
    s5.write(s5Init + i0H1); // Tail
    i0H1++;
  }
}
void moveHeadRight() {
  if (i2H1 <= 35) {
    s14.write(s14Init - i2H1);
    s15.write(s15Init + i2H1);
    s5.write(s5Init - i2H1); // Tail
    i2H1++;
  }
}

void grab() {
  if (i1H1 <= 20) {
    s13.write(90 + i1H1);
    i1H1++;
  }
}
void drop() {
  if (i2H1 <= 20) {
    s13.write(110 - i2H1);
    i2H1++;
  }
}

void tail() {
  if (i0T1 <= 45) {
    s5.write(s5Init - i0T1);
    i0T1++;
  }
  if ( i0T1 >= 45 & i1T1 <= 60) {
    s5.write(0 + i1T1);
    i1T1++;
  }

  if (i1T1 >= 60) {
    s5.write(60 - i2T1);
    i2T1++;
  }

  if (i2T1 >= 30) {
    i0T1 = 0;
    i1T1 = 0;
    i2T1 = 0;
  }

}

void moveLeg1Simple() {
  if (i1L1 <= 10) {
    s17.write(s17Init);
    i1L1++;
  }
  if (i2L1 <= 30) {
    s16.write(s16Init - 20 + i2L1);
    Serial.println(s16.read());
    i2L1++;
  }

  if (i2L1 > 28 & i3L1 <= 10) {
    s17.write(s17Init - 30);
    i3L1++;
  }
  
  if (i2L1 >= 30) {
    s16.write(s16Init - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}

void moveLeg1RightSimple() {
  if (i1L1 <= 10) {
    s17.write(s17Init);
    i1L1++;
  }
  if (i2L1 <= 30) {
    s16.write(s16Init - i2L1);
    i2L1++;
  }

  if (i2L1 > 28 & i3L1 <= 10) {
    s17.write(s17Init - 20);
    i3L1++;
  }
  
  if (i2L1 >= 30) {
    s16.write(s16Init - 20 + i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}


void moveLeg1() {
  if (i1L1 <= 10) {
    s18.write(30 - i1L1 * 2);
    s17.write(90 - i1L1 * 3);
    i1L1++;
  }
  if (i2L1 <= 30) {
    s16.write(50 - i2L1);
    i2L1++;

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  if (i2L1 >= 30) {
    s16.write(20 - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}


void moveLeg2Simple() {
  if (i1L2 <= 10) {
    s20.write(s20Init);
    i1L2++;
  }
  if (i1L2 <= 30) {
    s19.write(s19Init + 30 - i2L2);
    i2L2++;
  }

  if (i2L2 > 28 & i3L2 <= 10) {
    s20.write(s20Init + 20);
    i3L2++;
  }
  
  if (i2L2 >= 30) {
    s19.write(s19Init + i4L2);
    i4L2++;
    l1status = HIGH;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg2LeftSimple() {
  if (i1L2 <= 10) {
    s20.write(s20Init);
    i1L2++;
  }
  if (i1L2 <= 30) {
    s19.write(s19Init + i2L2);
    i2L2++;
  }

  if (i2L2 > 28 & i3L2 <= 10) {
    s20.write(s20Init + 20);
    i3L2++;
  }
  
  if (i2L2 >= 30) {
    s19.write(s19Init + 30 - i4L2);
    i4L2++;
    l1status = HIGH;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

// Each iteration or step is executed in the main loop section where there is also a delay time for controlling the speed of movement
void moveLeg2() {
  if (i1L2 <= 10) {
    s21.write(50 - i1L2 * 2);
    s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(75 - i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(45 + i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg3RightSimple() {
  if (i1L1 <= 10) {
    s23.write(s23Init - 30);
  }
  if (i2L1 <= 30) {
    s22.write(s22Init -10 + i2L1);
  }
  if (i2L1 > 28 & i3L1 <= 10) {
    s23.write(s23Init);
  }
  if (i2L1 >= 30) {
    s22.write(s22Init +10 - i4L1);
  }
}

void moveLeg3Simple() {
  if (i1L1 <= 10) {
    s23.write(s23Init - 30);
  }
  if (i2L1 <= 30) {
    s22.write(s22Init + 30 - i2L1);
  }
  if (i2L1 > 28 & i3L1 <= 10) {
    s23.write(s23Init);
  }
  if (i2L1 >= 30) {
    s22.write(s22Init + i4L1);
  }
}


void moveLeg3() {
  if (i1L1 <= 10) {
    s24.write(50 - i1L1 * 2);
    s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(80 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(50 + i4L1);
  }
}

void moveLeg4LeftSimple() {
  if (i1L1 <= 10) {
    s11.write(s11Init);
  }
  if (i2L1 <= 30) {
    s12.write(s12Init - 30 + i2L1);
  }
  
  if (i2L1 > 28 & i3L1 <= 10) {
    s11.write(s11Init + 20);
  }
  if (i2L1 >= 30) {
    s12.write(s12Init - i4L1);
  }
}



void moveLeg4Simple() {
  if (i1L1 <= 10) {
    s11.write(s11Init);
  }
  if (i2L1 <= 30) {
    s12.write(s12Init - i2L1);
  }
  
  if (i2L1 > 28 & i3L1 <= 10) {
    s11.write(s11Init + 20);
  }
  if (i2L1 >= 30) {
    s12.write(s12Init - 30 + i4L1);
  }
}


void moveLeg4() {
  if (i1L2 <= 10) {
    s10.write(65 + i1L2 * 2);
    s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(35 + i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(65 - i4L2);
  }
}

void moveLeg5Simple() {
  if (i1L1 <= 10) {
    s7.write(s7Init);
  }
  if (i2L1 <= 30) {
    s8.write(s8Init + i2L1);
  }
  
  if (i2L1 > 28 & i3L1 <= 10) {
    s7.write(s7Init - 10);
  }
  if (i2L1 >= 30) {
    s8.write(s8Init + 30 - i4L1);
  }
}

void moveLeg5RightSimple() {
  if (i1L1 <= 10) {
    s7.write(s7Init);
  }
  if (i2L1 <= 30) {
    s8.write(s8Init + 30 - i2L1);
  }
  
  if (i2L1 > 28 & i3L1 <= 10) {
    s7.write(s7Init - 10);
  }
  if (i2L1 >= 30) {
    s8.write(s8Init + i4L1);
  }
}


void moveLeg5() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(30 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(60 - i4L1);
  }
}


void moveLeg6LeftSimple() {
  if (i1L2 <= 10) {
    s2.write(s2Init);
  }
  if (i2L2 <= 30) {
    s4.write(s4Init -30 + i2L2);
  }
  if (i2L2 > 28 & i3L2 <= 10) {
    s2.write(s2Init + 20);
  }
  if (i2L2 >= 30) {
    s4.write(s4Init - i4L2);
  }
}


void moveLeg6Simple() {
  if (i1L2 <= 10) {
    s2.write(s2Init);
  }
  if (i2L2 <= 30) {
    s4.write(s4Init - i2L2);
  }
  if (i2L2 > 28 & i3L2 <= 10) {
    s2.write(s2Init + 20);
  }
  if (i2L2 >= 30) {
    s4.write(s4Init - 30 + i4L2);
  }
}



void moveLeg6() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s4.write(60 + i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s4.write(90 - i4L2);
  }
}

void moveLeg1Rev() {
  // Swign phase - move leg though air - from initial to final position
  // Rise the leg
  if (i1L1 <= 10) {
    s18.write(60 - i1L1 * 2);
    s17.write(90 - i1L1 * 3);
    i1L1++;
  }
  // Rotate the leg
  if (i2L1 <= 21) {
    s16.write(100 - i2L1);
    i2L1++;

  }
  // Move back to touch the ground
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(-40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L1 >= 20) {
    s16.write(70 - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  // Reset the counters for repeating the process
  if (i4L1 >= 60) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }

}
void moveLeg2Rev() {
  if (i1L2 <= 10) {
    s21.write(50 - i1L2 * 2);
    s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(45 + i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(75 - i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg3Rev() {
  if (i1L1 <= 10) {
    s24.write(50 - i1L1 * 2);
    s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(50 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(80 - i4L1);
  }
}

void moveLeg4Rev() {
  if (i1L2 <= 10) {
    s10.write(65 + i1L2 * 2);
    s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(65 - i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(35 + i4L2);
  }
}

void moveLeg5Rev() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(60 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(30 + i4L1);
  }
}

void moveLeg6Rev() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s4.write(90 - i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s4.write(60 + i4L2);
  }
}

void moveLeg1Right() {
  if (i1L1 <= 10) {
    s18.write(60 - i1L1 * 2);
    s17.write(90 - i1L1 * 3);
    i1L1++;
  }
  if (i2L1 <= 30) {
    s16.write(70 + i2L1);
    i2L1++;

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  if (i2L1 >= 30) {
    s16.write(100 - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}
void moveLeg2Right() {
  if (i1L2 <= 10) {
    s21.write(50 - i1L2 * 2);
    s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(45 + i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(75 - i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg3Right() {
  if (i1L1 <= 10) {
    s24.write(50 - i1L1 * 2);
    s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(50 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(80 - i4L1);
  }
}

void moveLeg4Left() {
  if (i1L2 <= 10) {
    s10.write(65 + i1L2 * 2);
    s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(60 - i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(30 + i4L2);
  }
}

void moveLeg5Left() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(60 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(30 + i4L1);
  }
}

void moveLeg6Left() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s4.write(90 - i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s4.write(60 + i4L2);
  }
}

void initialPosTail() {
  i0T1 = 0;
  i1T1 = 0;
  i2T1 = 0;
  i3T1 = 0;
  i4T1 = 0;
  i5T1 = 0;
  i6T1 = 0;
  t = 0;
}

void initialPosHead() {
  attStatus = LOW;
  aStatus = LOW;
  i0H1 = 0;
  i1H1 = 0;
  i2H1 = 0;
  i3H1 = 0;
  i4H1 = 0;
  i5H1 = 0;
  i6H1 = 0;
  i7H1 = 0;
  i8H1 = 0;
  h = 0;
  aa = 0;
}

void initialPosition() {
  a = 0;
  aa = 0;
  m = 0;
  l1status = LOW;
  l2status = LOW;
  aStatus = LOW;
  attStatus = LOW;

  s15.write(s15Init);
  s14.write(s14Init);
  //s13.write(90);
  s5.write(s5Init);
  
  s16.write(s16Init);
  s17.write(s17Init);
  s18.write(s18Init);
  
  s19.write(s19Init);
  s20.write(s20Init);
  s21.write(s21Init);
  
  s22.write(s22Init);
  s23.write(s23Init);
  s24.write(s24Init);

  s12.write(s12Init);
  s11.write(s11Init);
  s10.write(s10Init);
  
  s8.write(s8Init);
  s7.write(s7Init);
  s6.write(s6Init);
  
  s4.write(s4Init);
  s2.write(s2Init);
  s1.write(s1Init);

  i0H1 = 0;
  i1H1 = 0;
  i2H1 = 0;
  i3H1 = 0;
  i4H1 = 0;
  i5H1 = 0;
  i6H1 = 0;
  i7H1 = 0;
  i8H1 = 0;

  i0T1 = 0;
  i1T1 = 0;
  i2T1 = 0;
  i3T1 = 0;
  i4T1 = 0;
  i5T1 = 0;
  i6T1 = 0;

  i1L1 = 0;
  i2L1 = 0;
  i3L1 = 0;
  i4L1 = 0;
  i5L1 = 0;
  i6L1 = 0;

  i1L2 = 0;
  i2L2 = 0;
  i3L2 = 0;
  i4L2 = 0;
  i5L2 = 0;
  i6L2 = 0;
}

//===== getDistance - Custom Function
int getDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // distance in cm
  return distance;
}
