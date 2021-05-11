#include "AST.h"
using namespace std;
 map<string, float> variables;
 map<string, float>::iterator it = variables.begin();

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
                insertionEqualBrother(root, str, 1);
            }
            else {
                root = root->son;
                while (root->brother != NULL) {
                    root = root->brother;
                }
                insertionEqualBrother(root, str, 0);
            }
        }
        else {
            root = root->son;
            while (root->brother != NULL) {
                root = root->brother;
            }
            insertionEqualBrother(root, str, 0);
        }
    }

}

int getOperationIndex(string str, int start) {
    for (int i = start; i < str.length(); i++) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') return i;
    }
    return -1;
}

int getOperationIndex(string str, int start, int end) {
    for (int i = start; i < end; i++) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') return i;
    }
    return -1;
}

int getPlusIndex(string str, int start, int end) {
    for (int i = start; i < end; i++) {
        if (str[i] == '+' || str[i] == '-') return i;
    }
    return -1;
}

int getPlusIndex(string str, int start) {
    for (int i = start; i < str.length(); i++) {
        if (str[i] == '+' || str[i] == '-') return i;
    }
    return -1;
    
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

void insertionPlus(Node* root, string str, int start, int end) {
    int plusIndex = end;
    string beforePlus = str.substr(start, plusIndex - start);
    root->brother = getNewNode(str.substr(plusIndex, 1));
    root = root->brother;
    int multIndex = getOperationIndex(beforePlus, 0);
    if (multIndex < 0) {
        root->son = getNewNode(beforePlus);
        root = root->son;
    }
    else {
        int iterationCouner = 0;
        int start2 = 0;
        while (multIndex > 0) {
            if (iterationCouner == 0) {
                root->son = getNewNode(str.substr(start+multIndex, 1));
                root = root->son;
            }
            else {
                root->brother = getNewNode(str.substr(start+multIndex, 1));
                root = root->brother;
            }
            root->son = getNewNode(beforePlus.substr(start2, multIndex - start2));
            root = root->son;
            start2 = multIndex + 1;
            multIndex = getOperationIndex(beforePlus, start2);
            iterationCouner++;
            
        }
        multIndex = getOperationIndex(beforePlus, start2 - 1);
        root->brother = getNewNode(beforePlus.substr(multIndex + 1));
    }
}

void insertionEqualBrother(Node* root, string str, int toSon) {
    int foundEqual = str.find('=');
    int start = 0;
    if (foundEqual > 0) {
        if (toSon == 0) {
            root->brother = getNewNode("=");
            root = root->brother;
        }
        else if (toSon == 1) {
            root->son = getNewNode("=");
            root = root->son;
        }
    root->son = getNewNode(str.substr(start,foundEqual - start));
    root = root->son;
    start = foundEqual + 1;
    foundEqual = str.find('=', start);
    while (foundEqual > 0) {
        root->brother = getNewNode("=");
        root = root->brother;
        root->son = getNewNode(str.substr(start, foundEqual - start));
        root = root->son;
        start = foundEqual + 1;
        foundEqual = str.find('=', start);
        }
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
        start = -1;
        while (operationPrecedence != 2) {
            start = getOperationIndex(str, start+1);
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
            root->brother = getNewNode(str.substr(multIndex + 1));
            return;
        }
        else {
            start = 0;
            int plusIndex = getPlusIndex(str, start);
            start = str.rfind('=')+1;
            while (plusIndex > 0) {
                insertionPlus(root, str, start, plusIndex);
                root = root->brother->son;
                start = plusIndex + 1;
                plusIndex = getPlusIndex(str, start);
            }
            start = start - 1;
            plusIndex = getPlusIndex(str, start);
            int operationAfter = getOperationIndex(str, plusIndex + 1);
            if (operationAfter < 0) {
                root->brother = getNewNode(str.substr(plusIndex + 1));
                root = root->brother;
            }
            else {
                while (operationAfter > 0) {
                    root->brother = getNewNode(str.substr(operationAfter, 1));
                    root = root->brother;
                    root->son = getNewNode(str.substr(plusIndex + 1, operationAfter - plusIndex - 1));
                    root = root->son;
                    plusIndex = operationAfter + 1;
                    operationAfter = getOperationIndex(str, plusIndex + 1);
                }
                operationAfter = getOperationIndex(str, plusIndex - 1);
                root->brother = getNewNode(str.substr(operationAfter + 1));
            }
        }
    }
}

float getNodeData(Node* root) {
    if (root->data == "+") {
        return getNodeData(root->son) + getNodeData(root->son->brother);
    }
    else if (root->data == "-") {
        return getNodeData(root->son) - getNodeData(root->son->brother);
    }
    else if (root->data == "*") {
        return getNodeData(root->son) * getNodeData(root->son->brother);
    }
    else if (root->data == "/") {
        return getNodeData(root->son) / getNodeData(root->son->brother);
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
                cout << "Wrong variable"<<endl;
            }
        }
    }
}

void whil312312e (Node* root, int i, vector<string> varVector) {
    if (i != 0) {
        for (int j = 0; j < i; j++) {
            root = root->brother;
        }
    }
    if (root->data == "=") {
        root = root->son;
        varVector.push_back(root->data);
        while (root->brother->data == "=") {
            varVector.push_back(root->brother->son->data);
            root = root->brother->son;
        }
        float value = getNodeData(root->brother);
        for (int j = 0; j < varVector.size(); j++) {
            variables[varVector[j]] = value;
            cout << value << endl;
        }
    }
}

float getResult(Node* root, int i) {
    for (int j = 0; j < i; j++) {
        root = root->brother;
    }
    float value = getNodeData(root);
    return value;
}

void calculate(Node* root, vector<string> info) {
    int i = 0;
    
    root = root->son;
    vector<string> varVector;
    
    while (i < info.size()-1) {
        whil312312e(root,i, varVector);
        varVector.clear();
        i++;
    }
    float result = getResult(root,i);
    cout << "Result: " << result;
}