#include <iostream>
#include "Solver/Problem.h"

#include "VertexColoring/Graph.h"
#include "VertexColoring/Coloring.h"
#include "Solver/Mutation.h"
#include "Solver/LinearFunction.h"
#include "VertexColoring/Conflicts.h"
#include "Solver/SimulatedAnnealing.h"
#include "VertexColoring/KineticConflicts.h"
#include "Solver/QuantumAnnealing.h"
#include "Solver/QuantumAnnealingBounded.h"
#include "VertexColoring/VertexConflictMutation.h"


int main ()
{
    //std::cin.get();

    //std::string textFile = "data/dsjc250.5.col";
    std::string textFile = "data/dsjc500.5.col";
    Graph g = Graph(textFile);

    std::vector<std::shared_ptr<Coloring>> stateVector;
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, 48)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, 48)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, 48)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, 48)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, 48)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, 48)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, 48)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, 48)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, 48)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, 48)) );
    Problem<Coloring> p = Problem<Coloring>(stateVector);

    LinearFunction gamma = LinearFunction(0.75,0,100000,4*g.getNumberVertices()*28); //*28

    //SimulatedAnnealing annealing = SimulatedAnnealing();
    //QuantumAnnealing quantumAnnealing = QuantumAnnealing();
    QuantumAnnealingBounded quantumAnnealing = QuantumAnnealingBounded();
    std::cout << "Start" << std::endl;
    //annealing.run<Coloring, Conflicts, VertexConflictMutation, VertexElementaryMutation>(p, temperature, 3100);
    quantumAnnealing.run<Coloring, Conflicts, KineticConflicts, VertexConflictMutation, VertexElementaryMutation>
                        (p, 0.35 / stateVector.size(), gamma, 20378);

    return 0;
}
