#include "Stoper.h"
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


#include <iostream>

using namespace std::chrono;


Stoper *Stoper::stoper = NULL;

Stoper::Stoper()
{
    this->duration=-1;
}
Stoper::~Stoper()
{

}



Stoper Stoper::getInstance()
{
    if(stoper==nullptr)
        stoper = new Stoper();
    return *stoper;

}

int Stoper::start()
{
    Stoper::t1 = high_resolution_clock::now();
}

int Stoper::stop()
{
    Stoper::t2= high_resolution_clock::now();
    duration = duration_cast<microseconds>( t2 - t1 ).count();
    return duration;
}

long Stoper::getLastMeasure()
{
    return duration;
}

void Stoper::printLastMeasure()
{
    std::cout<<"Czas: "<<duration<<std::endl;
}
