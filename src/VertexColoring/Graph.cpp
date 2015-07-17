#include "VertexColoring/Graph.h"

Graph::Graph(std::string &textFile)
{
    std::ifstream inFile(textFile.c_str());
    std::string strOneLine;

    if (!inFile) std::cout << "File not found." << std::endl;

    while (inFile){
        getline(inFile, strOneLine);
        std::vector<std::string> line = split(strOneLine, ' ');
        if (line.empty()) break;
        if (line[0] == "p"){
            int vertices = std::stoi(line[2]);
            connections = std::vector<std::vector<double>>(vertices, std::vector<double> {});
        }
        else if(line[0] == "e" ){
            //int firstVertexIndex = std::stoi(line[1]) - 1;
            //int secondVertexIndex = std::stoi(line[2]) - 1;
            connections[std::stoi(line[1]) - 1].push_back(std::stoi(line[2]) - 1);
            connections[std::stoi(line[2]) - 1].push_back(std::stoi(line[1]) - 1);
        }
    }

}

Graph::~Graph()
{
    //dtor
}

int Graph::getNumberVertices(){
    return connections.size();
}
