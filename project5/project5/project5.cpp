#include <iostream>
#include "ReadFromFile.h"
#include "AST.h"
#include <vector>
#include "CalculateAST.h"

using namespace std;

int main()
{
	ReadFromFile file;
	vector<string> info = file.ReadInfo();
	Node* root=NULL;
	root=getNewNode("Start");
	for (int i = 0; i < info.size(); i++) 
	{
		Insert(root, info[i]);
	}
	calculate(root, info);
	return 0;
}
