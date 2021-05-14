#include "AST.h"
using namespace std;

//creating new Node with data without future links
Node* getNewNode(string data)
{
    Node* newNode = new Node();
    newNode->data = data;
    newNode->son = NULL;
    newNode->brother = NULL;
    return newNode;
}

void Insert(Node* Myroot, string str) 
{
    if (Myroot == NULL) 
    {
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



void insertionPlus(Node* root, string str, int start, int end,int toSon) 
{
    int plusIndex = start;
    string afterPlus = str.substr(plusIndex+1, end - plusIndex);
    if (toSon == 1) {
        if (root->son != NULL && root->son->data == "") {
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
        root->son = getNewNode("");
        root = root->son;
        root->brother = getNewNode(afterPlus);
        root = root->son;   
    }
    else 
    {
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

void insertMultBetween(Node* root, string between, int foundedMultInBetween) 
{
    int end3 = between.length() - 1;
    root->brother = getNewNode(between.substr(foundedMultInBetween, 1));
    root = root->brother;
    while (foundedMultInBetween > 0) 
    {
        root->data = between.substr(foundedMultInBetween, 1);
        root->son = getNewNode("");
        root = root->son;
        root->brother = getNewNode(between.substr(foundedMultInBetween + 1, end3 - foundedMultInBetween));
        end3 = foundedMultInBetween - 1;
        foundedMultInBetween = getMultIndex(between, between.length() - end3);
    }
    end3++;
    root->data = between.substr(0, end3);
}



void insertionEqualBrother(Node* root, string str, int toSon) 
{
    int founded = getOperationIndex(str, 0);
    int equalIndex = str.rfind('=');
    if (equalIndex <= 0)
    {
        insertionExample(root, str, toSon);
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
                if (toSon == 1) {
                    root = root->son;
                }
                else {
                root = root->brother;
                }
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
                int foundedMultInBetween = getMultIndex(between, 0);
                if (foundedMultInBetween < 0) {
                    root->brother = getNewNode(between);
                }
                else {
                    insertMultBetween(root, between, foundedMultInBetween);
                }
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
                equalIndex = str.find('=');
                root->data = str.substr(0, equalIndex);
            }
        }
    }
}


void insertionExample(Node* root, string str, int toSon)
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
        int end1 = str.length() - 1;
        int plusIndex1 = getPlusIndexLeft(str, str.length() - 1);
        string between = str.substr(0, plusIndex1);
        while (root->son != NULL)
        {
            root = root->son;
        }
        int multIndex = getMultIndex(between, 0);
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
                root->son = getNewNode(sonForMulti);
                root = root->son;
                root->brother = getNewNode(between);
                multIndex = multIndex2 - 1;
                multIndex2 = getOperationIndex(between.substr(multIndex), 0);
            }
            multIndex = getMultLeft(str, 0);
            root->data = str.substr(0, multIndex);
        }
        else
        {
            root->data = between;
        }
    }
}


int getOperationIndex(string str, int start)
{
    for (int i = str.length() - start - 1; i >= 0; i--)
    {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') return i;
    }
    return -1;
}

int getPlusIndex(string str, int start)
{
    for (int i = str.length() - 1 - start; i >= 0; i--) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '=') return i;
    }
    return -1;

}

int getMultIndex(string str, int start)
{
    for (int i = str.length() - start - 1; i >= 0; i--) {
        if (str[i] == '*' || str[i] == '/' || str[i] == '=') return i;
    }
    return -1;
}

int getPlusIndexLeft(string str, int start)
{
    for (int i = 0; i < start; i++) {
        if (str[i] == '+' || str[i] == '-') return i;
    }
    return -1;
}
int getMultLeft(string str, int start)
{
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '*' || str[i] == '/') return i;
    }
    return -1;
}
int getMultIndexSubstr(string str, int start)
{
    for (int i = start - 1; i >= 0; i--) {
        if (str[i] == '*' || str[i] == '/' || str[i] == '=') return i;
    }
    return -1;
}


int getOperationPrecedence(char oper)
{
    switch (oper) {
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 1;
    }
}