#include "AST.h"
using namespace std;

Node* getNewNode(string data) {//creating new Node with data without future links
    Node* newNode = new Node();
    newNode->data = data;
    newNode->son = NULL;
    newNode->brother = NULL;
    return newNode;
}

void Insert(Node* Myroot, string str) {
    if (Myroot == NULL) {
        return;
    }
    else {
        Node* root = Myroot;
        int founded = str.find('=');
        if (founded >= 0) {
            if (root->son == NULL) {
                Node* newNode = getNewNode("=");
                root->son = newNode;
                root = root->son;
                root->son = getNewNode(str.substr(0, str.find('=')));
                root->son->brother = getNewNode(str.substr(str.find('=')+1));
                //tree
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
                Node* newNode = getNewNode("=");
                root->brother = newNode;
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

int getOperationIndex(string str, int start, int end) {
    for (int i = start; i < end; i++) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') return i;
    }
}

int getPlusIndex(string str, int start, int end) {
    for (int i = start; i < end; i++) {
        if (str[i] == '+' || str[i] == '-') return i;
    }
}

int getPlusIndex(string str, int start) {
    for (int i = start; i < str.length(); i++) {
        if (str[i] == '+' || str[i] == '-') return i;
    }
}

int getOperationPrecedence(char oper) {
    switch (oper) {
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 1;
    }
}

void insertionEqualBrother(Node* root, string str) {
    int foundEqual = str.find('=');
    int start = 0;
    while (foundEqual > 0) {
        root->brother = getNewNode("=");
        root = root->brother;
        root->son = getNewNode(str.substr(str.find('=', foundEqual-start)));
        root = root->son;
        start = foundEqual + 1;
        foundEqual= str.find('=', start);
    }
    int operationIndex = getOperationIndex(str, 0);
    if (operationIndex < 0) {
        foundEqual = str.rfind('=');
        root->brother = getNewNode(str.substr(foundEqual + 1));
        return;
    }
    else {
        start = 0;
        int operationPrecedence = getOperationPrecedence(str[getOperationIndex(str, start)]);
        while (operationPrecedence != 2) {
            start = getOperationIndex(str, start);
            if (start > 0) {
            operationPrecedence = getOperationPrecedence(str[getOperationIndex(str, start)]);
            }
            else {
                break;
           }
        }
        if (operationPrecedence == 1) {
            start = 0;
            int multIndex = getOperationIndex(str, start);
            while (multIndex > 0) {
                root->brother = getNewNode(str.substr(multIndex, 1));
                root = root->brother;
                root->son = getNewNode(str.substr(start, multIndex - start));
                root = root->son;
                start = multIndex + 1;
                multIndex = getOperationIndex(str, start);
            }
            multIndex = getOperationIndex(str, start - 1);
            root->brother = getNewNode(str.substr(multIndex+1));
            return;
        }
        else {
            start = 0; // for + or -
            int start2 = 0; // for * or /
            int plusIndex = getPlusIndex(str, start);
            while (plusIndex > 0) {
                string beforePlus = str.substr(start, plusIndex - start);
                root->brother = getNewNode(str.substr(plusIndex, 1));
                root = root->brother;
                int multIndex = getOperationIndex(beforePlus, start);
                if (multIndex < 0) {
                    root->son = getNewNode(beforePlus);
                    root = root->son;
                }
                else {
                    while (multIndex > 0) {
                        root->son = getNewNode(str.substr(multIndex,1));
                        root = root->son;
                        root->son = getNewNode(beforePlus.substr(start2, multIndex - start2));
                        root = root->son;
                        start2 = multIndex + 1;
                        multIndex = getOperationIndex(beforePlus, start2);
                    }
                    multIndex = getOperationIndex(beforePlus, start2 - 1);
                    root->brother = getNewNode(beforePlus.substr(multIndex + 1));
                }
                start = plusIndex + 1;
                plusIndex = getPlusIndex(str, start);
            }
            plusIndex = getPlusIndex(str, start - 1);
        }
    }
}





//
//void displayTree(Node* root) {
//    if (root == NULL) {
//        cout << "Empty";
//    }
//    else {
//        Node* myRoot = root;
//        cout << "                                            " << root->data<< endl;
//        cout << "                    " << root->son->data;
//        root = root->son;
//        while (root->brother != NULL) {
//            cout << "                    " << root->brother->data;
//            root = root->brother;
//        }
//        cout << endl;
//
//
//        root = myRoot->son;
//        while (root->son != NULL) {
//            cout << "                    " << root->son->data;
//            root = root->son;
//            while (root->brother != NULL) {
//                cout << "                    " << root->brother->data;
//                root = root->brother;
//            }
//            cout << endl;
//
//        }
//        
//    }
//}