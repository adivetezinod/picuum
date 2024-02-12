#include <Arduino.h>
#include <picuum/MovementController.hpp>

static const int R_A = 10;
static const int R_B = 11;
static const int L_A = 13;
static const int L_B = 12;

#define MAX_BITS 8
#define MAX_SPEED ((1 << MAX_BITS) - 1)

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

    void MovementController::forward()
    {
        analogWrite(R_A, MAX_SPEED);
        analogWrite(L_A, MAX_SPEED);
    }

    void MovementController::backward()
    {
        analogWrite(R_B, MAX_SPEED);
        analogWrite(L_B, MAX_SPEED);
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
        analogWrite(L_A, MAX_SPEED);
        analogWrite(R_B, MAX_SPEED);
    }

    void MovementController::left()
    {
        analogWrite(R_A, MAX_SPEED);
        analogWrite(L_B, MAX_SPEED);
    }
}
