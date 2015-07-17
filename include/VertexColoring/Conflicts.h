#ifndef CONFLICTS_H
#define CONFLICTS_H

#include <Solver/PotentialEnergy.h>
#include "VertexColoring/Coloring.h"
#include "VertexColoring/VertexElementaryMutation.h"

class Conflicts : public PotentialEnergy
{
    public:
        Conflicts() {}
        virtual ~Conflicts() {}

        template <typename stateType>
        static double getEnergy(const stateType &state) {std::cout << "Derived" << std::endl; return PotentialEnergy::getEnergy(state);};

        template <typename stateType, typename elementaryMutation>
        static double getDifferenceEnergy(const stateType &state, const elementaryMutation &mutElem) {return PotentialEnergy::getDifferenceEnergy(state, mutElem);};
    protected:
    private:
};


template<>
double Conflicts::getEnergy<Coloring>(const Coloring &state){
    return state.getNumberOfEdgesInConflict();
}

template<>
double Conflicts::getDifferenceEnergy<Coloring, VertexElementaryMutation>(const Coloring &state, const VertexElementaryMutation &mutElem){
    return state.F[mutElem.getVertex()][mutElem.getColor()] - state.F[mutElem.getVertex()][state.coloring[mutElem.getVertex()]];
}

#endif // CONFLICTS_H
