#ifndef _DFRobot_ESP32_Servo_h
#define _DFRobot_ESP32_Servo_h

#include "pins_arduino.h"
#include "Arduino.h"
#include "esp32-hal-timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/xtensa_api.h"
#include "freertos/task.h"
#include "rom/ets_sys.h"
#include "soc/timer_group_struct.h"
#include "soc/dport_reg.h"
#include "esp_attr.h"
#include "esp_intr.h"

#define SERVO_VERSION   1

#define SERVO_NUM_MAX   32
#define SERVO_ANGLE_MAX 180
#define SERVO_PULSE_MAX 2400
#define SERVO_PULSE_MIN 544
#define INVALID_SERVO   255
#define SERVO_CYCLE     20000

typedef struct {
	uint8_t nbr;       //servos num 0 - 39
	uint8_t isActive;  //servo status
} servoPinDef;

typedef struct {
	servoPinDef Pin;              //servo pin
	volatile unsigned int ticks;  //servo pulse to high
} servoDef;


class DFRobot_ESP32_Servo {
public:
	DFRobot_ESP32_Servo(void);
	uint8_t attach(int pin);
	uint8_t attach(int pin, int pulseMin, int pulseMax);
	void detach(void);
	void write(int value);
	void writeMicroseconds(int value);
	int  read(void);
	int  readMicroseconds(void);
	bool attached(void);
private:
	uint8_t servoIndex;
	int lastWriteValue;
	int pulseMax;
	int pulseMin;
};


#endif

