#include <iostream>
#include "ReadFromFile.h"
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
	return 0;
}

