#include <iostream>
#include "ReadFromFile.h"
#include "DataProcessing.h"
using namespace std;



int main()
{
	ReadFromFile file;
	file.GetName();
	vector<string> info = file.ReadInfo();
	for (size_t i = 0; i < info.size(); i++)
	{
		cout << info[i] << " ";
	}
	cout << endl;
	DataProcessing process;
	process.GetValue(info);
	return 0;
}

//добавить обработку, если строки в файле начинаются с пробела " "
//в конце поменять, чтобы пользователь вводил имя файла(+возможно, добавлять .txt)