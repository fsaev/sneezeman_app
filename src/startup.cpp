#include "startup.h"
#include <Arduino.h>

int numJogs = 5;

void initValve(int valvePin)
{
    for (int i = 0 ; i < numJogs; i++)
    {
        delay(250);
        digitalWrite(valvePin, HIGH);
        delay(250);
        digitalWrite(valvePin, LOW);

    }
}