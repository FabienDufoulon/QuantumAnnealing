#ifndef POTENTIALENERGY_H
#define POTENTIALENERGY_H

#include <iostream>

/**
Interface. Defines the function methods for the potential energy.
*/
class PotentialEnergy
{
    public:
        PotentialEnergy() {};
        virtual ~PotentialEnergy() {};

        template <typename stateType>
        static double getEnergy(const stateType &state) {return 0;};

        template <typename stateType, typename elementaryMutation>
        static double getDifferenceEnergy(const stateType &state, const elementaryMutation &mutElem) {return 0;};

};

#endif // POTENTIALENERGY_H
