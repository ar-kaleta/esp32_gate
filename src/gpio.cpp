#include "gpio.h"
#include <Arduino.h>

void setupPins() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(GPIO_NUM_4, OUTPUT);
  pinMode(GPIO_NUM_5, OUTPUT);
  pinMode(GPIO_NUM_18, INPUT);
}

std::string firstOn() {
  digitalWrite(GPIO_NUM_4, HIGH);
  return "GPIO 4 on";
}

std::string firstOff() {
  digitalWrite(GPIO_NUM_4, LOW);
  return "GPIO 4 off";
}

std::string secondOn() {
  digitalWrite(GPIO_NUM_5, HIGH);
  return "GPIO 5 on";
}

std::string secondOff() {
  digitalWrite(GPIO_NUM_5, LOW);
  return "GPIO 5 off";
}

std::string flipPinState() {
  if (digitalRead(GPIO_NUM_4) == HIGH || digitalRead(GPIO_NUM_5) == HIGH) {
    digitalWrite(GPIO_NUM_4, LOW);
    digitalWrite(GPIO_NUM_5, LOW);
    return "Both off";
  } else {
    digitalWrite(GPIO_NUM_4, HIGH);
    digitalWrite(GPIO_NUM_5, HIGH);
    return "Both on";
  }
}

std::string rcChangeState() {
  static unsigned long lastTime = 0;
  unsigned long debounceDelay =
      200; // Adjust debounce delay to avoid multiple triggers

  if (HIGH == digitalRead(GPIO_NUM_18) &&
      (millis() - lastTime > debounceDelay)) {
    lastTime = millis(); // Update the time of the last successful trigger
    return flipPinState();
  }
  return "";
}
