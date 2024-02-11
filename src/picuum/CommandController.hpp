#ifndef COMMAND_CONTROLLER_H
#define COMMAND_CONTROLLER_H

namespace picuum {
    class CommandController {
        public:
            void setup();
            void tick();

        class CommandDelegator {
            public:
                virtual void setup() = 0;
                virtual void tick() = 0;
        };
    };
}

#endif //COMMAND_CONTROLLER_H