#ifndef MUTATION_H
#define MUTATION_H

#include "PCG/pcg_random.hpp"

/**
Interface. Defines the method functions of the mutation.
*/
class Mutation
{
    public:
        Mutation() {};
        virtual ~Mutation() {};

        template <typename stateType, typename elemMutation>
        static void DoMutation(stateType &state, const elemMutation &mut) {}; //Requires to update backMutation in State (so change can be turned back).

        template <typename stateType, typename elemMutation>
        static std::unique_ptr<elemMutation> getElementaryMutation(const stateType &state, pcg32 &rng) {return nullptr;};
    protected:
    private:
};

#endif // MUTATION_H
