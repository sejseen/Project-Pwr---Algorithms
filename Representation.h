#ifndef REPRESENTATION_H
#define REPRESENTATION_H

class Representation {
public:
    int startingPoint;
    Representation() = default;
    virtual void getMST() = 0;
    virtual void getShortestPath() = 0;
    virtual void addNode()=0;
    virtual void addOneWayNeighbour(int a, int b, int w) = 0;
    virtual void addBothWayNeighbour(int a, int b, int w) = 0;
    virtual void display()=0;
    void addFromFileMST();
    void addFromFileShortestPath();
    void addRandom(int howMany = 15,int percentageDensity= 25,bool trueIfMST = false);
    virtual ~Representation() = default;
};

#endif
