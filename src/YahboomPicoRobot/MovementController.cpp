#include <Arduino.h>
#include <picuum/MovementController.hpp>

static const int R_A = 10;
static const int R_B = 11;
static const int L_A = 13;
static const int L_B = 12;

#define MAX_BITS 16
#define MAX_SPEED ((1 << MAX_BITS) - 1)
#define BY_MAX_SPEED(by) (int)(by * MAX_SPEED)

namespace picuum
{
    void MovementController::setup()
    {
        analogWriteResolution(MAX_BITS);

        pinMode(R_A, OUTPUT);
        pinMode(R_B, OUTPUT);
        pinMode(L_A, OUTPUT);
        pinMode(L_B, OUTPUT);
    }

    void MovementController::forward(float multiplier)
    {
        analogWrite(R_A, BY_MAX_SPEED(multiplier));
        analogWrite(L_A, BY_MAX_SPEED(multiplier));
    }

    void MovementController::backward(float multiplier)
    {
        analogWrite(R_B, BY_MAX_SPEED(multiplier));
        analogWrite(L_B, BY_MAX_SPEED(multiplier));
    }

    void MovementController::stop()
    {
        analogWrite(R_A, 0);
        analogWrite(R_B, 0);

        analogWrite(L_A, 0);
        analogWrite(L_B, 0);
    }

    void MovementController::right()
    {
        analogWrite(L_A, BY_MAX_SPEED(1));
        analogWrite(R_B, BY_MAX_SPEED(1));
    }

    void MovementController::left()
    {
        analogWrite(R_A, BY_MAX_SPEED(1));
        analogWrite(L_B, BY_MAX_SPEED(1));
    }
}
