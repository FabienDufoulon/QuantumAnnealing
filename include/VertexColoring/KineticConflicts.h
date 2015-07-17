#ifndef KINETICCONFLICTS_H
#define KINETICCONFLICTS_H

#include <Solver/KineticEnergy.h>


class KineticConflicts : public KineticEnergy
{
    public:
        KineticConflicts() {}
        virtual ~KineticConflicts() {}

        template <typename stateType>
        static double getEnergy(const Problem<stateType> &problem) {return KineticEnergy::getEnergy(problem);};

        template <typename stateType, typename elementaryMutation>
        static double getDifferenceEnergy(const stateType &state, const stateType &next, const stateType &prev, const elementaryMutation &mutElem) {return KineticEnergy::getDifferenceEnergy(state, next, prev, mutElem);};

        template <typename stateType, typename elementaryMutation>
        static double getDifferenceEnergyBounded(const stateType &state, const stateType &next, const stateType &prev, const elementaryMutation &mutElem) {return KineticEnergy::getDifferenceEnergyBounded(state, next, prev, mutElem);};

    protected:
    private:
};

template<>
double KineticConflicts::getEnergy<Coloring>(const Problem<Coloring> &problem){
    std::cout << "Wrong place" << std::endl;
    return 0;
}

template<>
double KineticConflicts::getDifferenceEnergy<Coloring, VertexElementaryMutation>(const Coloring &state, const Coloring &next, const Coloring &prev, const VertexElementaryMutation &mutElem){

    //const Coloring* cNext = dynamic_cast<const Coloring*>(state.getNext());
    //std::cout << "state " << typeid(state.getNext()).name() << std::endl;
    //std::cout << "before get" << std::endl;
    //const Coloring* cNext = state.getNext();
    //Coloring cNext = problem.nextStates.find(state)->second;
    //std::cout << "after first get : " << typeid(*cNext).name() << std::endl;
    //if (cNext == nullptr) std::cout << "Fail here" << std::endl;
    //std::cout << cNext->getMaxColors() << std::endl;
    //const Coloring* cPrev = dynamic_cast<const Coloring*>(state.getPrevious());
    //const Coloring* cPrev = state.getPrevious();
    //Coloring cPrev = problem.prevStates.find(state)->second;
    double diffEnergy = 0;
    //std::cout << "KE2" << std::endl;

    std::vector<int> Valpha (state.colorClasses[ state.coloring[mutElem.getVertex()] ] );
    //std::vector<int> Vbeta = state.colorClasses[ mutElem.getColor() ];

    //std::cout << "h" << std::endl;

    //Valpha.erase(mutElem.getVertex());
    eraseSorted(Valpha, mutElem.getVertex());

    for (int vertex : Valpha ){
        diffEnergy += 2*( next.spin(vertex, mutElem.getVertex()) + prev.spin(vertex, mutElem.getVertex()) );
    }

    for (int vertex : state.colorClasses[ mutElem.getColor() ] ){
        diffEnergy -= 2*( next.spin(vertex, mutElem.getVertex()) + prev.spin(vertex, mutElem.getVertex()) );
    }

    insertSorted(Valpha, mutElem.getVertex());
    //Valpha.insert(mutElem.getVertex());

    //std::cout << "KE" << std::endl;

    return diffEnergy;

}

template<>
double KineticConflicts::getDifferenceEnergyBounded<Coloring, VertexElementaryMutation>(const Coloring &state, const Coloring &next, const Coloring &prev, const VertexElementaryMutation &mutElem){

    //std::unordered_set<int> Valpha = state.colorClasses[ state.coloring[mutElem.getVertex()] ];
    //std::unordered_set<int> Vbeta = state.colorClasses[ mutElem.getColor() ];

    return 4*( state.colorClasses[ state.coloring[mutElem.getVertex()] ].size() + state.colorClasses[ mutElem.getColor() ].size() - 1);

}
#endif // KINETICCONFLICTS_H
