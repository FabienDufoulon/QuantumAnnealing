#ifndef FUNCTION_H
#define FUNCTION_H


class Function
{
    public:
        Function(double startP, double endP, int nbSteps, int plateauIts) : startPoint(startP), endPoint(endP), currentPoint(startP), numberOfSteps(nbSteps), iterationsByPlateau(plateauIts) {};
        virtual ~Function() {};

        ///Makes the function start over
        virtual void reset() { currentPoint = startPoint; };
        ///Pure virtual function that implements the nature of the function.
        virtual bool step() = 0;
        ///Returns the current y value of the function.
        double getCurrentPoint() {return currentPoint;};
        ///Returns an approximation of the number of iterations in this function(number of times step can be called and return true)
        int getTotalApproximateIterations() {return numberOfSteps*iterationsByPlateau;};
        ///Returns the number of iterations on any y value.
        int getIterationsByPlateau() {return iterationsByPlateau;};

    protected:
        ///First Y value of the function.
        double startPoint;
        ///Last Y value of the function.
        double endPoint;
        ///Current Y value of the function.
        double currentPoint;
        ///Number of different Y values taken by the function.
        int numberOfSteps;
        ///Number of times the function takes the same Y value concurrently.
        int iterationsByPlateau;

        ///The function decreases its Y value by this every step.
        double decreaseByStep;
        ///Counter of the current number of iterations on this step.
        double plateauCurrentIteration;
};

#endif // FUNCTION_H
