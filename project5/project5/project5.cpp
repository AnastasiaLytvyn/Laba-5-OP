#include <iostream>
#include "ReadFromFile.h"
#include <stack>
//#include <algorithm>
//#include "DataProcessing.h"
using namespace std;

int priorityOfOperation(string operation)
{
	switch (operation[0])
	{
	case '(':
	case ')':
		return 0;
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	case '^':
		return 3;
	case '=':
		return 4;
	default:
		return -1;
	}
}

int findOperatorRight(string str) {
	int operationIndex1 = str.rfind('+');
	int operationIndex2 = str.rfind('-');
	int operationIndex3 = str.rfind('*');
	int operationIndex4 = str.rfind('/');
	int operationIndex5 = str.rfind('^');
	int operationIndex6 = str.rfind('(');
	int operationIndex7 = str.rfind(')');
	int operationIndex8 = str.rfind('=');
	return max(operationIndex8,max(operationIndex7, max(operationIndex6, max(operationIndex5, max(operationIndex4, (max(operationIndex3, (max(operationIndex1, operationIndex2)))))))));
}

int findOperator(string str, int start) {
	int operationIndex1 = str.find('+', start);
	int operationIndex2 = str.find('-', start);
	int operationIndex3 = str.find('*', start);
	int operationIndex4 = str.find('/', start);
	int operationIndex5 = str.find('^', start);
	int operationIndex6 = str.find('(', start);
	int operationIndex7 = str.find(')', start);
	int operationIndex8 = str.find('=', start);

	for (int i = 0; i < str.length(); i++) {
		if (operationIndex1 == i) return operationIndex1;
		else if (operationIndex2 == i) return operationIndex2;
		else if (operationIndex3 == i) return operationIndex3;
		else if (operationIndex4 == i) return operationIndex4;
		else if (operationIndex5 == i) return operationIndex5;
		else if (operationIndex6 == i) return operationIndex6;
		else if (operationIndex7 == i) return operationIndex7;
		else if (operationIndex8 == i) return operationIndex8;
	}
	return -1;
}

string pushOperator(string example, string postfix, stack<string>* operationsstack, int index)
{
	string operationString = example.substr(index, 1);
	if ((*operationsstack).empty())
		(*operationsstack).push(operationString);
	else
	{
		if (operationString[0] == '(') {
			(*operationsstack).push(operationString);
		}
		else if (operationString[0] == ')') {

			while ((*operationsstack).top() != "(") {
				postfix = postfix + (*operationsstack).top() + ' ';
				(*operationsstack).pop();
			}
			(*operationsstack).pop();
		}
		else if (priorityOfOperation(((*operationsstack).top())) >= priorityOfOperation(operationString))
		{
			postfix = postfix + (*operationsstack).top() + ' ';
			(*operationsstack).pop();
			(*operationsstack).push(operationString);
		}
		else
			(*operationsstack).push(operationString);
	}
	return postfix;
}


int main()
{
	ReadFromFile file;
	file.GetName();
	vector<string> info = file.ReadInfo();
	for (size_t i = 0; i < info.size(); i++)
	{
		cout << info[i] << " ";
	}
	cout << endl;
	stack<string> operationsstack;
	string polishNotation = "";
	for (int i = 0; i < info.size(); i++)
	{
		string str = info[i];
		size_t index = 0;
		while ((index = str.find(' ')) != string::npos) str.erase(index, 1);
		int start = 0;
		int operationIndex = findOperator(str, start);
		while (operationIndex >= 0)
		{
			if (!(str.substr(start, operationIndex - start)).empty())
			{
				polishNotation = polishNotation + str.substr(start, operationIndex - start) + ' ';
			}
			polishNotation = pushOperator(str, polishNotation, &operationsstack, operationIndex);
			start = operationIndex + 1;
			operationIndex = findOperator(str, start);
			if (operationIndex < 0) 
			{
				operationIndex = findOperatorRight(str);
				polishNotation = polishNotation + str.substr(operationIndex + 1) + ' ';
				operationIndex = -1;
			}
		}
		while (!operationsstack.empty())
		{
			polishNotation = polishNotation + (operationsstack).top() + ' ';
			(operationsstack).pop();
		}
	}
	cout << polishNotation << " ";
	//DataProcessing process;
	//process.GetValue(info);
	return 0;
}

//добавить обработку, если строки в файле начинаются с пробела " "		///вроде уже добавила
//в конце поменять, чтобы пользователь вводил имя файла(+возможно, добавлять .txt)