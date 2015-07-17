#include "Solver/LinearFunction.h"

LinearFunction::LinearFunction(double startP, double endP, int nbSteps, int stepPlateau) : Function(startP, endP, nbSteps, stepPlateau)
{
    pointStep = (endP - startP) / nbSteps;
    stepOnPlateau = 0;
}

LinearFunction::~LinearFunction()
{
    //dtor
}

bool LinearFunction::step(){
    ++stepOnPlateau;

    if (stepOnPlateau == stepPlateau) {
        currentPoint += pointStep;
        stepOnPlateau = 0;
    }

    if (currentPoint < endPoint) return false;
    else return true;

}
