#include <Arduino.h>
#include <Bounce2.h>

#define LED1 5
#define LED2 13
#define POTI A0
#define LDR A1
#define TASTER1 6
#define ZEIT 300

Bounce2::Button button = Bounce2::Button();

float spannung;
uint16_t ldr;
bool ledState = false;
bool blinkState = false; 
unsigned long lastBlink;
unsigned long last;
unsigned long blinkInterval = 500;

void setup()
{
    Serial.begin(115200);
    Serial.println("..Start..");
    pinMode(TASTER1,INPUT);
    button.attach(TASTER1, INPUT);
    button.interval(20);
    pinMode(LED1, OUTPUT);
    digitalWrite(LED1, ledState);
    pinMode(LED2, OUTPUT);
    digitalWrite(LED2, LOW);
    pinMode(POTI, INPUT);
}

void loop()
{
    button.update();
    if (button.pressed())
    {
        ledState = !ledState;
        digitalWrite(LED1, ledState);
    }

    ldr = analogRead(LDR);
    spannung = (ldr * 5.0) / 1023.0;

    uint16_t poti = analogRead(POTI);
    blinkInterval = map(poti, 0, 1023, 50, 500);

    if(ldr > 2.0)
    {
        digitalWrite(LED1, ledState);
    }
    else if(ldr < 1.0)
    {
        digitalWrite(LED1, !ledState);
    }

    if (millis() - lastBlink >= blinkInterval)
    {
        blinkState = !blinkState;
        digitalWrite(LED2, blinkState);
        lastBlink = millis();
    }

    if (millis() - last > 300)
    {
        Serial.print("LED: ");
        if (ledState)
        {
            Serial.print("EIN  ||");
        }
        else
        {
            Serial.print("AUS  ||");
        }
        Serial.print("     LDR: ");
        Serial.println(spannung);
        last = millis();
    }


}
