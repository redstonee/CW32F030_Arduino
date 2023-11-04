#include <Arduino.h>

void setup()
{
    pinMode(PC13, OUTPUT);
}

void loop()
{
    digitalWrite(PC13,1);
    delay(100);
    digitalWrite(PC13,0);
    delay(100);
}