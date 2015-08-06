#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <Solver/Annealing.h>


class SimulatedAnnealing : public Annealing
{
    public:
        SimulatedAnnealing() {};
        virtual ~SimulatedAnnealing() {};

        template <typename stateType, typename potentialEnergy, typename mutation, typename elementaryMutation>
        void run(Problem<stateType> &problem, Function &Temperature, uint32_t seed = time(0));

};

//All parameters assumed to be initiated for a run (Function, Problem)
template <typename stateType, typename potentialEnergy, typename mutation, typename elementaryMutation>
void SimulatedAnnealing::run(Problem<stateType> &problem, Function &Temperature, uint32_t seed) {

    //Init random generator for this run.
    rng.seed(seed);
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    problem.initStartStates(rng);

    auto bestEnergy = problem.template getPotentialEnergy<potentialEnergy>(0);
    std::cout << "Starting best energy : " << bestEnergy << std::endl;

    //std::unique_ptr<elementaryMutation> mut;

    while (Temperature.step() && bestEnergy != 0){

        auto mut = problem.template getMutationElementaire<mutation, elementaryMutation>(0, rng);
        //diffEnergy = problem.calculatePotentialEnergyDifference(pot, *mutations[0], *mut, *problem.states[0]);
        auto diffEnergy = problem.template calculatePotentialEnergyDifferenceFast<potentialEnergy, elementaryMutation>(*mut, 0);

        if (diffEnergy <= 0 ) {
            problem.template change<mutation, elementaryMutation>(*mut, 0);

            auto currentPotentialEnergy = problem.template getPotentialEnergy<potentialEnergy>(0);
            if (currentPotentialEnergy < bestEnergy) {
                bestEnergy = currentPotentialEnergy;
                std::cout << "Best Energy : " << bestEnergy << std::endl;
            }
        }
        else {
            auto proba = exp( -diffEnergy / Temperature.getCurrentPoint());
            if (proba > distribution(rng)){
                problem.template change<mutation, elementaryMutation>(*mut, 0);
            }
        }


    }

}

#endif // SIMULATEDANNEALING_H
