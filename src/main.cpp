#include <Arduino.h>
#include <picuum/Picuum.hpp>

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello World");

  picuum::movementController.setup();
  picuum::commandController.setup();
}

void loop()
{
  picuum::commandController.tick();
}