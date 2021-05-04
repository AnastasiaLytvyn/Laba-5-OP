#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

class RPN
{
	stack<string> operations;
	int PriorityOfOperation(string);
	int FindOperator(string, int);
	int FindLastOperator(string);
	string PushOperator(string, string, int);
public:
	string GetRPNstring(vector<string>);
};

