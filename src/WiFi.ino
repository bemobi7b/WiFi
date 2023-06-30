#include "env.h"

#include <blynk.h>
#include "oled-wing-adafruit.h"

#define TEMPINPUT A4
#define VIRTUAL_BUTTON_PIN V2
#define VIRTUAL_TEMP_STATE V1
#define VIRTUAL_NOTE V0
#define NOTIFY_EVENT_CODE "notify"
#define HARDWARE_NOTIFY_MSG "Hardware button pressed!"
#define VIRTUAL_NOTIFY_MSG "Virtual button pressed!"

OledWingAdafruit display;
uint64_t reading;

SYSTEM_THREAD(ENABLED);
void setup()
{
    Serial.begin(9600);
    Blynk.begin(BLYNK_AUTH_TOKEN);
    display.setup();
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.display();
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
    display.setCursor(0, 0);
    display.println("Current temperature: \n");
    display.printf("%u C \n", temp);
    display.printf("%u F", fahrenheit);
    display.display();
    Blynk.virtualWrite(VIRTUAL_TEMP_STATE, temp);
    if (display.pressedA())
    {
        Serial.println("Press");
        Blynk.virtualWrite(VIRTUAL_NOTE, HIGH);
        Blynk.virtualWrite(VIRTUAL_BUTTON_PIN, HIGH);
        display.clearDisplay();
        display.println("Push Sent");
        display.display();
        Blynk.logEvent(NOTIFY_EVENT_CODE, HARDWARE_NOTIFY_MSG);
        delay(5000);
        Blynk.virtualWrite(VIRTUAL_BUTTON_PIN, LOW);
    }
    else
    {
        // Blynk.virtualNote
        delay(200);
    }
}
BLYNK_WRITE(VIRTUAL_BUTTON_PIN)
{
    Serial.println("Button Tapped");
    if (param.asInt() == 1)
    {
        Blynk.logEvent(NOTIFY_EVENT_CODE, VIRTUAL_NOTIFY_MSG);
    }
}