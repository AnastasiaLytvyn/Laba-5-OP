#pragma once
#include <iostream>
#include <string>
#include <stack>
using namespace std;


struct Node
{
    char data;
    Node* left;
    Node* right;
};


class AST
{
    Node* root;
public:
    AST()
    {
        root = NULL;
    }
    Node* GetNode(char symbol, Node* leftsym, Node* rightsym)
    {

        if (root == NULL)
            root = new Node();
        root->data = symbol;
        root->left = leftsym;
        root->right = rightsym;
        return root;
    }
    stack<Node*> addNode(stack<Node*> stack, char symbol)
    {
        root->left = stack.top();
        stack.pop();
        root->right = stack.top();
        stack.pop();
        stack.push(GetNode(symbol, root->left, root->right));
        return stack;
    }
};
