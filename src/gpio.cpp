#include "gpio.h"
#include <Arduino.h>

void setupPins() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(GPIO_NUM_4, OUTPUT);
  pinMode(GPIO_NUM_5, OUTPUT);
}

std::string firstOn() {
  digitalWrite(GPIO_NUM_4, HIGH);
  return "First on";
}

std::string firstOff() {
  digitalWrite(GPIO_NUM_4, LOW);
  return "First off";
}

std::string secondOn() {
  digitalWrite(GPIO_NUM_5, HIGH);
  return "Second on";
}

std::string secondOff() {
  digitalWrite(GPIO_NUM_5, LOW);
  return "Second off";
}
