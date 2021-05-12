#include <iostream>
#include "ReadFromFile.h"
//#include "RPN.h"
//#include "ShuntingYard.h"
#include "AST.h"
#include <vector>
#include <map>


using namespace std;




int main()
{
	ReadFromFile file;
	file.GetName();
	vector<string> info = file.ReadInfo();
	Node* root=NULL;
	root=getNewNode("Start");
	for (int i = 0; i < info.size(); i++) {
		Insert(root, info[i]);
		cout << i;
	}
	
	//calculate(root,info);
	
	return 0;
}

//добавить обработку, если строки в файле начинаются с пробела " "		///вроде уже добавила
//в конце поменять, чтобы пользователь вводил имя файла(+возможно, добавлять .txt)