#include "Representation.h"

#include <Representation.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void Representation::addRandom(int howMany, int percentageDensity,
        bool trueIfMST)
{
    srand(time(NULL));
    int modulo = 100 / percentageDensity;
    this->startingPoint = rand()%howMany;
    for (int i = 0; i < howMany; i++)
        this->addNode();
    int counter = 1;
    if (trueIfMST)
    {
        for (int i = 0; i < howMany - 1; i++)
        {
            this->addBothWayNeighbour(i, i + 1, rand() % 20 + 1);
        }
        this->addBothWayNeighbour(howMany - 1, 0, rand() % 20 + 1);

        for (int i = 0; i < howMany; i++)
        {
            for (int j = counter; j < howMany; j++)
            {
                if ((j + i) % modulo == 0)
                    this->addBothWayNeighbour(i, j, rand() % 20 + 1);

            }
            counter++;
        }

    }
    else
    {
        for (int i = 0; i < howMany - 1; i++)
        {
            this->addBothWayNeighbour(i, i + 1, rand() % 20 + 1);
        }
        this->addBothWayNeighbour(howMany - 1, 0, rand() % 20 + 1);
        for (int i = 0; i < howMany; i++)
        {
            for (int j = 0; j < howMany; j++)
            {
                if (j % modulo == 0)
                    this->addOneWayNeighbour(i, j, rand() % 20 + 1);

            }
        }
    }
}

void Representation::addFromFileMST()
{

    std::string filePath;
     std::cout << "podaj sciezke do pliku: ";
     std::cin >> filePath;
    std::fstream plik;

    plik.open(filePath, std::ios::in);

    if (plik.is_open())
    {
        std::string howManyNodes;
        std::string howManyConnections;

        plik >> howManyConnections;
        plik >> howManyNodes;
        for (int i = 0; i < stoi(howManyNodes); i++) ///std::stoi(string) zamienia string na int
            this->addNode();
        for (int i = 0; i < stoi(howManyConnections); i++) ///std::stoi(string) zamienia string na int
        {
            int first, second, weigth;
            plik >> first;
            plik >> second;
            plik >> weigth;
            this->addBothWayNeighbour(first, second, weigth);
        }

    }
    else
    {
        std::cout << "nie znalazelm pliku";

    }

}

void Representation::addFromFileShortestPath()
{
    std::string filePath;
     std::cout << "podaj sciezke do pliku: ";
     std::cin >> filePath;
    std::fstream plik;

    plik.open(filePath,
            std::ios::in);

    if (plik.is_open())
    {
        std::string howManyNodes;
        std::string howManyConnections;

        plik >> howManyConnections;
        plik >> howManyNodes;
        plik >> startingPoint;
        for (int i = 0; i < stoi(howManyNodes); i++) ///std::stoi(string) zamienia string na int
            this->addNode();
        for (int i = 0; i < stoi(howManyConnections); i++) ///std::stoi(string) zamienia string na int
        {
            int first, second, weigth;
            plik >> first;
            plik >> second;
            plik >> weigth;
            this->addOneWayNeighbour(first, second, weigth);
        }

    }
    else
    {
        std::cout << "nie znalazelm pliku";

    }
}
