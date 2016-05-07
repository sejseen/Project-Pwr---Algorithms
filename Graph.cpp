#include "Graph.h"

#include <Graph.h>
#include <utility>

int Graph::getSize()
{
    return nodes.size();
}

bool Graph::equals(const Graph & b)
{
    if (this->nodes != b.nodes)
        return false;
    return true;
}
void Graph::display()
{
    std::cout << "waga: " << this->weight << std::endl;
    for (auto a : edges)
    {
        std::cout << a[0] << "-" << a[1] << " (" << a[2] << ")";
        std::cout << std::endl;
    }

}

Graph Graph::MakeGraphFromVector(std::vector<int> edge)
{
    Graph a;
    a.nodes.insert(edge[0]);
    a.nodes.insert(edge[1]);
    a.edges.push_back(edge);
    a.weight = edge[2];
    return a;
}
int Graph::FindInGraph(std::vector<Graph>&graphTree, int element)
{
    int i = 0;
    for (auto a : graphTree)
    {
        for (auto node : a.nodes)
            if (node == element)
                return i;
        i++;
    }
}

void Graph::connectTwoGraphs(Graph & a, Graph & b)
{
    /*std::cout<<"----------------------------"<<std::endl;
     a.display();
     b.display();*/

        a.nodes.insert(b.nodes.begin(), b.nodes.end());
        a.edges.insert(a.edges.end(), b.edges.begin(), b.edges.end());
        a.weight += b.weight;
        b.nodes.erase(b.nodes.begin(), b.nodes.end());
        b.edges.erase(b.edges.begin(), b.edges.end());
        b.weight = 0;

        /*a.display();
     b.display();
    std::cout << std::endl;*/
}
void Graph::displayGraphTree(std::vector<Graph> tree)
{
    for (auto a : tree)
    {
        a.display();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool Graph::isInVector(const std::vector<int> &searched,
        const std::vector<std::vector<int>> &vector)
{
    for (auto a : vector)
    {
        if (searched[0] == a[0])
            if (searched[1] == a[1])
                return true;
        if (searched[0] == a[1])
            if (searched[1] == a[0])
                return true;
    }
    return false;
}
