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
        //std::vector<std::vector<int>>& getF() const { return F;};
        //std::vector<int>& getColoring() const { return coloring;};
        //std::unordered_set<int>& getVerticesInConflict() const { return verticesInConflict;};
        //std::vector<std::unordered_set<int>>& getColorClasses() const { return colorClasses;};
        int getMaxColors() const {return maxColors;};
        void affectColor(int vertex, int color) {coloring[vertex] = color;};

        bool goodColoring() const;

        //std::vector<std::unordered_set<int>> colorClasses;
        std::vector<std::vector<int>> colorClasses; //Color classes vectors are sorted
        ///Unordered set of vertices in conflict. There are no duplicates due to the nature of the data structure.
        //std::unordered_set<int> verticesInConflict;
        std::vector<int> verticesInConflict; //Vertices in conflict vector is sorted
        std::vector<std::vector<int>> F;
        std::vector<int> coloring;
        std::vector<int> bestColoring;

        /*void setNext(Coloring* n) {std::cout << "setting next "; this->next = n; std::cout << next->getMaxColors() << std::endl;};
        void setPrevious(Coloring* p) {std::cout << "setting prev "; this->previous = p; std::cout << previous->getMaxColors() << std::endl;};
        Coloring* getNext() const {std::cout << "coloring : "; std::cout << typeid(*next).name() << std::endl; return next;};
        Coloring* getPrevious() const {std::cout << "coloring" << std::endl; return previous;};*/

    protected:
        //Coloring* next;
        //Coloring* previous;

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

