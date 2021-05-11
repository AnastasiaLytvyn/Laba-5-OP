#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
using namespace std;


struct Node
{
    string data;
    Node* son;
    Node* brother;
};

Node* getNewNode(string);
void Insert(Node*, string);
float getResult(Node* root);
int getOperationIndex(string, int);
int getOperationIndex(string str, int start, int end);
int getOperationPrecedence(char oper);
int getPlusIndex(string str, int start);
int getPlusIndex(string str, int start, int end);
void calculate(Node* root, vector<string>);
void insertionEqualBrother(Node* root, string str, int toSon = 0);
void insertionPlus(Node* root, string str, int start, int end);