#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include "AST.h"

using namespace std;


class ShuntingYard
{
public:
    map<char, int> OperatorsMap();
    Node* DataProcessing(vector<string>);
};

