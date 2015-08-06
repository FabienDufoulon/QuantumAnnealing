#ifndef LINEARFUNCTION_H
#define LINEARFUNCTION_H

#include <Solver/Function.h>

class LinearFunction : public Function
{
    public:
        LinearFunction(double startP, double endP, int nbSteps, int stepPlateau);
        virtual ~LinearFunction() {};

        bool step();
};

#endif // LINEARFUNCTION_H
