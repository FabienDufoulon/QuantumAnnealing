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

    protected:
    private:
};

//All parameters assumed to be initiated for a run (Function, Problem)
template <typename stateType, typename potentialEnergy, typename mutation, typename elementaryMutation>
void SimulatedAnnealing::run(Problem<stateType> &problem, Function &Temperature, uint32_t seed) {

    //Init random generator for this run.
    rng.seed(seed);
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    //for test
    problem.initStartStates(rng);

    double bestEnergy = problem.template getPotentialEnergy<potentialEnergy>(0);
    std::cout << "Starting best energy : " << bestEnergy << std::endl;

    std::unique_ptr<elementaryMutation> mut;
    double proba = 1;
    double diffEnergy = 0;
    double currentPotentialEnergy = 0;

    while (Temperature.step() && bestEnergy != 0){
        //std::cout << "Temperature : " << Temperature.getCurrentPoint() << " at step " << Temperature.getStepPlateau() << std::endl;

        mut = problem.template getMutationElementaire<mutation, elementaryMutation>(0, rng);
        //double diffEnergy = problem.calculatePotentialEnergyDifference(pot, *mutations[0], *mut, *problem.states[0]);
        diffEnergy = problem.template calculatePotentialEnergyDifferenceFast<potentialEnergy, elementaryMutation>(*mut, 0);

        if (diffEnergy <= 0 ) {
            problem.template change<mutation, elementaryMutation>(*mut, 0);
            //std::cout << "Mutation done " << std::endl;

            currentPotentialEnergy = problem.template getPotentialEnergy<potentialEnergy>(0);
            if (currentPotentialEnergy < bestEnergy) {
                bestEnergy = currentPotentialEnergy;
                std::cout << "Best Energy : " << bestEnergy << std::endl;
            }
        }
        else {
            proba = exp( -diffEnergy / Temperature.getCurrentPoint());
            //std::cout << "Mutation " << std::endl;
            if (proba > distribution(rng)){
                problem.template change<mutation, elementaryMutation>(*mut, 0);
                //std::cout << "Mutation done " << std::endl;
            }
            //else std::cout << "No Mutation done " << std::endl;
        }


    }

}

#endif // SIMULATEDANNEALING_H
