#include <iostream>
#include "ReadFromFile.h"
//#include "RPN.h"
//#include "ShuntingYard.h"
#include "AST.h"


using namespace std;




int main()
{
	ReadFromFile file;
	file.GetName();
	vector<string> info = file.ReadInfo();
	//for (size_t i = 0; i < info.size(); i++)
	//{
		//cout << info[i] << " ";
	//}
	//cout << endl;
	//RPN str;
	//string RPN = str.GetRPNstring(info);
	/*ShuntingYard tree;
	Node* done;*/
	//done=tree.DataProcessing(info);

	/*
	a=b=4
	a=b+4
	*/
	Node* root=NULL;
	root=getNewNode("Start");
	Insert(root, "a=5");
	Insert(root, "b=4");
	Insert(root, "a+b");


	displayTree(root);

	/*cout << root->son->brother->data<<endl;
	cout << root->son->brother->son->data << endl;
	cout << root->son->brother->son->brother->data << endl;

	*/
	return 0;
}

//добавить обработку, если строки в файле начинаются с пробела " "		///вроде уже добавила
//в конце поменять, чтобы пользователь вводил имя файла(+возможно, добавлять .txt)