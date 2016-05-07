#include "Matrix.h"

#include <Matrix.h>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <limits>

Matrix::Matrix()
{
    // TODO Auto-generated constructor stub

}

int Matrix::getCoutOfNodes()
{
    return this->matrix.size();
}

Matrix::~Matrix()
{
    // TODO Auto-generated destructor stub
}

int Matrix::getXY()
{
}

void Matrix::getMST()
{
    auto graph = this->Kruskal();
    //graph.display();
}

void Matrix::getShortestPath()
{
    for (int i = 0; i < this->getCoutOfNodes(); i++)
    {
        if (i == startingPoint)
            continue;
        auto list = this->Dijkstry(startingPoint, i);
        auto iterator = list.begin();
        for (int i = 0; i < list.size() - 1; i++, iterator++)
            std::cout << *iterator << ", ";
        std::cout << "(" << *(iterator++) << ")";
        std::cout << std::endl;
    }
}

void Matrix::addNode()
{
    std::vector<int> temp;
    for (int i = 0; i < getCoutOfNodes() + 1; i++)
        temp.push_back(0);
    this->matrix.push_back(temp);

    for (auto node = this->matrix.begin(); node != (this->matrix.end() - 1);
            node++)
        node->push_back(0);
}

void Matrix::addOneWayNeighbour(int a, int b, int w)
{
    //auto indexes = this->askForIndexes();
    this->setNeighbours(a, b, w);
}

void Matrix::addBothWayNeighbour(int a, int b, int w)
{
    //auto indexes = this->askForIndexes();
    this->setNeighbours(a, b, w);
    this->setNeighbours(b, a, w);

}

void Matrix::setNeighbours(int a, int b, int c)
{
    this->matrix[a][b] = c;
}

std::tuple<int, int, int> Matrix::askForIndexes()
{
    int a, b, c;
    std::cout << "podaj indeks pierwszego elementu";
    std::cin >> a;
    std::cout << "podaj indeks drugiego elementu";
    std::cin >> b;
    std::cout << "podaj wage";
    std::cin >> c;

    std::tuple<int, int, int> indexes(a, b, c);
    return indexes;

}

void Matrix::display()
{
    std::cout << "    ";
    for (int i = 0; i < this->getCoutOfNodes(); i++)
        std::cout << i << "  ";
    std::cout << std::endl;

    std::cout << std::endl;

    int i = 0, j = 0;
    for (auto node : this->matrix)
    {
        {
            std::cout << i << "| ";
            for (auto neighbours : node)
                printf("%2d ", neighbours);
            i++;
            std::cout << std::endl;
        }
    }
}

std::list<int> Matrix::Dijkstry(int startNode, int endNode)
{
    std::vector<std::vector<int>> costTable(this->matrix);
    int countOfNodes = getCoutOfNodes();
    //table[0] - numer kolumny
    //table[1] - koszt
    //table[2] - poprzednik
    //table[3] - done
    int ** table = new int*[4];
    for (int i = 0; i < 4; i++)
    {
        table[i] = new int[countOfNodes];
    }

    for (int i = 0; i < countOfNodes; i++)
    {
        table[0][i] = i;
        table[1][i] = std::numeric_limits<int>::max();
        table[2][i] = -1;
        table[3][i] = 0;

    }

    table[1][startNode] = 0;

    while (!allAreDone(table, countOfNodes))
    {

        int minPosition = getMinNotDoneIndex(table, countOfNodes);

        table[3][minPosition] = 1;

        for (int i = 0; i < countOfNodes; i++)
        {
            if (this->matrix[minPosition][i] != 0)//oznacza to że dwa wierzchołki są sąsiadami
            {
                if (table[1][i]
                        > table[1][minPosition] + this->matrix[minPosition][i])
                {
                    table[1][i] = table[1][minPosition]
                            + this->matrix[minPosition][i];
                    table[2][i] = minPosition;
                }
            }
        }

    }

    std::list<int> bestWayList;
    int prev_value = endNode;
    while (prev_value != table[0][startNode])
    {
        bestWayList.push_front(prev_value);
        prev_value = table[2][prev_value];
    }
    bestWayList.push_front(startNode);
    bestWayList.push_back(table[1][endNode]);

    /*for (auto i : bestWayList)
     std::cout << i << " ";*/
    return bestWayList;

}

bool allAreDone(int ** element, int countOfNodes)
{
    bool done = true;
    for (int i = 0; i < countOfNodes; i++)
    {
        if (element[3][i] == 0)
        {
            done = false;
            return done;
        }
    }
    return done;
}

int getMinNotDoneIndex(int** table, int countOfNodes)
{
    int min = INT32_MAX;
    int minPosition = 0;
    int counter = 0;
    for (int i = 0; i < countOfNodes; i++)
    {
        if (table[1][i] < min)
            if (table[3][i] == 0)
            {
                minPosition = counter;
                min = table[1][i];

            }
        counter++;
    }
    return minPosition;
}
//============================================================================
//ALGORYTM KRUSKALA
//============================================================================

const Graph & Matrix::Kruskal()
{
    auto listOfEdgesWithWeigth = GetListOfEdgesWithWeigth();

    std::sort(listOfEdgesWithWeigth.begin(), listOfEdgesWithWeigth.end(),//algorithm sorts descending by weigth
            [](std::vector<int> a, std::vector<int>b)->bool
            {	return a[2]<b[2];});		//i'm using lambda expressin (c++11)

    std::vector<Graph> graphTree;
    for (auto edge : listOfEdgesWithWeigth)
        graphTree.push_back(Graph::MakeGraphFromVector(edge));
    /*

     for(auto a : listOfEdgesWithWeigth)
     {for(auto b: a)
     std::cout<<b<<" ";
     std::cout<<"\n";
     }
     */

    int howManyToConnect = this->getCoutOfNodes();
    int counter = 0;
    for (auto edge : listOfEdgesWithWeigth)
    {
        int first = Graph::FindInGraph(graphTree, edge[0]);
        int second = Graph::FindInGraph(graphTree, edge[1]);
        if (first > second)
            std::swap(first, second);

        //std::cout<<edge[0]<<": "<<first<<" , "<<edge[1]<<": "<<second<<std::endl;
        if (!graphTree[first].equals(graphTree[second]))
        {
            Graph::connectTwoGraphs(graphTree[first], graphTree[second]);
            Graph::connectTwoGraphs(graphTree[first], graphTree[counter]);
        }
        /*for(auto a: graphTree)
         a.display();
         std::cout<<"------------------------------------------"<<std::endl;*/
        counter++;
    }
    graphTree[0].display();
    return graphTree[0];
}

std::vector<std::vector<int>> Matrix::GetListOfEdgesWithWeigth()
{

    std::vector<std::vector<int>> firstSecondWeigth;
    int edgeNumber = 0;
    for (auto edge : matrix)
    {
        int neighbourNumber = 0;
        for (auto neighbourWeigth : edge)
        {
            if (neighbourWeigth != 0)
            {
                std::vector<int> temp;
                temp.push_back(edgeNumber);
                temp.push_back(neighbourNumber);
                temp.push_back(neighbourWeigth);
                if (Graph::isInVector(temp, firstSecondWeigth))
                {
                    neighbourNumber++;
                    continue;
                }
                firstSecondWeigth.push_back(temp);
            }
            neighbourNumber++;

        }
        edgeNumber++;

    }
    return firstSecondWeigth;
}
