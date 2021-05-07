//#include "ShuntingYard.h"
//
//map<char, int> ShuntingYard::OperatorsMap()
//{
//	map<char, int> operators;
//	operators['+'] = 1;
//	operators['-'] = 1;
//	operators['*'] = 2;
//	operators['/'] = 2;
//	operators['^'] = 3;
//	operators['='] = 4;
//	return operators;
//}
//
//
//Node* ShuntingYard::DataProcessing(vector<string> info)
//{
//    map<char, int> operatorsNpriority = OperatorsMap();
//    stack<char> operators;
//    stack<Node*> operand;
//    string operation, popped;
//    AST tree;
//    for (int i = 0; i < info.size(); i++)
//    {
//        operation = info[i];
//        for (int j = 0; j < info[i].length(); j++)
//        {
//            switch (operation[j])
//            {
//            case '(':
//                operators.push(operation[0]);
//                break;
//            case')':
//                while (!operators.empty())
//                {
//                    popped = operators.top();
//                    operators.pop();
//                    if ('(' == popped[0])
//                        continue;
//                    else
//                    {
//                        ////////add new node
//                        operand = tree.addNode(operand, popped[0]);
//                        cout << " ";
//
//                    }
//                }
//                //break;/////
//            default:
//                if (operatorsNpriority.count(operation[j]))
//                {
//                    map<char, int>::iterator firstit = operatorsNpriority.begin();
//                    map<char, int>::iterator secondit = operatorsNpriority.begin();
//
//                    char first = operation[j];
//                    char second;
//                    while (!operators.empty() && (second = operators.top()))
//                    {
//                        string secondoperator = "";
//                        secondoperator += second;
//                        firstit = operatorsNpriority.find(operation[j]);
//                        secondit = operatorsNpriority.find(secondoperator[0]);
//                        if (firstit->second <= secondit->second)
//                        {
//                            operators.pop();
//                            ////// added new node
//                            operand = tree.addNode(operand, secondit->first);
//                            cout << " ";
//
//                        }
//                        else break;
//                    }
//                    operators.push(first);
//                }
//                else
//                {
//                    ///// added new node
//                    operand.push(tree.GetNode(operation[j], 0, 0));
//                    cout << " ";
//                }
//                break;
//            }
//
//        }
//       
//    }
//    while (!operators.empty())
//    {
//        operand = tree.addNode(operand, operators.top());
//        operators.pop();
//    }
//    cout << operand.size() << endl;
//    return operand.top();
//}
//
