#ifndef GPIO_H
#define GPIO_H

#include <string>

void setupPins();

std::string firstOn();
std::string firstOff();
std::string secondOn();
std::string secondOff();
std::string flipPinState();
std::string rcChangeState();

#endif // GPIO_H
