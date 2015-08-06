#ifndef KINETICCONFLICTS_H
#define KINETICCONFLICTS_H

#include <Solver/KineticEnergy.h>


class KineticConflicts : public KineticEnergy
{
    public:
        KineticConflicts() {}
        virtual ~KineticConflicts() {}

        template <typename stateType>
        static double getEnergy(const Problem<stateType> &problem) {return KineticEnergy::getEnergy(problem);}; //shouldn't be called

        template <typename stateType, typename elementaryMutation>
        static double getDifferenceEnergy(const stateType &state, const stateType &next, const stateType &prev, const elementaryMutation &mutElem) {return KineticEnergy::getDifferenceEnergy(state, next, prev, mutElem);}; //shouldn't be called

        template <typename stateType, typename elementaryMutation>
        static double getDifferenceEnergyBounded(const stateType &state, const stateType &next, const stateType &prev, const elementaryMutation &mutElem) {return KineticEnergy::getDifferenceEnergyBounded(state, next, prev, mutElem);}; //shouldn't be called

};

//These methods are the ones called normally.
template<>
double KineticConflicts::getEnergy<Coloring>(const Problem<Coloring> &problem){
    std::cout << "Wrong place" << std::endl;
    //Not implemented yet.
    return 0;
}

template<>
double KineticConflicts::getDifferenceEnergy<Coloring, VertexElementaryMutation>(const Coloring &state, const Coloring &next, const Coloring &prev, const VertexElementaryMutation &mutElem){

    auto diffEnergy = 0.;
    std::vector<int> Valpha (state.colorClasses[ state.coloring[mutElem.getVertex()] ] );
    eraseSorted(Valpha, mutElem.getVertex());

    for (int vertex : Valpha ){
        diffEnergy += 2*( next.spin(vertex, mutElem.getVertex()) + prev.spin(vertex, mutElem.getVertex()) );
    }

    for (int vertex : state.colorClasses[ mutElem.getColor() ] ){
        diffEnergy -= 2*( next.spin(vertex, mutElem.getVertex()) + prev.spin(vertex, mutElem.getVertex()) );
    }

    insertSorted(Valpha, mutElem.getVertex());
    return diffEnergy;

}

template<>
double KineticConflicts::getDifferenceEnergyBounded<Coloring, VertexElementaryMutation>(const Coloring &state, const Coloring &next, const Coloring &prev, const VertexElementaryMutation &mutElem){

    return 4*( state.colorClasses[ state.coloring[mutElem.getVertex()] ].size() + state.colorClasses[ mutElem.getColor() ].size() - 1);

}

#endif // KINETICCONFLICTS_H
