#include <Arduino.h>
#include <Servo.h>
#include <EEPROM.h>
#include "Button.hpp"

#define SERVO_PIN 11

#define BUTTON_L 2
#define BUTTON_R 3
#define BUTTON_GENERAL 4

#define FILTER_FULL 123 // increase for overshoot
#define FILTER_ZERO 24  // decrease for overshoot

#define LO_FILTER 800
#define HI_FILTER 1830

#define LED_L 8
#define LED_R 9
#define LED_S 10

#define ADJUSTMENT_RESOLUTION 5

#define POS_ADDRESS 0
#define STATE_ADDRESS 10

Servo servo;
Button button_l = Button(BUTTON_L, false);
Button button_r = Button(BUTTON_R, false);
Button button_g = Button(BUTTON_GENERAL, false);

int state = FILTER_FULL;
long current_pos = FILTER_FULL;
int full_position = 0;
uint8_t is_setup = 0;

void writeLongIntoEEPROM(int address, long number);
long readLongFromEEPROM(int address);

void setup()
{
    Serial.begin(9600);
    servo.attach(SERVO_PIN);

    // writeLongIntoEEPROM(STATE_ADDRESS, 0);

    delay(1000);


    is_setup = readLongFromEEPROM(STATE_ADDRESS);
    if (is_setup)
    {
        Serial.println("Setup Already!");
        full_position = readLongFromEEPROM(POS_ADDRESS);
        Serial.print("Saved Full Position: ");
        Serial.println(full_position);

        servo.writeMicroseconds(full_position);
        state = full_position;

        digitalWrite(LED_S, HIGH);
    }
    else
    {
        Serial.println("SETUP MODE");
        current_pos = HI_FILTER;
        digitalWrite(LED_S, LOW);
    }
}

void loop()
{
    // Serial.println("IDLE");
    button_l.update_button();
    button_r.update_button();
    button_g.update_button();

    if (!is_setup)
    {
        Serial.println("SETUP MODE");
        if (button_l.was_pushed())
        {
            current_pos += ADJUSTMENT_RESOLUTION;
            servo.writeMicroseconds(current_pos);
            Serial.println("L");
            digitalWrite(LED_L, HIGH);
            delay(50);
            digitalWrite(LED_L, LOW);
        }
        else if (button_r.was_pushed())
        {
            servo.writeMicroseconds(current_pos - 500);
            delay(500);
            current_pos -= ADJUSTMENT_RESOLUTION;
            servo.writeMicroseconds(current_pos);
            Serial.println("R");
            digitalWrite(LED_R, HIGH);
            delay(50);
            digitalWrite(LED_R, LOW);
        }
        else if (button_g.was_pushed())
        {
            writeLongIntoEEPROM(POS_ADDRESS, current_pos);
            is_setup = 1;
            writeLongIntoEEPROM(STATE_ADDRESS, is_setup);
            full_position = current_pos;
            state = full_position;
            Serial.print("Position Saved! ");
            Serial.println(full_position);
            digitalWrite(LED_S, HIGH);
            digitalWrite(LED_L, HIGH);
        }
        // Serial.println("SETUP DONE!");
    }
    else if (button_l.was_pushed() && state == LO_FILTER)
    {
        state = full_position;
        servo.writeMicroseconds(full_position);
        Serial.print("POSITION ");
        Serial.println(full_position);

        digitalWrite(LED_L, HIGH);
        digitalWrite(LED_R, LOW);
    }
    else if (button_r.was_pushed() && state == full_position)
    {
        state = LO_FILTER;
        servo.writeMicroseconds(LO_FILTER);
        Serial.println("POSITION ZERO");
        digitalWrite(LED_L, LOW);
        digitalWrite(LED_R, HIGH);
    }
    else if (button_g.was_pushed() && is_setup) // Reset the value
    {
        is_setup = 0;
        digitalWrite(LED_S, LOW);
        digitalWrite(LED_L, LOW);
        digitalWrite(LED_R, LOW);
        writeLongIntoEEPROM(STATE_ADDRESS, 0);
        current_pos = HI_FILTER;
        servo.writeMicroseconds(HI_FILTER);
    }
    delay(50);
}

void writeLongIntoEEPROM(int address, long number)
{
	EEPROM.write(address, (number >> 24) & 0xFF);
	EEPROM.write(address + 1, (number >> 16) & 0xFF);
	EEPROM.write(address + 2, (number >> 8) & 0xFF);
	EEPROM.write(address + 3, number & 0xFF);
}

long readLongFromEEPROM(int address)
{
	return ((long)EEPROM.read(address) << 24) +
		   ((long)EEPROM.read(address + 1) << 16) +
		   ((long)EEPROM.read(address + 2) << 8) +
		   (long)EEPROM.read(address + 3);
}