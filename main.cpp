#include <QCoreApplication>
#include <iostream>>

#include <Matrix.h>
#include <Neighboorlist.h>
#include <Stoper.h>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <limits> ///tutaj jest klasa numeric_limits
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

Representation* chooseRepresentation(int &reprInt);
int chooseAlgorithm();

int main()
{

    char ster = 'x';
    Stoper stoper = Stoper::getInstance();
    int reprInt;
    std::shared_ptr<Representation> representation(
            chooseRepresentation(reprInt)); ///odkomentowac
    int problem = chooseAlgorithm(); 	//#1 - MST , 2 - najkrótsza droga
    //Representation *representation = new BST();

    while (ster != 'k')
    {
        system("clear");
        representation->display();
        cout << "\na - dodaj ciag testowy"
                "\nf - dodaj z pliku"
                "\ns - start"
                "\np - zmien problem"
                "\nc - zmien strukture"
                "\nk - zakoncz porgram\n";

        cin >> ster;
        cout << ster << endl;
        cin.clear();
        try
        {
            switch (ster)
            {
            case 'a':
            {
                representation->addRandom();
                break;
            }

            case 'f':
            {
                if (problem == 1)
                    representation->addFromFileMST();
                else if (problem == 2)
                    representation->addFromFileShortestPath();

                break;
            }
            case 's':
            {
                if (problem == 1)
                    representation->getMST();
                else if (problem == 2)
                    representation->getShortestPath();
                break;
            }
            case 'p':
            {
                problem = chooseAlgorithm(); //#1 - MST , 2 - najkrótsza droga
                if (reprInt == 1)
                    representation.reset(new NeighbourList);
                if (reprInt == 2)
                    representation.reset(new Matrix);

                break;
            }
            case 'c':
            {
                representation.reset(chooseRepresentation(reprInt));
                break;
            }
            case 'k':
            {
                break;
            }
            default:
            {
                printf("BLAD: wybrano bledna opcje\n");
                cin.clear();
                cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            }

            }

        } catch (length_error &a)
        {
            cout << a.what();
        } catch (...)
        {
            cout << "BLAD najprawdopodobniej wczytano zla wartosc\n";
        }

        char t;
        while ((t = getchar()) != EOF && t != '\n')
            continue;        //czyści bufor czekając na ENTER
        getchar();
    }
}

int chooseAlgorithm()
{
    int value;
    for (;;)
    {
        system("clear");

        string info = "wybierz problem:\n[1] - MST \n[2] - najkrótsza droga\n";
        cout << info;
        cin >> value;

        if (!isdigit(value))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); ///numeric_limits<streamsize>::max()  oznacza ze cin.ignore ma zignorowac wszystkie znaki z bufora az do \n
        }

        switch (value)
        {
        case 1:
        {
            return 1;
        }
        case 2:
        {
            return 2;
        }

        default:
        {
            cout << "BLAD zly wybor\n";
        }
        }
    }
}
Representation* chooseRepresentation(int &reprInt)
{
    int value;
    for (;;)
    {
        system("clear");

        string info =
                "wybierz strukture do testu:\n[1] - lista\n[2] - macierz\n";
        cout << info;
        cin >> value;

        if (!isdigit(value))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); ///numeric_limits<streamsize>::max()  oznacza ze cin.ignore ma zignorowac wszystkie znaki z bufora az do \n
        }

        switch (value)
        {
        case 1:
        {
            reprInt = 1;
            return new NeighbourList;
        }
        case 2:
        {
            reprInt = 2;
            return new Matrix;
        }

        default:
        {
            cout << "BLAD zly wybor\n";
        }
        }
    }
}
