#include <Arduino.h>

void setup()
{
    pinMode(PC13, OUTPUT);
    Serial.begin(115200);
}

void loop()
{
    Serial.println("Fuck The World!");
    digitalWrite(PC13, 1);
    delay(500);
    digitalWrite(PC13, 0);
    delay(500);
}