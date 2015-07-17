#ifndef VERTEXCONFLICTMUTATION_H
#define VERTEXCONFLICTMUTATION_H

#include <Solver/Mutation.h>
#include "VertexColoring/Coloring.h"


class VertexConflictMutation : public Mutation
{
    public:
        VertexConflictMutation() {};
        virtual ~VertexConflictMutation() {};

        template <typename stateType, typename elemMutation>
        static void DoMutation(stateType &state, const elemMutation &mut) { Mutation::DoMutation(state,mut); }; //Requires to update backMutation in State (so change can be turned back).

        template <typename stateType, typename elemMutation>
        static std::unique_ptr<elemMutation> getElementaryMutation(const stateType &state, pcg32 &rng) { return Mutation::getElementaryMutation(state,rng); };
    protected:
    private:
};

template<>
void VertexConflictMutation::DoMutation<Coloring, VertexElementaryMutation>(Coloring &state, const VertexElementaryMutation &mut){

    int previousColor = state.coloring[mut.getVertex()];

    //if (previousColor == m.getColor()) return;
    state.affectColor(mut.getVertex(), mut.getColor());
    //std::cout << previousColor << "c" << m.getColor() << std::endl;
    state.updateLocal(mut.getVertex(), previousColor);
	//Requires to update backMutation in State (so change can be turned back).
}

template<>
std::unique_ptr<VertexElementaryMutation> VertexConflictMutation::getElementaryMutation<Coloring, VertexElementaryMutation>(const Coloring &state, pcg32 &rng){
    std::uniform_int_distribution<int> distributionVertex(0, state.verticesInConflict.size()-1);
    int randomVertex = distributionVertex(rng);
    randomVertex = state.verticesInConflict[randomVertex];
    //std::cout << randomVertex << " " << c.getVerticesInConflict().size() << std::endl;

    /*for (auto it : state.verticesInConflict){
        if (randomVertex == 0) {
            randomVertex = it;
            break;
        }
        --randomVertex;
    }*/

    std::uniform_int_distribution<int> distributionCouleur(0, state.getMaxColors()-1);
    int randomColor = distributionCouleur(rng);
    //What if it's the same color??? let QA take care of it.

    return std::unique_ptr<VertexElementaryMutation>(new VertexElementaryMutation(randomVertex, randomColor));
}

#endif // VERTEXCONFLICTMUTATION_H
