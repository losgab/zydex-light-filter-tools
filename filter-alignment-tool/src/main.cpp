#include <Arduino.h>
#include <Servo.h>
#include <Bounce2.h>

#define SERVO_PIN 11

#define LED_GENERAL 8
#define LED_FULL 9
#define LED_ZERO 10

#define LASER_FULL 6
#define LASER_ZERO 7

#define BUTTON_SWEEPSTART 2
#define BUTTON_TOGGLE 3
#define BUTTON_LASER 4

#define FILTER_FULL 123 // increase for overshoot
#define FILTER_ZERO 24  // decrease for overshoot

#define LASER_ON_TIME 30000

Servo servo;
Bounce2::Button buttonSweepStart = Bounce2::Button();
Bounce2::Button buttonToggle = Bounce2::Button();
Bounce2::Button buttonLaser = Bounce2::Button();

int state = 0;
int laserState = 0;
long startTime = 0;

void setup()
{
    pinMode(LED_FULL, OUTPUT);
    pinMode(LED_ZERO, OUTPUT);
    pinMode(LED_GENERAL, OUTPUT);
    pinMode(LASER_FULL, OUTPUT);
    pinMode(LASER_ZERO, OUTPUT);

    digitalWrite(LED_GENERAL, HIGH);

    servo.attach(SERVO_PIN);
    buttonSweepStart.attach(BUTTON_SWEEPSTART, INPUT_PULLUP);
    buttonSweepStart.interval(5);
    buttonSweepStart.setPressedState(HIGH);
    buttonToggle.attach(BUTTON_TOGGLE, INPUT_PULLUP);
    buttonToggle.interval(5);
    buttonToggle.setPressedState(HIGH);
    buttonLaser.attach(BUTTON_LASER, INPUT_PULLUP);
    buttonLaser.interval(5);
    buttonLaser.setPressedState(HIGH);
}

void loop()
{
    buttonSweepStart.update();
    buttonToggle.update();
    buttonLaser.update();
    if (buttonLaser.pressed())
    {
        laserState = 1;
        if (state == FILTER_FULL)
        {
            digitalWrite(LASER_FULL, HIGH);
            digitalWrite(LASER_ZERO, LOW);
        }
        else
        {
            digitalWrite(LASER_FULL, LOW);
            digitalWrite(LASER_ZERO, HIGH);
        }
        startTime = millis();
    }
    if (buttonSweepStart.pressed())
    {
        state = FILTER_FULL;
        for (int i = 20; i <= 170; i++)
        {
            servo.write(i);
            delay(5);
        }
        for (int i = 170; i >= 20; i--)
        {
            servo.write(i);
            delay(5);
        }
        for (int i = 20; i <= 170; i++)
        {
            servo.write(i);
            delay(5);
        }
        for (int i = 170; i >= 20; i--)
        {
            servo.write(i);
            delay(5);
        }
        digitalWrite(LED_FULL, HIGH);
        digitalWrite(LED_ZERO, LOW);
        servo.write(FILTER_FULL);
        delay(100);

        laserState = 1;
        digitalWrite(LASER_FULL, HIGH);
        digitalWrite(LASER_ZERO, LOW);
        startTime = millis();
    }
    if (buttonToggle.pressed() && state != 0)
    {
        if (state == FILTER_FULL)
        {
            state = FILTER_ZERO;
            digitalWrite(LED_FULL, LOW);
            digitalWrite(LED_ZERO, HIGH);
            servo.write(FILTER_ZERO);
            delay(100);
            digitalWrite(LASER_ZERO, HIGH);
            digitalWrite(LASER_FULL, LOW);
        }
        else
        {
            state = FILTER_FULL;
            digitalWrite(LED_FULL, HIGH);
            digitalWrite(LED_ZERO, LOW);
            servo.write(FILTER_FULL);
            delay(100);

            digitalWrite(LASER_FULL, HIGH);
            digitalWrite(LASER_ZERO, LOW);
        }
        laserState = 1;
        startTime = millis();
    }
    if (laserState == 1 && millis() - startTime >= LASER_ON_TIME)
    {
        digitalWrite(LASER_FULL, LOW);
        digitalWrite(LASER_ZERO, LOW);
        startTime = laserState = 0;
    }
    delay(50);
}
