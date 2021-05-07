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

Node* getNewNode(string data);
Node* InsertNewLine(Node* root, string str);