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
int getOperationIndex(string str, int start, int end);
int getOperationPrecedence(char oper);
int getPlusIndex(string str, int start);
int getPlusIndex(string str, int start, int end);

void insertionEqualBrother(Node* root, string str, int toSon = 0);
void insertionPlus(Node* root, string str, int start, int end);