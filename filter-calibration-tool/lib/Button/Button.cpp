#include "Button.hpp"

Button::Button(uint8_t pin, uint8_t is_input_pullup)
{
    _pin = pin;
    last_state = 0;
    pushed = 0;

    pinMode(pin, (is_input_pullup) ? INPUT_PULLUP : INPUT);
}

void Button::update_button()
{
	uint8_t reading = !digitalRead(_pin);
	pushed = (last_state == 0 && reading == HIGH) ? 1 : 0;
    last_state = reading;
}

uint8_t Button::was_pushed()
{
    return pushed;
}

uint8_t Button::is_pressed()
{
    // return button->pressed;
    return 0;
}