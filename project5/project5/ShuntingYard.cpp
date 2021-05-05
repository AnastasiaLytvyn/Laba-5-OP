#include "ShuntingYard.h"

map<string, int> ShuntingYard::OperatorsMap()
{
	map<string, int> operators;
	operators["+"] = 1;
	operators["-"] = 1;
	operators["*"] = 2;
	operators["/"] = 2;
	operators["^"] = 3;
	operators["="] = 4;
	return operators;
}

void ShuntingYard::DataProcessing(vector<string> info)
{
    map<string, int> operatorsNpriority = OperatorsMap();
    stack<char> operators;
    string operation, popped;
    for (int i = 0; i < info.size(); i++)
    {
        operation = info[i];
        switch (operation[0])
        {
        case '(':
            operators.push(operation[0]);
            break;
        case')':
            while (!operators.empty())
            {
                popped = operators.top();
                operators.pop();
                if ('(' == popped[0])
                    continue;
                else
                {
                    ////////add new node
                }

            }
            break;/////
        default:
            if (operatorsNpriority.count(operation))
            {
                map<string, int>::iterator firstit = operatorsNpriority.begin();
                map<string, int>::iterator secondit = operatorsNpriority.begin();

                char first = operation[0];
                char second;
                while (!operators.empty() && (second = operators.top()))
                {
                    string secondoperator = "";
                    secondoperator += second;
                    firstit = operatorsNpriority.find(operation);
                    secondit = operatorsNpriority.find(secondoperator);
                    if (firstit->second <= secondit->second)
                    {
                        operators.pop();
                        ////// added new node
                    }
                    else break;
                }
                operators.push(first);
            }
            else
            {
                ///// added new node
            }
            break;
        }
    }
}
