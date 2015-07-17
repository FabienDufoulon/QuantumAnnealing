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
        static double getEnergy(const stateType &state) {std::cout << "Pot Generic" << std::endl; return 0;};

        template <typename stateType, typename elementaryMutation>
        static double getDifferenceEnergy(const stateType &state, const elementaryMutation &mutElem) {return 0;};
    protected:
    private:
};

#endif // POTENTIALENERGY_H
