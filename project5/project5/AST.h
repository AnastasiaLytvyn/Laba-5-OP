#pragma once
#include <iostream>
#include <string>
#include <stack>
using namespace std;


struct Node
{
    string data;
    Node* son;
    Node* brother;
};

Node* getNewNode(string);
void Insert(Node*, string);
int getOperationIndex(string, int);
void displayTree(Node*);