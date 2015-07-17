#ifndef LINEARFUNCTION_H
#define LINEARFUNCTION_H

#include <Solver/Function.h>
#include <iostream>//test

class LinearFunction : public Function
{
    public:
        LinearFunction(double startP, double endP, int nbSteps, int stepPlateau);
        virtual ~LinearFunction();

        bool step();
    protected:
    private:
};

#endif // LINEARFUNCTION_H
