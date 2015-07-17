#ifndef VERTEXELEMENTARYMUTATION_H
#define VERTEXELEMENTARYMUTATION_H

#include <Solver/ElementaryMutation.h>


class VertexElementaryMutation : public ElementaryMutation
{
    public:
        VertexElementaryMutation(int vertex, int color) : vertex(vertex), color(color) {};
        virtual ~VertexElementaryMutation() {};

        int getVertex() const {return vertex;};
        int getColor() const {return color;};
    protected:
    private:
        int vertex;
        int color;
};

#endif // VERTEXELEMENTARYMUTATION_H
