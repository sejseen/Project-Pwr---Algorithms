#ifndef MATRIX_H
#define MATRIX_H

#include <Representation.h>
#include <list>
#include <tuple>
#include <vector>
#include <Graph.h>




class Matrix: public Representation {
public:
    int width;
    int height;
    std::vector<std::vector<int>> matrix;

    Matrix();
    int getXY();
    void getMST() override;
    void getShortestPath() override;
    void addNode() override;
    void addOneWayNeighbour(int a, int b, int w) override;
    void addBothWayNeighbour(int a, int b, int w) override;
    void display() override;
    int getCoutOfNodes();

    const Graph & Kruskal();
    std::vector<std::vector<int>> GetListOfEdgesWithWeigth();


    void setNeighbours(int a, int b, int c);
    std::list<int> Dijkstry(int startNode, int endNode);
    std::tuple<int, int, int> askForIndexes();


    virtual ~Matrix();
};
int getMinNotDoneIndex(int** table, int countOfNodes);
bool allAreDone(int ** element, int countOfNodes);

#endif
