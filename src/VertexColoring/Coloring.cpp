#include "VertexColoring/Coloring.h"

Coloring::Coloring(Graph &g, int colors) : graph(g), maxColors(colors), edgesInConflict(0)
{
    coloring = std::vector<int>(graph.getNumberVertices(), 0);
    bestColoring = std::vector<int>(graph.getNumberVertices(), 0);
    F = std::vector<std::vector<int>>(graph.getNumberVertices(), std::vector<int>(maxColors, 0));
    colorClasses = std::vector<std::vector<int>>(maxColors, std::vector<int>{});
}

Coloring::~Coloring() {}

void Coloring::initStart(pcg32 &rng){
    std::uniform_int_distribution<int> distribution(0,maxColors-1);
    for (int i = 0; i < coloring.size(); i++){
        coloring[i] = distribution(rng);
        //Initialize color classes.
        colorClasses[coloring[i]].push_back(i); //In sorted order
    }

    for (int vertex = 0; vertex < coloring.size(); vertex++){
        for (auto adjacentVertex : graph.connections[vertex]){
            //Initialize vertices in conflict and the F vector.
            if (coloring[vertex] == coloring[adjacentVertex]){
                insertSorted(verticesInConflict, vertex); //In sorted order
                ++edgesInConflict;
            }
            ++F[vertex][coloring[adjacentVertex]];
        }
    }

    edgesInConflict /= 2;
    std::cout << "rand init " << edgesInConflict << std::endl;
}

void Coloring::updateLocal(int vertex, int previousColor){
    //Vertex and color from 0 to bound-1

    //Update Color classes
    eraseSorted(colorClasses[previousColor], vertex);
    insertSorted(colorClasses[coloring[vertex]], vertex);

    for (auto v : graph.connections[vertex]){
        //Update F
        ++F[v][coloring[vertex]];
        --F[v][previousColor];

        //Mise a jour des conflits
        if (coloring[v] == previousColor){
            --edgesInConflict;
            if(!inConflict(v)) eraseSorted(verticesInConflict, v);
        }
        if(coloring[v]  == coloring[vertex]){
            ++edgesInConflict;
            insertSorted(verticesInConflict, v);
        }
    }
    //If vertex not in conflict, remove it from the vertices in conflict set.
    if (!inConflict(vertex)) eraseSorted(verticesInConflict, vertex);

    this->backMutation.reset( new VertexElementaryMutation(vertex, previousColor) );

}

bool Coloring::inConflict(int vertex) const{
    bool conflict = false;
    for (auto v : graph.connections[vertex]){
        if (coloring[vertex] == coloring[v]){
            conflict = true;
            break;
        }
    }
    return conflict;
}

int Coloring::spin(int vertex, int vertex2) const{
    if (coloring[vertex] == coloring[vertex2]) return -1;
    else return 1;
}

void Coloring::saveColoring(){
    bestColoring = std::vector<int>(coloring);
}

bool Coloring::goodColoring() const{
    for (int v = 0; v < coloring.size(); v++){
        if ( inConflict(v) ) return false;
    }
    return true;
}
