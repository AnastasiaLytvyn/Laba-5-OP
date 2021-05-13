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
    for (int i = str.length()-start-1; i >= 0; i--) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') return i;
    }
    return -1;
}

int getPlusIndex(string str, int start) {
    for (int i = str.length()-1-start; i >=0; i--) {
        if (str[i] == '+' || str[i] == '-' || str[i]=='=') return i;
    }
    return -1;
    
}


int getMultIndex(string str, int start) {
    for (int i = str.length() - start - 1; i >= 0; i--) {
        if (str[i] == '*' || str[i] == '/' || str[i] == '=') return i;
    }
    return -1;
}

int getPlusIndexLeft(string str, int start) {
    for (int i = 0; i < start; i++) {
        if (str[i] == '+' || str[i] == '-') return i;
    }
    return -1;
}
int getMultLeft(string str, int start) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '*' || str[i] == '/') return i;
    }
    return -1;
}

int getMultIndexSubstr(string str, int start) {
    for (int i = start - 1; i >= 0; i--) {
        if (str[i] == '*' || str[i] == '/' || str[i] == '=') return i;
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

void insertionPlus(Node* root, string str, int start, int end,int toSon) {
    int plusIndex = start;
    string afterPlus = str.substr(plusIndex+1, end - plusIndex);
    if (toSon == 1) {
        if (root->son->data == "") {
            root->son->data = str.substr(plusIndex, 1);
            root = root->son;
        }
        else {
            root->son = getNewNode(str.substr(plusIndex, 1));
            root = root->son;
        }
    }
    else {
        root->brother = getNewNode(str.substr(plusIndex, 1));
        root = root->brother;
    }
    int multIndex = getOperationIndex(afterPlus, 0);
    if (multIndex < 0) {
        root->son = getNewNode("");////// mb trouble in 1
        root = root->son;
        root->brother = getNewNode(afterPlus);
        root = root->son;   //////zach
    }
    else {
        int start2 = afterPlus.length()-1;
        root->son = getNewNode("");
        root = root->son;
        int countmultind = 0;
        while (multIndex > 0) {
            ++countmultind;
            if (countmultind == 1)
            {
                root->brother = getNewNode(afterPlus.substr(multIndex,1));
                root = root->brother;
            }
            else
            {
                root->data= afterPlus.substr(multIndex, 1);
            }
            root->son = getNewNode("");
            root = root->son;
            root->brother = getNewNode(afterPlus.substr(multIndex+1, start2-multIndex));
            start2 = multIndex - 1;
            multIndex = getMultIndexSubstr(afterPlus, start2);
        }
        if (start2 != 0)
        {
            multIndex = getOperationIndex(afterPlus, start2 - 1);
        }
        else
        {
            multIndex = getMultLeft(afterPlus, start2+1);
        }
        root->data = afterPlus.substr(0,multIndex);
    }
}



void insertionEqualBrother(Node* root, string str, int toSon) {
    int founded = getOperationIndex(str, 0);
    int equalIndex = str.rfind('=');
    if (equalIndex <= 0) {
        if (isdigit(str[0])) 
        {
            int plusIndex = getPlusIndex(str, 0);
            if (plusIndex <= 0) {
                int multIndex = getMultIndex(str, 0);
                int end = str.length();
                if (toSon == 1) {
                    root->son = getNewNode(str.substr(multIndex, 1));
                    root = root->son;

                }
                else {
                    root->brother = getNewNode(str.substr(multIndex, 1));
                    root = root->brother;
                }
                while (multIndex > 0) {
                    root->data = str.substr(multIndex, 1);
                    root->son = getNewNode("");
                    root = root->son;
                    root->brother = getNewNode(str.substr(multIndex + 1, end - multIndex - 1));
                    end = multIndex;
                    multIndex = getMultIndex(str, str.length() - end);
                }
               
                root->data = str.substr(0, end);
            }
            else {
                int end = str.length() - 1;
                insertionPlus(root, str, plusIndex, end, toSon);
                root = root->brother;
                while (plusIndex > 0) {
                    end = plusIndex - 1;
                    plusIndex = getPlusIndex(str, str.length() - end);
                    if (plusIndex > 0) {
                        insertionPlus(root, str, plusIndex, end, 1);
                        root = root->son;
                    }
                }
                ////////////////
                ///// equalIndex==0;
                int end1 = str.length() - 1;
                int equalIndex = 0;
                int plusIndex1 = getPlusIndexLeft(str, str.length() - 1);
                string between = str.substr(equalIndex, plusIndex1 - equalIndex);
                while (root->son != NULL)
                {
                    root = root->son;
                }
                int multIndex = getMultIndex(between, equalIndex);
                if (multIndex > 0)
                {
                    root->data = str.substr(multIndex, 1);
                    root->son = getNewNode("");
                    root = root->son;
                    root->brother = getNewNode(between.substr(multIndex + 1));
                    int multIndex2 = getOperationIndex(between.substr(0, multIndex), 0);
                    string sonForMulti;
                    while (multIndex2 > 0)
                    {
                        int founded = getMultIndex(between.substr(0, multIndex2), 0);
                        if (founded > 0)
                        {
                            sonForMulti = between.substr(founded);
                        }
                        else
                        {
                            sonForMulti = between.substr(0, multIndex2);
                        }
                        between = str.substr(multIndex2 + 1, multIndex - multIndex2 - 1);
                        root->data = str.substr(multIndex2, 1);
                        root->son = getNewNode(sonForMulti);//
                        root = root->son;
                        root->brother = getNewNode(between);
                        multIndex = multIndex2 - 1;
                        multIndex2 = getOperationIndex(between.substr(multIndex), 0);
                    }
                    root->data = between.substr(0, multIndex);
                }
                else
                {
                    root->data = between;
                }
                //after while
               //multIndex = getMultIndex(between, equalIndex);
               // root->data = str.substr(0, multIndex);
            }
        }
        else {
            if (variables.count(str) == 1) {
                it = variables.find(str);
                cout << "Result: " << it->second;
            }
            else {
                cout << "Error";
            }
        }
    }
    else {
        if (founded <= 0) {
            int end = str.length() - 1;
            if (toSon == 1) {
            root->son = getNewNode("=");
            root = root->son;
            }
            else if (toSon == 0) {
                root->brother = getNewNode("=");
                root = root->brother;

            }
            root->son = getNewNode("");
            root = root->son;
            root->brother = getNewNode(str.substr(equalIndex + 1, end - equalIndex));
            end = equalIndex;
            equalIndex = str.rfind('=', equalIndex - 1);
            while (equalIndex > 0){
                root->data = "=";
                root->son = getNewNode("");
                root = root->son;
                root->brother = getNewNode(str.substr(equalIndex + 1, end - equalIndex-1));
                end = equalIndex;

                equalIndex = str.rfind('=',equalIndex-1);
            }
            root->data = str.substr(0, str.find('='));
        }
        else
        {                                                  ////
            int plusIndex = getPlusIndex(str, 0);
            if (plusIndex <= 0) {
                int multIndex = getMultIndex(str, 0);
                int end = str.length();
                if (toSon == 1) {
                root->son = getNewNode(str.substr(multIndex, 1));
                root = root->son;
                
                }
                else {
                    root->brother = getNewNode(str.substr(multIndex, 1));
                    root = root->brother;
                }
                while (multIndex > 0 && str[multIndex] != '=') {
                    root->data = str.substr(multIndex, 1);
                    root->son = getNewNode("");
                    root = root->son;
                    root->brother = getNewNode(str.substr(multIndex+1,end-multIndex-1));
                    end = multIndex;
                    multIndex = getMultIndex(str, str.length() - end);
                }
                while (multIndex > 0 && str[multIndex] == '=') {
                    root->data = "=";
                    root->son = getNewNode("");
                    root = root->son;
                    root->brother = getNewNode(str.substr(multIndex+1, end - multIndex-1));
                    end = multIndex;
                    multIndex = getMultIndex(str, str.length() - end);
                }
                root->data = str.substr(0, str.find('='));
            }
            else {
                int plusIndex = getPlusIndex(str, 0);
                int end = str.length() - 1;
                insertionPlus(root, str, plusIndex, end, toSon);
                root = root->brother;
                while (plusIndex > 0 && str[plusIndex] != '=') {
                    end = plusIndex - 1;
                    plusIndex = getPlusIndex(str, str.length()-end);
                    if (plusIndex > 0 && str[plusIndex]!='=') {
                    insertionPlus(root, str, plusIndex, end, 1);
                    root = root->son;
                    }
                }
                int end1 = str.length()-1;
                int equalIndex = str.rfind('=', end1);
                int plusIndex1 = getPlusIndexLeft(str, str.length()-1);
                string between = str.substr(equalIndex + 1, plusIndex1 - equalIndex - 1);
                while (root->son != NULL) {
                    root = root->son;
                }
                root->data = str.substr(equalIndex, 1);
                root->son = getNewNode("");
                root = root->son;
                root->brother = getNewNode(between);
                equalIndex--;
                int equalIndex2 = str.rfind('=', equalIndex);
                while (equalIndex2 > 0) {
                    between = str.substr(equalIndex2 + 1, equalIndex - equalIndex2);
                    root->data = str.substr(equalIndex2, 1);
                    root->son = getNewNode("=");
                    root = root->son;
                    root->brother = getNewNode(between);
                    equalIndex = equalIndex2 - 1;
                    equalIndex2 = str.rfind('=', equalIndex);
                }
                //after while
                equalIndex = str.find('=');
                root->data = str.substr(0, equalIndex);
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
        while (root->brother->data == "=") {//change
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