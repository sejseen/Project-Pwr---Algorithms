#include "Neighboorlist.h"

#include "Neighboorlist.h"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>

NeighbourList::NeighbourList()
{
    // TODO Auto-generated constructor stub

}

NeighbourList::~NeighbourList()
{
    // TODO Auto-generated destructor stub
}

void NeighbourList::getMST()		//funkcja pobierająca drzewo MST
{
    auto graph = this->Kruskal();
    //graph.display();
}

void NeighbourList::getShortestPath()	//funkcja pobierająca najkrótszą drogę
{
    for (auto node : this->elements)	//alalizuje wszystkie najkrótsze ścieżki
    {
        if (node->number == startingPoint)
            continue;
        auto list = this->Dijkstry(startingPoint, node->number);	//zwraca liste zawierającą droge od startu do szukanej
        auto iterator = list.begin();
        for (int i=0; i<list.size()-1; i++,iterator++)
            std::cout << *iterator << ", ";
        std::cout << "(" << *(iterator++) << ")";
        std::cout << std::endl;
    }
}

void NeighbourList::addNode()			//dodaje wierzchołek do listy
{

    std::unique_ptr<Node> newNode(new Node);
    newNode->number = this->elements.size();
    this->elements.push_back(std::move(newNode));

}

void NeighbourList::display()			//wyświetla graf w postaci listowej
{
    for (auto &i : this->elements)
    {
        std::cout << i->number << ": ";
        for (auto &neighbour : i->neighbours)
            std::cout << neighbour.neighbourNumer << "(" << neighbour.weigth
                    << ")" << " ";
        std::cout << "\n";
    }
}

std::tuple<int, int, int> NeighbourList::askForIndexes()		//nie użwywana ale służy do komunikacji z użytkownikiem
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

std::list<int> NeighbourList::Dijkstry(int startNode, int endNode)		//szuka najkrótszej drogi pomiędzy startNode a endNode
{
    for (auto i : this->elements)			//zeruje cost oraz prev
        i->resetToDjistry();
    this->elements[startNode]->cost = 0;

    while (!allAreDone(this->elements))
    {

        int minPosition = getMinNotDoneIndex(this->elements);		//pobieram minimalny nie zrobiony

        this->elements[minPosition]->done = true;	//ustawiam jako zrobiony

        for (auto edge : this->elements[minPosition]->neighbours)
        {
            if (elements[edge.neighbourNumer]->cost	> this->elements[minPosition]->cost + edge.weigth)	//przelatuje po sąsiadach i jeżeli ich koszt może być mniejszy to go aktualizuje
            {
                elements[edge.neighbourNumer]->cost =	elements[minPosition]->cost + edge.weigth;
                elements[edge.neighbourNumer]->prev = minPosition;
            }
        }

    }
    std::list<int> bestWayList;		//tutaj będzie wynik
    int prev_value = endNode;
    while (prev_value != elements[startNode]->number)		//przechodzę po elementach od końca aż dojde do startu
    {
        bestWayList.push_front(prev_value);
        prev_value = elements[prev_value]->prev;
    }
    bestWayList.push_front(startNode);	//dodaje start
    bestWayList.push_back(elements[endNode]->cost); //na koniec wrzucam koszt przejśca
    /*for(auto i: bestWayList)
     std::cout<<i<<" ";*/
    return bestWayList;

}

bool allAreDone(std::vector<std::shared_ptr<Node>> element)		//sprawdzam czy wszystkie są zrobione
{
    bool done = true;
    for (auto a : element)
    {
        if (a->done == false)
        {
            done = false;
            return done;
        }
    }
    return done;
}

int getMinNotDoneIndex(std::vector<std::shared_ptr<Node>> element)
{
    int min = INT32_MAX;
    int minPosition = 0;
    int counter = 0;
    for (auto a : element)
    {
        if (a->cost < min)
            if (a->done == false)
            {
                minPosition = counter;
                min = a->cost;

            }
        counter++;
    }
    return minPosition;
}

const Graph & NeighbourList::Kruskal()		//algorytm kruskala
{
    auto listOfEdgesWithWeigth = GetListOfEdgesWithWeigth();	//pobieram w formie listy 3 elementów wszystkie krawędzie

    std::sort(listOfEdgesWithWeigth.begin(), listOfEdgesWithWeigth.end(), //algorytm sortuje rosnąco względem wag
            [](std::vector<int> a, std::vector<int>b)->bool
            {	return a[2]<b[2];});		//i'm using lambda expressin (c++11)

    std::vector<Graph> graphTree;
    for (auto edge : listOfEdgesWithWeigth)
        graphTree.push_back(Graph::MakeGraphFromVector(edge));


    /* for(auto a : listOfEdgesWithWeigth)
     {for(auto b: a)
     std::cout<<b<<" ";
     std::cout<<"\n";
     }*/


    int howManyToConnect = this->elements.size();
    int counter=0;
    for (auto edge : listOfEdgesWithWeigth)
    {
        int first = Graph::FindInGraph(graphTree, edge[0]);
        int second = Graph::FindInGraph(graphTree, edge[1]);
        if(first>second)
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
    /*for(auto a: graphTree)
        a.display();*/
    graphTree[0].display();
    return graphTree[0];
}

void NeighbourList::addOneWayNeighbour(int a, int b, int w)
{
    //auto indexes = this->askForIndexes();
    this->setNeighbours(a, b, w);
}

void NeighbourList::addBothWayNeighbour(int a, int b, int w)
{
    //auto indexes = this->askForIndexes();
    this->setNeighbours(a, b, w);
    this->setNeighbours(b, a, w);

}

std::vector<std::vector<int>> NeighbourList::GetListOfEdgesWithWeigth()
{

    std::vector<std::vector<int>> firstSecondWeigth;
    for (auto edge : elements)
    {
        for (auto neighbour : edge->neighbours)
        {
            std::vector<int> temp;
            temp.push_back(edge->number);
            temp.push_back(neighbour.neighbourNumer);
            temp.push_back(neighbour.weigth);
            if (Graph::isInVector(temp, firstSecondWeigth))
                continue;
            firstSecondWeigth.push_back(temp);
        }

    }
    return firstSecondWeigth;
}

void NeighbourList::setNeighbours(int a, int b, int c)
{

    this->elements[a]->neighbours.insert(Edge(b, c));

}
