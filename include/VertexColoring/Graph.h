#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iostream>

class Graph
{
    public:
        Graph(std::string &textFile);
        virtual ~Graph() {};

        //Stores connections for each vertex to other vertices. (stored is vertex index, so going from 0 to numberOfVertices - 1)
        std::vector<std::vector<double>> connections;
        int getNumberVertices() {return connections.size();};

};

//Functions to make splitting string in text file parsing much easier
// http://stackoverflow.com/questions/236129/split-a-string-in-c
static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

#endif // GRAPH_H
