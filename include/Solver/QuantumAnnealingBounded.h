#ifndef QUANTUMANNEALINGBOUNDED_H
#define QUANTUMANNEALINGBOUNDED_H

#include <Solver/Annealing.h>


class QuantumAnnealingBounded : public Annealing
{
    public:
        QuantumAnnealingBounded() {}
        virtual ~QuantumAnnealingBounded() {}

        template <typename stateType, typename potentialEnergy, typename kineticEnergy, typename mutation, typename elementaryMutation>
        void run(Problem<stateType> &problem, double temperature, Function &Gamma, uint32_t seed = time(0));
    protected:
    private:
};

//All parameters assumed to be initiated for a run (Function, Problem)
template <typename stateType, typename potentialEnergy, typename kineticEnergy, typename mutation, typename elementaryMutation>
void QuantumAnnealingBounded::run(Problem<stateType> &problem, double temperature, Function &Gamma,  uint32_t seed){
    //Init random generator for this run.
    rng.seed(seed);
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    //for test
    problem.initStartStates(rng);

    int replicaPalier = 1; //Nombre d'iterations a chaque palier
    double bestEnergy = problem.template getPotentialEnergy<potentialEnergy>(0);
    for (int i = 1; i < problem.states.size(); i++){
        if (problem.template getPotentialEnergy<potentialEnergy>(i) < bestEnergy ) bestEnergy = problem.template getPotentialEnergy<potentialEnergy>(i);
    }
    std::cout << "Starting best energy : " << bestEnergy << std::endl;

    std::unique_ptr<elementaryMutation> mut;
    int replicas = problem.getNumberReplicas();
    double proba = 1;

    double diffPotentialEnergy = 0;
    double diffKineticEnergy = 0;
    double diffKineticEnergyBounded = 0;
    double diffEnergy = 0;
    double currentPotentialEnergy = 0;
    double jGamma = 0;
    double AcceptProba = 0;

    while (Gamma.step() && bestEnergy != 0){
        //shuffle state pointers to mix interactions
        //std::vector<stateType*> shuffledStates(problem.states);
        std::vector<int> shuffledStateIndexes(problem.states.size());
        std::iota(std::begin(shuffledStateIndexes), std::end(shuffledStateIndexes), 0);
        std::random_shuffle(std::begin(shuffledStateIndexes), std::end(shuffledStateIndexes), rng);

        jGamma = -temperature/2*log(tanh(Gamma.getCurrentPoint() / replicas / temperature ));

        for (auto stateIndex : shuffledStateIndexes){
            for (int i = 0 ; i < replicaPalier; i++){
                //std::cout << "in" << std::endl;
                mut = problem.template getMutationElementaire<mutation, elementaryMutation>(stateIndex, rng);

                //Dumb methods for difference in energy (potential and kinetic). If problem is compatible, use the other method
                //which gives out the difference in energy based on the information of the coming mutation(without having to do it).
                //double diffPotentialEnergy = problem.calculatePotentialEnergyDifference(pot, *mutations[0], *mut, *ptState);
                diffPotentialEnergy = problem.template calculatePotentialEnergyDifferenceFast<potentialEnergy, elementaryMutation>(*mut, stateIndex);
                //double diffKineticEnergy = problem.calculateKineticEnergyDifference(kin, *mutations[0], *mut, *ptState);
                //std::cout << "PE" << std::endl;
                diffKineticEnergyBounded = problem.template calculateKineticEnergyDifferenceBounded<kineticEnergy, elementaryMutation>(*mut, stateIndex);
                //std::cout << "KE" << std::endl;
                diffEnergy = diffPotentialEnergy / replicas - diffKineticEnergyBounded * jGamma;

                //std::cout << "DE" << std::endl;

                if (diffPotentialEnergy < 0 ){
                    problem.template change<mutation, elementaryMutation>(*mut, stateIndex);
                    currentPotentialEnergy = problem.template getPotentialEnergy<potentialEnergy>(stateIndex);

                    if (currentPotentialEnergy < bestEnergy){
                        bestEnergy = currentPotentialEnergy;
                        std::cout << "Best Energy : " << bestEnergy << std::endl;

                        if (bestEnergy == 0){
                            std::cout << "end" << std::endl;
                            return;
                        }

                    }

                }
                else {
                    if (diffEnergy <= 0) proba = 1;
                    else proba = exp( -diffEnergy / temperature);

                    AcceptProba = distribution(rng);

                    if (proba >= AcceptProba){

                        diffKineticEnergy = problem.template calculateKineticEnergyDifferenceFast<kineticEnergy, elementaryMutation>(*mut, stateIndex);
                        diffEnergy = diffPotentialEnergy / replicas - diffKineticEnergy * jGamma;

                        if (diffEnergy <= 0) problem.template change<mutation, elementaryMutation>(*mut, stateIndex);
                        else {
                            proba = exp( -diffEnergy / temperature);
                            if (proba > AcceptProba) problem.template change<mutation, elementaryMutation>(*mut, stateIndex);
                        }

                    }
                }
                //std::cout << "end" << std::endl;
            }
        }
    }

}

#endif // QUANTUMANNEALINGBOUNDED_H
