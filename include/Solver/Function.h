#ifndef FUNCTION_H
#define FUNCTION_H


class Function
{
    public:
        Function(double startP, double endP, int nbSteps, int stepPlateau) : startPoint(startP), endPoint(endP), numberOfSteps(nbSteps), currentPoint(startP), stepPlateau(stepPlateau) {};
        virtual ~Function() {};

        virtual void reset() { currentPoint = startPoint; };
        virtual bool step() = 0;
        double getCurrentPoint() {return currentPoint;};
        int getTotalApproximateIterations() {return numberOfSteps*stepPlateau;};
        int getStepPlateau() {return stepPlateau;};

    protected:
        double startPoint;
        double endPoint;
        double currentPoint;
        int numberOfSteps;
        int stepPlateau;

        double pointStep;
        double stepOnPlateau;
    private:
};

#endif // FUNCTION_H
