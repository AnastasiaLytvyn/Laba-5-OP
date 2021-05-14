#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct Node
{
    string data;
    Node* son;
    Node* brother;
};
Node* getNewNode(string);
void Insert(Node*, string);
void insertionPlus(Node*, string, int, int, int);
void insertMultBetween(Node*, string, int);
void insertionEqualBrother(Node*, string, int);
void insertionExample(Node*, string, int);

int getOperationIndex(string, int);
int getPlusIndex(string, int);
int getMultIndex(string, int);
int getPlusIndexLeft(string, int);
int getMultLeft(string, int);
int getMultIndexSubstr(string, int);
int getOperationPrecedence(char);
