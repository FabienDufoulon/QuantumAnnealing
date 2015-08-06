#ifndef COLORING_H
#define COLORING_H

#include "Solver/State.h"
#include "VertexColoring/Graph.h"
#include <random>
#include <algorithm>
#include "VertexColoring/VertexElementaryMutation.h"

class Coloring : public State
{
    public:
        Coloring(Graph &g, int colors);
        virtual ~Coloring();

        void initStart(pcg32 &rng);
        void updateLocal(int vertex, int previousColor);
        int spin(int vertex, int vertex2) const;

        int getNumberOfEdgesInConflict() const { return edgesInConflict;};
        int getMaxColors() const {return maxColors;};
        void affectColor(int vertex, int color) {coloring[vertex] = color;};

        bool goodColoring() const;

        std::vector<std::vector<int>> colorClasses; //Color classes vectors are sorted
        ///Unordered set of vertices in conflict. There are no duplicates due to the nature of the data structure.
        std::vector<int> verticesInConflict; //Vertices in conflict vector is sorted
        std::vector<std::vector<int>> F;
        std::vector<int> coloring;
        std::vector<int> bestColoring;

    private:
        Graph& graph;
        int maxColors;
        int edgesInConflict;

        bool inConflict(int vertex) const;

        void saveColoring();
};

template <typename Vector, typename T>
static void eraseSorted(Vector &vec, T value)
{
    auto pr = std::equal_range(std::begin(vec), std::end(vec), value);
    vec.erase(pr.first, pr.second);
}

template <typename Vector, typename T>
static void insertSorted(Vector &vec, T value){
    typename Vector::iterator i = std::lower_bound( std::begin(vec), std::end(vec), value );
    if (i == std::end(vec) || value < *i){
        vec.insert(i, value);
    }
}


#endif // COLORING_H

