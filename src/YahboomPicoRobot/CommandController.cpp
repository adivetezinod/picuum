#include <vector>
#include <Arduino.h>
#include <Ultrasonic.h>
#include <picuum/CommandController.hpp>
#include <picuum/Picuum.hpp>

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
    uint8_t buffer[16];

public:
    enum PicuumControllerCommand
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    BluetoothCommandDelegator() : bluetooth(16, 17)
    {
    }

    void setup()
    {
        bluetooth.begin(9600);
        bluetooth.setTimeout(5);
    }

    void tick()
    {
        while (bluetooth.available())
        {
            uint8_t c = 0;
            uint8_t index = 0;
            size_t read = bluetooth.readBytes(buffer, sizeof(buffer));
            while (index < read)
            {
                c = buffer[index++];
                switch (c)
                {
                case PicuumControllerCommand::FORWARD:
                    picuum::movementController.forward();
                    break;
                case PicuumControllerCommand::BACKWARD:
                    picuum::movementController.backward();
                    break;
                case PicuumControllerCommand::LEFT:
                    picuum::movementController.left();
                    break;
                case PicuumControllerCommand::RIGHT:
                    picuum::movementController.right();
                    break;
                }
                delay(50);
                picuum::movementController.stop();
            }
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