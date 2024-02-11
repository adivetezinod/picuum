#include <Arduino.h>
#include <picuum/CommandController.hpp>
#include <Ultrasonic.h>
#include <vector>

class UltrasonicCommandDelegator : public picuum::CommandController::CommandDelegator
{
private:
    Ultrasonic us;

public:
    UltrasonicCommandDelegator() : us(0, 1)
    {
    }

    void setup()
    {
    }

    void tick()
    {
    }
};

class BluetoothCommandDelegator : public picuum::CommandController::CommandDelegator
{
private:
    UART bluetooth;

    char buffer[64];

public:
    BluetoothCommandDelegator() : bluetooth(16, 17)
    {
    }

    void setup()
    {
        bluetooth.begin(9600);
    }

    void tick()
    {
        while (bluetooth.available())
        {
            size_t read = bluetooth.readBytes(buffer, sizeof(buffer));
            buffer[read] = 0;
            Serial.print(read);
            Serial.print(" ");
            Serial.print(buffer);
            Serial.println("-----");
            bluetooth.println("Donizete");
        }
    }
};

static UltrasonicCommandDelegator ultrasonic;
static BluetoothCommandDelegator bluetooth;

static picuum::CommandController::CommandDelegator *delegators[] = {
    &ultrasonic,
    &bluetooth,
};

namespace picuum
{
    void CommandController::setup()
    {
        for (auto delegator : delegators)
        {
            delegator->setup();
        }
    }

    void CommandController::tick()
    {
        for (auto delegator : delegators)
        {
            delegator->tick();
        }
    }
}