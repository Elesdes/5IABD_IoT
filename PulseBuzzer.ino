#include "thingProperties.h"

const char pinLed = D2;
const char pinFinger = A0;
const char buzzerPin = D3;

void setup()
{
    // Initialize serial and wait for port to open:
    Serial.begin(9600);
    // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
    delay(1500);

    pinMode(pinLed, OUTPUT);
    pinMode(pinFinger, INPUT);
    pinMode(buzzerPin, OUTPUT);

    // Defined in thingProperties.h
    initProperties();

    // Connect to Arduino IoT Cloud
    ArduinoCloud.begin(ArduinoIoTPreferredConnection);

    /*
       The following function allows you to obtain more information
       related to the state of network and IoT Cloud connection and errors
       the higher number the more granular information you’ll get.
       The default is 0 (only errors).
       Maximum is 4
   */
    setDebugMessageLevel(2);
    ArduinoCloud.printDebugInfo();
}

void loop()
{

    float pulse;
    int sum = 0;
    for (int i = 0; i < 20; i++)
        sum += analogRead(A0);
    pulse = sum / 20.00;
    finger = pulse;
    Serial.println(pulse);

    if (pulse > 100.0 && pulse < 170.0)
    {
        digitalWrite(pinLed, LOW);
        digitalWrite(buzzerPin, HIGH);
        delay(100);
        digitalWrite(buzzerPin, LOW);
    }
    else if (pulse > 170.0)
    {
        digitalWrite(pinLed, HIGH);
    }
    else
    {
        digitalWrite(pinLed, LOW);
    }

    ArduinoCloud.update();
    delay(100);
}