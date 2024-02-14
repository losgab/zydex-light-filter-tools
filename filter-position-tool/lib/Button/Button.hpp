/*
    Buttons for Arduino (OOP Based)

    Convenience library for observing button state changes.
    - Detects when a button was pushed
    - Detects if a button is held down (not implemented yet)

    Written by Gabriel Thien 2023
*/
#ifndef Button_h
#define Button_h

#include <Arduino.h>
#include <stdint.h>

class Button
{
public:
    Button(uint8_t pin, uint8_t is_input_pullup);
    void update_button();
    uint8_t was_pushed();
    uint8_t is_pressed();

private:
    uint8_t _pin;
    uint8_t last_state;
    uint8_t pushed;
};

#endif