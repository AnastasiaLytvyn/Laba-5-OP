#include "RPN.h"

int RPN::PriorityOfOperation(string operation)
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

int RPN::FindOperator(string str, int start)
{
	int operationIndex1 = str.find('+', start);
	int operationIndex2 = str.find('-', start);
	int operationIndex3 = str.find('*', start);
	int operationIndex4 = str.find('/', start);
	int operationIndex5 = str.find('^', start);
	int operationIndex6 = str.find('(', start);
	int operationIndex7 = str.find(')', start);
	int operationIndex8 = str.find('=', start);
	for (int i = 0; i < str.length(); i++)
	{
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

int RPN::FindLastOperator(string str)
{
	int operationIndex1 = str.rfind('+');
	int operationIndex2 = str.rfind('-');
	int operationIndex3 = str.rfind('*');
	int operationIndex4 = str.rfind('/');
	int operationIndex5 = str.rfind('^');
	int operationIndex6 = str.rfind('(');
	int operationIndex7 = str.rfind(')');
	int operationIndex8 = str.rfind('=');
	int lastOperatorIndex = max(operationIndex8, max(operationIndex7, max(operationIndex6, max(operationIndex5, max(operationIndex4, (max(operationIndex3, (max(operationIndex1, operationIndex2)))))))));
	return lastOperatorIndex;
}

string RPN::PushOperator(string example, string postfix, int index)
{
	string operationString = example.substr(index, 1);
	if (operations.empty())
		operations.push(operationString);
	else
	{
		if (operationString[0] == '(') 
		{
			operations.push(operationString);
		}
		else if (operationString[0] == ')')
		{

			while (operations.top() != "(") 
			{
				postfix = postfix + operations.top() + ' ';
				operations.pop();
			}
			operations.pop();
		}
		else if (PriorityOfOperation((operations.top())) >= PriorityOfOperation(operationString))
		{
			postfix = postfix + operations.top() + ' ';
			operations.pop();
			operations.push(operationString);
		}
		else
			operations.push(operationString);
	}
	return postfix;
}

string RPN::GetRPNstring(vector<string> info)
{
	string polishNotation = "";
	for (int i = 0; i < info.size(); i++)
	{
		string str = info[i];
		size_t index = 0;
		while ((index = str.find(' ')) != string::npos) str.erase(index, 1);
		int start = 0;
		int operationIndex = FindOperator(str, start);
		while (operationIndex >= 0)
		{
			if (!(str.substr(start, operationIndex - start)).empty())
			{
				polishNotation = polishNotation + str.substr(start, operationIndex - start) + ' ';
			}
			polishNotation = PushOperator(str, polishNotation, operationIndex);
			start = operationIndex + 1;
			operationIndex = FindOperator(str, start);
			if (operationIndex < 0)
			{
				operationIndex = FindLastOperator(str);
				polishNotation = polishNotation + str.substr(operationIndex + 1) + ' ';
				operationIndex = -1;
			}
		}
		while (!operations.empty())
		{
			polishNotation = polishNotation + (operations).top() + ' ';
			(operations).pop();
		}
	}
	cout << polishNotation << " ";
	return polishNotation;
}