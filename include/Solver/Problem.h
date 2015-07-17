#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <map>
#include <memory>

#include <iostream> //test
#include "PCG/pcg_random.hpp"


template <typename stateType>
class Problem
{
    public:
        Problem(std::vector<std::shared_ptr<stateType>> stateVector);
        virtual ~Problem();

        std::vector<std::shared_ptr<stateType>> states;
        //std::map<stateType*,stateType> nextStates;
        //std::map<stateType*,stateType> prevStates;

        template <typename potEnergy, typename elementaryMutation>
        double calculatePotentialEnergyDifferenceFast(const elementaryMutation &mutElem, int stateIndex);

        template <typename potEnergy, typename mutation, typename elementaryMutation>
        double calculatePotentialEnergyDifference(const elementaryMutation &mutElem, int stateIndex);

        template <typename kinEnergy, typename elementaryMutation>
        double calculateKineticEnergyDifferenceFast(const elementaryMutation &mutElem, int stateIndex);

        template <typename kinEnergy, typename elementaryMutation>
        double calculateKineticEnergyDifferenceBounded(const elementaryMutation &mutElem, int stateIndex);

        template <typename kinEnergy, typename mutation, typename elementaryMutation>
        double calculateKineticEnergyDifference(const elementaryMutation &mutElem, int stateIndex);

        template <typename potEnergy>
        double getPotentialEnergy(int stateIndex);

        template <typename mutation, typename elementaryMutation>
        void change(const elementaryMutation &mutElem, int stateIndex);

        template <typename mutation, typename elementaryMutation>
        std::unique_ptr<elementaryMutation> getMutationElementaire(int stateIndex, pcg32 &rng);

        int getNumberReplicas();
        void initStartStates(pcg32 rng);

        std::shared_ptr<stateType> getNext(int stateIndex);
        std::shared_ptr<stateType> getPrevious(int stateIndex);

    protected:
    private:
};

template <typename stateType>
Problem<stateType>::Problem(std::vector<std::shared_ptr<stateType>> stateVector) : states(stateVector)
{
    //std::cout << "Map " << nextStates.max_size() << " " << prevStates.max_size() << std::endl;
    //std::shared_ptr<stateType> previousState(states.back());
    /*for (auto pt : states){
        prevStates.insert(std::make_pair(pt, *previousState));
        nextStates.insert(std::make_pair(previousState, *pt));
        previousState.reset(pt);
    }*/
}

template <typename stateType>
Problem<stateType>::~Problem()
{
    //dtor
}

template <typename stateType>
std::shared_ptr<stateType> Problem<stateType>::getNext(int stateIndex){
    if (stateIndex == states.size() - 1 ) return states[0];
    else return states[stateIndex+1];
    //no overflow treatment
}

template <typename stateType>
std::shared_ptr<stateType> Problem<stateType>::getPrevious(int stateIndex){
    if (stateIndex == 0 ) return states[states.size() - 1];
    else return states[stateIndex-1];
    //no overflow treatment
}


template <typename stateType>
template <typename potEnergy, typename elementaryMutation>
double Problem<stateType>::calculatePotentialEnergyDifferenceFast(const elementaryMutation &mutElem, int stateIndex){
    //if (getPotentialEnergy(pot, state) < 0) std::cout << "Calculating DEp : " << getPotentialEnergy(pot, state) << std::endl;
    return potEnergy::template getDifferenceEnergy<stateType, elementaryMutation>(*states[stateIndex], mutElem);
}

template <typename stateType>
template <typename potEnergy, typename mutation, typename elementaryMutation>
double Problem<stateType>::calculatePotentialEnergyDifference(const elementaryMutation &mutElem, int stateIndex){
    //std::cout << "Calculating DEp : " << getPotentialEnergy(pot, state) << std::endl;
    double energy = potEnergy::template getEnergy<stateType>(*states[stateIndex]);
    mutation::template DoMutation(*states[stateIndex], mutElem);
    double energyAfterMutation = potEnergy::template getEnergy<stateType>(*states[stateIndex]);
    mutation::template DoMutation(*states[stateIndex], *(states[stateIndex]->backMutation));
    //std::cout << "finished DEp : " << getPotentialEnergy(pot, state) << std::endl;

    return energyAfterMutation-energy;
}

template <typename stateType>
template <typename kinEnergy, typename elementaryMutation>
double Problem<stateType>::calculateKineticEnergyDifferenceFast(const elementaryMutation &mutElem, int stateIndex){
    //std::cout << "in problem" << std::endl;
    return kinEnergy::template getDifferenceEnergy<stateType, elementaryMutation>(*states[stateIndex], *getNext(stateIndex),
                                                                                   *getPrevious(stateIndex), mutElem);
}

template <typename stateType>
template <typename kinEnergy, typename elementaryMutation>
double Problem<stateType>::calculateKineticEnergyDifferenceBounded(const elementaryMutation &mutElem, int stateIndex){
    //std::cout << "in problem" << std::endl;
    return kinEnergy::template getDifferenceEnergyBounded<stateType, elementaryMutation>(*states[stateIndex], *getNext(stateIndex),
                                                                                   *getPrevious(stateIndex), mutElem);
}

template <typename stateType>
template <typename kinEnergy, typename mutation, typename elementaryMutation>
double Problem<stateType>::calculateKineticEnergyDifference(const elementaryMutation &mutElem, int stateIndex){
    double energy = kinEnergy::template getEnergy<stateType>(*this);
    mutation::template DoMutation(*states[stateIndex], mutElem);
    double energyAfterMutation = kinEnergy::template getEnergy<stateType>(*this);
    mutation::template DoMutation(*states[stateIndex], *(states[stateIndex]->backMutation));

    return energyAfterMutation-energy;
}

template <typename stateType>
template <typename potEnergy>
double Problem<stateType>::getPotentialEnergy(int stateIndex){
    //std::cout << "BC" << std::endl;
    return potEnergy::template getEnergy<stateType>(*states[stateIndex]);
}

template <typename stateType>
template <typename mutation, typename elementaryMutation>
void Problem<stateType>::change(const elementaryMutation &mutElem, int stateIndex){
    mutation::template DoMutation(*states[stateIndex], mutElem);
}

template <typename stateType>
template <typename mutation, typename elementaryMutation>
std::unique_ptr<elementaryMutation> Problem<stateType>::getMutationElementaire(int stateIndex, pcg32 &rng){
    return mutation::template getElementaryMutation<stateType, elementaryMutation>(*states[stateIndex], rng);
}

template <typename stateType>
int Problem<stateType>::getNumberReplicas(){
    return states.size();
}

template <typename stateType>
void Problem<stateType>::initStartStates(pcg32 rng){
    for (auto s : states){
        s->initStart(rng);
    }
}

#endif // PROBLEM_H
