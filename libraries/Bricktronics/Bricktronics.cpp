#include "Bricktronics.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <Wire.h>

Bricktronics::Bricktronics() 
{
}

void delay_update(uint16_t ms, PIDMotor* m1, PIDMotor* m2)
{
    unsigned long end_time = millis() + ms;
    while (millis() < end_time)
    {
        if (m1) m1->update();
        if (m2) m2->update();
        delay(DELAY_UPDATE_MS);
    }
}

void Bricktronics::delay_update(unsigned int ms, PIDMotor* m1)
{
    unsigned long end_time = millis() + ms;
    while (millis() < end_time)
    {
        if (m1) m1->update();
        delay(DELAY_UPDATE_MS);
    }
}

void Bricktronics::pinMode(uint8_t pin, uint8_t mode)
{
    if (pin < 64)
    {
        ::pinMode(pin, mode);
    } else
    {
        mcp.pinMode(pin-64, mode);
    }
}

void Bricktronics::digitalWrite(uint8_t pin, uint8_t level)
{
    if (pin < 64)
    {
        ::digitalWrite(pin, level);
    } else
    {
        mcp.digitalWrite(pin-64, level);
    }
}

uint8_t Bricktronics::digitalRead(uint8_t pin)
{
    if (pin < 64)
    {
        ::digitalRead(pin);
    } else
    {
        mcp.digitalRead(pin-64);
    }
}

void Bricktronics::pullUp(uint8_t pin, uint8_t level)
{
    if (pin < 64)
    {
        digitalWrite(pin, level);
    } else
    {
        mcp.pullUp(pin-64, level);
    }
}

void Bricktronics::begin()
{
    Wire.begin();
    mcp.begin();
}
