#include "DFRobot_ESP32_servo.h"

servoDef servos[SERVO_NUM_MAX];
static hw_timer_t *timers[4];
static volatile uint8_t channel[4] = {0};

uint8_t servoCount = 0;


static void IRAM_ATTR timer0InterruptHandle(void)
{	
  static int timeInHigh = 0;
  static uint8_t cycleFlag = 0;
  if(servos[channel[0]].Pin.isActive == true) {
    digitalWrite(servos[channel[0]].Pin.nbr, 0);
    timeInHigh += servos[channel[0]].ticks;
  } if(cycleFlag) {
    cycleFlag = 0;
  } else {
    channel[0] ++;
  }
  while((servos[channel[0]].Pin.isActive == false) || (servos[channel[0]].ticks < SERVO_PULSE_MIN)) {
    channel[0] ++;
    if(channel[0] >= 8) {
      break;
    }
  }
  if(channel[0] >= 8) {
    timerAlarmWrite(timers[0], 20000 - timeInHigh, true);
    channel[0] = 0;
    timeInHigh = 0;
    cycleFlag = 1;
  } else {
    digitalWrite(servos[channel[0]].Pin.nbr, 1);
    timerAlarmWrite(timers[0], servos[channel[0]].ticks, true);
  }
}


static void IRAM_ATTR timer1InterruptHandle(void)
{	
  static int timeInHigh = 0;
  static uint8_t cycleFlag = 0;
  if(servos[channel[1] + 8].Pin.isActive == true) {
    digitalWrite(servos[channel[1] + 8].Pin.nbr, 0);
    timeInHigh += servos[channel[1] + 8].ticks;
  }
  if(cycleFlag) {
    cycleFlag = 0;
  } else {
    channel[1] ++;
  }
  while((servos[channel[1] + 8].Pin.isActive == false) || (servos[channel[1] + 8].ticks < SERVO_PULSE_MIN)) {
    channel[1] ++;
    if(channel[1] >= 8) {
      break;
    }
  }
  if(channel[1] >= 8) {
    timerAlarmWrite(timers[1], 20000 - timeInHigh, true);
    channel[1] = 0;
    timeInHigh = 0;
    cycleFlag = 1;
  } else {
    digitalWrite(servos[channel[1] + 8].Pin.nbr, 1);
    timerAlarmWrite(timers[1], servos[channel[1] + 8].ticks, true);
  }
}


static void IRAM_ATTR timer2InterruptHandle(void)
{
  static int timeInHigh = 0;
  static uint8_t cycleFlag = 0;
  if(servos[channel[2] + 16].Pin.isActive == true) {
    digitalWrite(servos[channel[2] + 16].Pin.nbr, 0);
    timeInHigh += servos[channel[2] + 16].ticks;
  }
  if(cycleFlag) {
    cycleFlag = 0;
  } else {
    channel[2] ++;
  }
  while((servos[channel[2] + 16].Pin.isActive == false) || (servos[channel[2] + 16].ticks < SERVO_PULSE_MIN)) {
    channel[2] ++;
    if(channel[2] >= 8) {
      break;
    }
  }
  if(channel[2] >= 8) {
    timerAlarmWrite(timers[2], 20000 - timeInHigh, true);
    channel[2] = 0;
    timeInHigh = 0;
    cycleFlag = 1;
  } else {
    digitalWrite(servos[channel[2] + 16].Pin.nbr, 1);
    timerAlarmWrite(timers[2], servos[channel[2]].ticks, true);
  }
}


static void IRAM_ATTR timer3InterruptHandle(void)
{
  static int timeInHigh = 0;
  static uint8_t cycleFlag = 0;
  if(servos[channel[3] + 24].Pin.isActive == true) {
    digitalWrite(servos[channel[3] + 24].Pin.nbr, 0);
    timeInHigh += servos[channel[3] + 24].ticks;
  }
  if(cycleFlag) {
    cycleFlag = 0;
  } else {
    channel[3] ++;
  }
  while((servos[channel[3] + 24].Pin.isActive == false) || (servos[channel[3] + 24].ticks < SERVO_PULSE_MIN)) {
    channel[3] ++;
    if(channel[3] >= 8) {
      break;
    }
  }
  if(channel[3] >= 8) {
    timerAlarmWrite(timers[3], 20000 - timeInHigh, true);
    channel[3] = 0;
    timeInHigh = 0;
    cycleFlag = 1;
  } else {
    digitalWrite(servos[channel[3] + 24].Pin.nbr, 1);
    timerAlarmWrite(timers[3], servos[channel[3] + 24].ticks, true);
  }
}



DFRobot_ESP32_Servo::DFRobot_ESP32_Servo(void)
{
  if(servoCount < SERVO_NUM_MAX) {
    timers[servoCount / 8] = timerBegin(servoCount / 8, 80, true);
    switch(servoCount / 8) {
      case 0:timerAttachInterrupt(timers[servoCount / 8], &timer0InterruptHandle, true);break;
      case 1:timerAttachInterrupt(timers[servoCount / 8], &timer1InterruptHandle, true);break;
      case 2:timerAttachInterrupt(timers[servoCount / 8], &timer2InterruptHandle, true);break;
      case 3:timerAttachInterrupt(timers[servoCount / 8], &timer3InterruptHandle, true);break;
    }
    this->servoIndex = servoCount ++;
  } else {
    this->servoIndex = INVALID_SERVO;
  }
}


uint8_t DFRobot_ESP32_Servo::attach(int pin)
{
  this->attach(pin, SERVO_PULSE_MIN, SERVO_PULSE_MAX);
  return this->servoIndex;
}


uint8_t DFRobot_ESP32_Servo::attach(int pin, int pulseMin, int pulseMax)
{
  if(servoCount < SERVO_NUM_MAX) {
    pinMode(pin, OUTPUT);
    this->pulseMax = pulseMax;
    this->pulseMin = pulseMin;
    servos[this->servoIndex].Pin.nbr = pin;
    servos[this->servoIndex].Pin.isActive = true;
  }
  return this->servoIndex;
}


void DFRobot_ESP32_Servo::detach(void)
{
  servos[this->servoIndex].Pin.isActive = false;
}


void DFRobot_ESP32_Servo::write(int value)
{
  if(servos[this->servoIndex].Pin.isActive) {
    this->writeMicroseconds(value);
  }
}


void DFRobot_ESP32_Servo::writeMicroseconds(int value)
{
  int temp = value;
  if(servos[this->servoIndex].Pin.isActive) {
    timerAlarmDisable(timers[this->servoIndex / 8]);
    this->lastWriteValue = value;
    if(temp <= 180) {
      temp = temp * (SERVO_PULSE_MAX - SERVO_PULSE_MIN) / 180 + SERVO_PULSE_MIN;
      servos[this->servoIndex].ticks = temp;
    }
    else {
      servos[this->servoIndex].ticks = temp;
    }
    timerAlarmWrite(timers[this->servoIndex / 8], servos[this->servoIndex].ticks, true);
    digitalWrite(servos[this->servoIndex].Pin.nbr, 1);
    timerAlarmEnable(timers[this->servoIndex / 8]);
  }
}


int DFRobot_ESP32_Servo::read(void)
{
  return this->lastWriteValue;
}


int DFRobot_ESP32_Servo::readMicroseconds(void)
{
  return this->lastWriteValue;
}


bool DFRobot_ESP32_Servo::attached(void)
{
  return servos[this->servoIndex].Pin.isActive;
}

