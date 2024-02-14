#include <Arduino.h>
#include <Servo.h>
#include "Button.hpp"

#define SERVO_PIN 11

#define BUTTON_TOP 2
#define BUTTON_MID 3
#define BUTTON_BOT 4

// #define ANGLE_N 30
// #define ANGLE_MIDDLE 90
// #define ANGLE_M -30

#define ANGLE_N +340
#define ANGLE_MIDDLE 1520
#define ANGLE_M -340

#define LO_FILTER 800
#define HI_FILTER 1830

#define LED_BOT 10
#define LED_MID 9
#define LED_TOP 8

#define POS_CHANGE_DELAY 500

#define ADJUSTMENT_RESOLUTION 5

#define POS_ADDRESS 0
#define STATE_ADDRESS 10

Servo servo;
Button button_top = Button(BUTTON_TOP, false);
Button button_mid = Button(BUTTON_MID, false);
Button button_bot = Button(BUTTON_BOT, false);

int state = 0;

// void writeLongIntoEEPROM(int address, long number);
// long readLongFromEEPROM(int address);

void setup()
{
    Serial.begin(9600);
    servo.attach(SERVO_PIN);

    // writeLongIntoEEPROM(STATE_ADDRESS, 0);

    delay(POS_CHANGE_DELAY);
    state = ANGLE_MIDDLE;

    // is_setup = readLongFromEEPROM(STATE_ADDRESS);
    // if (is_setup)
    // {
    //     Serial.println("Setup Already!");
    //     full_position = readLongFromEEPROM(POS_ADDRESS);
    //     Serial.print("Saved Full Position: ");
    //     Serial.println(full_position);

    //     servo.writeMicroseconds(full_position);
    //     state = full_position;

    //     digitalWrite(LED_S, HIGH);
    // }
    // else
    // {
    //     Serial.println("SETUP MODE");
    //     current_pos = HI_FILTER;
    //     digitalWrite(LED_S, LOW);
    // }
}

void loop()
{
    button_top.update_button();
    button_mid.update_button();
    button_bot.update_button();

    if (button_top.was_pushed() && state != ANGLE_N)
    {
        state = ANGLE_N;
        // servo.write(ANGLE_MIDDLE + ANGLE_N);
        servo.writeMicroseconds(ANGLE_MIDDLE + ANGLE_N);
        delay(POS_CHANGE_DELAY);
        Serial.print("POSITION ");
        Serial.println(ANGLE_MIDDLE + ANGLE_N);

        digitalWrite(LED_TOP, HIGH);
        digitalWrite(LED_MID, LOW);
        digitalWrite(LED_BOT, LOW);
    }
    else if (button_mid.was_pushed() && state != ANGLE_MIDDLE)
    {
        state = ANGLE_MIDDLE;
        // servo.write(ANGLE_MIDDLE);
        servo.writeMicroseconds(ANGLE_MIDDLE);
        delay(POS_CHANGE_DELAY);
        digitalWrite(LED_TOP, LOW);
        digitalWrite(LED_MID, HIGH);
        digitalWrite(LED_BOT, LOW);
        Serial.print("POSITION ");
        Serial.println(ANGLE_MIDDLE);
    }
    else if (button_bot.was_pushed() && state != ANGLE_M)
    {
        state = ANGLE_M;
        // servo.write(ANGLE_MIDDLE + ANGLE_M);
        servo.writeMicroseconds(ANGLE_MIDDLE + ANGLE_M);
        delay(POS_CHANGE_DELAY);
        digitalWrite(LED_TOP, LOW);
        digitalWrite(LED_MID, LOW);
        digitalWrite(LED_BOT, HIGH);
        Serial.print("POSITION ");
        Serial.println(ANGLE_MIDDLE + ANGLE_M);
    }
    delay(50);
}

// void writeLongIntoEEPROM(int address, long number)
// {
// 	EEPROM.write(address, (number >> 24) & 0xFF);
// 	EEPROM.write(address + 1, (number >> 16) & 0xFF);
// 	EEPROM.write(address + 2, (number >> 8) & 0xFF);
// 	EEPROM.write(address + 3, number & 0xFF);
// }

// long readLongFromEEPROM(int address)
// {
// 	return ((long)EEPROM.read(address) << 24) +
// 		   ((long)EEPROM.read(address + 1) << 16) +
// 		   ((long)EEPROM.read(address + 2) << 8) +
// 		   (long)EEPROM.read(address + 3);
// }