#include "Solver/LinearFunction.h"

LinearFunction::LinearFunction(double startP, double endP, int nbSteps, int plateauIts) : Function(startP, endP, nbSteps, plateauIts)
{
    decreaseByStep = (endP - startP) / nbSteps;
    plateauCurrentIteration = 0;
}

bool LinearFunction::step(){
    ++plateauCurrentIteration;

    if (plateauCurrentIteration == iterationsByPlateau) {
        currentPoint += decreaseByStep;
        plateauCurrentIteration = 0;
    }

    if (currentPoint < endPoint) return false;
    else return true;
}
