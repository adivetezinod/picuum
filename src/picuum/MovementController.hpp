#ifndef MOVEMENT_CONTROLLER_H
#define MOVEMENT_CONTROLLER_H

namespace picuum
{
    class MovementController
    {
    public:
        void setup();
        void forward(float);
        void backward(float);
        void stop();
        void right();
        void left();
    };
}

#endif //MOVEMENT_CONTROLLER_H