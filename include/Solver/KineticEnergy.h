#ifndef KINETICENERGY_H
#define KINETICENERGY_H

/**
Interface. Defines the function methods to calculate kinetic energy.
*/
template <typename stateType> class Problem;

class KineticEnergy
{
    public:
        KineticEnergy() {}
        virtual ~KineticEnergy() {}

        template <typename stateType>
        static double getEnergy(const Problem<stateType> &problem) {return 0;};

        template <typename stateType, typename elementaryMutation>
        static double getDifferenceEnergy(const stateType &state, const stateType &next, const stateType &prev, const elementaryMutation &mutElem) {return 0;};

        template <typename stateType, typename elementaryMutation>
        static double getDifferenceEnergyBounded(const stateType &state, const stateType &next, const stateType &prev, const elementaryMutation &mutElem) {return 0;};
    protected:
    private:
};

#endif // KINETICENERGY_H
