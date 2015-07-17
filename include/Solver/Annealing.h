#ifndef ANNEALING_H
#define ANNEALING_H

#include "Solver/Problem.h"
#include "Solver/Function.h"
#include <math.h>
#include "PCG/pcg_random.hpp"
#include <random>
#include <algorithm>

#include <iostream> // for test

/**
Represents the method used to do the annealing. This class contains none of the information required for one run of annealing.
*/
class Annealing
{
    public:
        Annealing() {}
        virtual ~Annealing() {}

        ///To be reimplemented depending on annealing method
        //virtual void run(Problem &problem) = 0;

    protected:
        uint32_t seed;
        pcg32 rng;
    private:
};

#endif // ANNEALING_H
