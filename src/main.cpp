#include <Arduino.h>
#include <picuum/Picuum.hpp>

namespace picuum
{
  picuum::CommandController commandController;
  picuum::MovementController movementController;
}

void setup()
{
  Serial.begin(115200);

  picuum::movementController.setup();
  picuum::commandController.setup();
}

void loop()
{
  picuum::commandController.tick();
}