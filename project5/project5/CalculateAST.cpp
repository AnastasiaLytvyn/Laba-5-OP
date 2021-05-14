#include "CalculateAST.h"


float getNodeData(Node* root, map<string, float>&variables, map<string, float>::iterator it)
{
    it = variables.begin();
    if (root->data == "+") {
        return getNodeData(root->son, variables, it) + getNodeData(root->son->brother, variables, it);
    }
    else if (root->data == "-") {
        return getNodeData(root->son, variables, it) - getNodeData(root->son->brother, variables, it);
    }
    else if (root->data == "*") {
        return getNodeData(root->son, variables, it) * getNodeData(root->son->brother, variables, it);
    }
    else if (root->data == "/") {
        return getNodeData(root->son, variables, it) / getNodeData(root->son->brother, variables, it);
    }
    else if (root->data == "=") {
        return getNodeData(root->son->brother, variables, it);
    }
    else {
        if (isdigit(root->data[0])) {
            return stof(root->data);
        }
        else {
            if (variables.count(root->data) == 1) {
                it = variables.find(root->data);
                return it->second;
            }
            else {
                cout << "Wrong variable" << endl;
            }
        }
    }
}

void forEvery(Node* root, int i, vector<string> varVector, map<string, float>&variables, map<string, float>::iterator it)
{
    it = variables.begin();
    if (i != 0)
    {
        for (int j = 0; j < i; j++)
        {
            root = root->brother;
        }
    }
    if (root->data == "=") {
        float value = getNodeData(root->son->brother, variables, it);
        root = root->son;

        while (root->data == "=") {
            varVector.push_back(root->son->brother->data);
            root = root->son;
        }
        varVector.push_back(root->data);
        for (int j = 0; j < varVector.size(); j++) {
            variables[varVector[j]] = value;
        }
    }
    else {
        float value = getNodeData(root, variables, it);
        while (root->data != "=") {
            root = root->son;
        }
        root = root->son;
        while (root->data == "=") {
            varVector.push_back(root->son->brother->data);
            root = root->son;
        }
        varVector.push_back(root->data);
        for (int j = 0; j < varVector.size(); j++) {
            variables[varVector[j]] = value;
            cout << value << endl;
        }
    }
}

float getResult(Node* root, int i, map<string, float>& variables, map<string, float>::iterator it)
{
    for (int j = 0; j < i - 1; j++)
    {
        root = root->brother;
    }
    float value = getNodeData(root, variables, it);
    return value;
}

void calculate(Node* root, vector<string> info)
{
    map<string, float> variables;
    map<string, float>::iterator it = variables.begin();
    int i = 0;
    root = root->son;
    vector<string> varVector;

    while (i < info.size()) {
        if (i != info.size() - 1) 
        {
            forEvery(root, i, varVector, variables, it);
            varVector.clear();
        }
        i++;
    }
    float result = getResult(root, i, variables, it);
    cout << "Result: " << result;
}