#ifndef STATE_H
#define STATE_H

#include "Solver/ElementaryMutation.h"
#include "PCG/pcg_random.hpp"
#include <memory>

/**
Interface. This class requires to be implemented in derived class so that the required information of an instance of
a problem is here, as well as the methods required to act upon these informations.
*/
class State
{
    public:
        State() {};
        virtual ~State() {};


        virtual void initStart(pcg32 &rng) {};

        std::unique_ptr<ElementaryMutation> backMutation; // Mutation to return to previous state.

};

#endif // STATE_H
