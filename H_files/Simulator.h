#ifndef SIMULATOR_H_
#define SIMULATOR_H_
#include "TreeNode.h"
#include "Tree.h"
#include <string>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;
class Simulator
{
public:
    Simulator();
    void loadCircuit(const string& filepath);
    void simulate(const string& filepath);   
    ~Simulator();
    
private:
    Tree* circuit;
    float Time;

};

#endif