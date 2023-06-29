/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Rich/CTD2023/WiFi/src/WiFi.ino"
#include "env.h"

#include <blynk.h>
#include "oled-wing-adafruit.h"

void setup();
void loop();
#line 6 "c:/Users/Rich/CTD2023/WiFi/src/WiFi.ino"
#define TEMPINPUT A4

OledWingAdafruit display;
uint64_t reading;

SYSTEM_THREAD(ENABLED);
void setup()
{
    Blynk.begin(BLYNK_AUTH_TOKEN);
    display.setup();
    display.clearDisplay();
    display.display();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    pinMode(TEMPINPUT, INPUT);
}
void loop()
{
    Blynk.run();
    display.loop();
    reading = analogRead(TEMPINPUT);
    double voltage = (reading * 3.3) / 4095.0;
    double temperature = (voltage - 0.5) * 100;
    int fahrenheit = temperature * 1.8 + 32;
    int temp = temperature;
    display.clearDisplay();
    display.println("Current temperature: \n");
    display.printf("%u C \n", temp);
    display.printf("%u F", fahrenheit);
    display.display();
    if (display.pressedA())
    {
        display.clearDisplay();
        display.println("Push Sent");
        display.display();
        delay(5000);
    }
}
BLYNK_WRITE(V0)
{
    Serial.println("Button Tapped");
    if (param.asInt() == 1)
    {
        Blynk.logEvent("push_notifications", "Hey, Blynk push here!");
    }
}