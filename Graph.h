#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <vector>

class Graph{
public:
    std::set<int> nodes;
    std::vector<std::vector<int>> edges;
    int weight;
    int getSize();
    bool equals(const Graph & b);
    void display();
    static Graph MakeGraphFromVector(std::vector<int> edge);
    static int FindInGraph(std::vector<Graph>&graphTree, int element);
    static void connectTwoGraphs(Graph & a, Graph & b);
    static void displayGraphTree(std::vector<Graph> tree);
    static bool isInVector(const std::vector<int> &searched,const std::vector<std::vector<int>> &vector);



};


#endif /* GRAPH_H_ */
