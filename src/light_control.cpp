#include <Arduino.h>

#include "light_control.h"

boolean LightControl::update() {
    Serial.print("HomeKit command received: ");
    Serial.println(power->getNewVal() ? "ON" : "OFF");
    digitalWrite(LIGHT_PIN, power->getNewVal() ? LIGHT_ON : LIGHT_OFF);
    return true;
}
