#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class ReadFromFile
{
	string fileName;
public:
	ReadFromFile();
	vector<string> ReadInfo();
};