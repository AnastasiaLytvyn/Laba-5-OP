#include "ReadFromFile.h"

ReadFromFile::ReadFromFile()
{
	fileName = "file.txt";
	//cout << "Enter name of file: ";
	//cin >> fileName;
}

vector<string> ReadFromFile::ReadInfo()
{
	vector<string> strings;
	string str;
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "Error! Cann't open this file" << endl;
	}
	else
	{
		while (!file.eof())
		{
			getline(file, str);
			strings.push_back(str);
		}
	}
	return strings;
}