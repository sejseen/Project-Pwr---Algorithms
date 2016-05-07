#ifndef NEIGHBOORLIST_H
#define NEIGHBOORLIST_H

#include <Representation.h>
#include <Graph.h>
#include <limits>
#include <list>
#include <memory>
#include <set>
#include <tuple>
#include <vector>

class Edge
{
public:
    Edge(int n, int w) :
            neighbourNumer(n), weigth(w)
    {
    }
    ;
    int neighbourNumer;
    int weigth;


    bool operator<(const Edge & a) const
    {
        if (this->neighbourNumer < a.neighbourNumer)
            return true;
        return false;
    }
};

class Node
{
public:
    std::set<Edge> neighbours;
    bool done;
    int cost;
    int prev;
    int number;
    Node()
    {
        number = -1;
        done = false;
        cost = std::numeric_limits<int>::max();
        prev = -1;
    }
    void resetToDjistry()
    {
        done = false;
        cost = std::numeric_limits<int>::max();
        prev= -1;
    }
};

class NeighbourList: public Representation
{

public:
    NeighbourList();
    virtual ~NeighbourList();
    void getMST() override;
    void getShortestPath() override;
    void addNode() override;
    void addOneWayNeighbour(int a, int b, int w) override;
    void addBothWayNeighbour(int a, int b, int w) override;
    void display() override;
    const Graph & Kruskal();
    std::list<int> Dijkstry(int, int);
    std::vector<std::vector<int>>GetListOfEdgesWithWeigth();

    std::vector<std::shared_ptr<Node>> elements;

    std::tuple<int, int, int> askForIndexes();
    void setNeighbours(int a, int b, int c);

};

    bool allAreDone(std::vector<std::shared_ptr<Node>> element);
    int getMinNotDoneIndex(std::vector<std::shared_ptr<Node>> element);
#endif
