#include <iostream>

#include "Solver/Problem.h"
#include "Solver/Mutation.h"
#include "Solver/LinearFunction.h"
#include "Solver/SimulatedAnnealing.h"
#include "Solver/QuantumAnnealing.h"

#include "VertexColoring/Graph.h"
#include "VertexColoring/Coloring.h"
#include "VertexColoring/Conflicts.h"
#include "VertexColoring/KineticConflicts.h"
#include "VertexColoring/VertexConflictMutation.h"


int main ()
{
    auto textFile = std::string("data/dsjc250.5.col");
    //std::string textFile = "data/dsjc500.5.col";
    auto g = Graph(textFile);

    auto color = 28;
    std::vector<std::shared_ptr<Coloring>> stateVector;
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, color)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, color)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, color)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, color)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, color)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, color)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, color)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, color)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, color)) );
    stateVector.push_back( std::shared_ptr<Coloring>(new Coloring(g, color)) );
    auto p = Problem<Coloring>(stateVector);

    auto gamma = LinearFunction(0.75,0,10000,4*g.getNumberVertices()*color); //*28

    //auto annealing = SimulatedAnnealing();
    auto quantumAnnealing = QuantumAnnealing();
    std::cout << "Start" << std::endl;
    //annealing.run<Coloring, Conflicts, VertexConflictMutation, VertexElementaryMutation>(p, temperature, 3100);
    quantumAnnealing.runBounded<Coloring, Conflicts, KineticConflicts, VertexConflictMutation, VertexElementaryMutation>
                        (p, 0.35 / stateVector.size(), gamma, 2078);

    return 0;
}
