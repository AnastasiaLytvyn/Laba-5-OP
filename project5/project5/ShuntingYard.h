#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

using namespace std;

class ShuntingYard
{
public:
	map<string, int> OperatorsMap();
	void DataProcessing(vector<string>);
};
