#include "AST.h"
using namespace std;

Node* Insert(Node* root, string data) {
    if (root == NULL) { //empty tree
        root = getNewNode(data);
    }
    else if (data < root->data) {
        root->son = Insert(root->son, data);
    }
    else {
        root->brother = Insert(root->brother, data);
    }
    return root;
}

Node* getNewNode(string data) {//creating new Node with data without future links
    Node* newNode = new Node();
    newNode->data = data;
    newNode->son = NULL;
    newNode->brother = NULL;
    return newNode;
}

Node* InsertNewLine(Node* root, string str) {
    if (root == NULL) {
        return;
    }
    else {
        if (str.find('=') >= 0) {
            if (root->son == NULL) {
                root = root->son;
                root = getNewNode("=");
                root->son = getNewNode(str.substr(0, str.find('=')));
                root->son->brother = getNewNode(str.substr(str.find('=')+1));
                /*
                            start
                          /      \
                        =        NULL
                      /   \
                    a      5
                */
            }
            else {
                root = root->son;
                while (root->brother != NULL) {
                    root = root->brother;
                }
                root->brother = getNewNode("=");
                root = root->brother;
                root->son = getNewNode(str.substr(0, str.find('=')));
                root->son->brother = getNewNode(str.substr(str.find('=') + 1));

            }
        }
        else {
            root = root->son;
            while (root->brother != NULL) {
                root = root->brother;
            }
            int operationIndex = getOperationIndex(str, 0);
            root->brother = getNewNode(str.substr(operationIndex,1));
            root = root->brother;
            root->son = getNewNode(str.substr(0, operationIndex));
            root->son->brother = getNewNode(str.substr(operationIndex + 1));
        }
    }
}

int getOperationIndex(string str, int start) {
    for (int i = start; i < str.length(); i++) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') return i;
    }
}

