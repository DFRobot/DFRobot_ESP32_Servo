//Each of the 8 servos uses a hardware timer

#include "DFRobot_ESP32_servo.h"

DFRobot_ESP32_Servo servo0;
DFRobot_ESP32_Servo servo1;
DFRobot_ESP32_Servo servo2;
DFRobot_ESP32_Servo servo3;
DFRobot_ESP32_Servo servo4;
DFRobot_ESP32_Servo servo5;
DFRobot_ESP32_Servo servo6;
DFRobot_ESP32_Servo servo7;
DFRobot_ESP32_Servo servo8;
DFRobot_ESP32_Servo servo9;
DFRobot_ESP32_Servo servo10;


void setup(void) {

  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  servo1.attach(D2);
  servo9.attach(D4);
  servo10.attach(D5);
  
}


void loop(void) {

  delay(2000);
  servo1.write(45);
//  servo9.write(45);
  servo10.write(45);
  delay(2000);
//  servo1.write(135);
//  servo9.write(135);
//  servo10.write(135);

}


