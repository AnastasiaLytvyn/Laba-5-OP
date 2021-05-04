#include "DataProcessing.h"

void DataProcessing::GetValue(vector<string> info)
{
	map<string, int> values;
	string variable;
	int value;
	int position;
	for (int i = 0; i < info.size(); i++)
	{
		position = info[i].find('=');
		if (position != string::npos)
		{
			variable = info[i].substr(0, position);
			value = stoi(info[i].substr(position + 1));
			//cout <<variable << "==" << value << endl;
			values[variable] = value;
		}
		else
		{
			//анализ примера...
		}
	}
	//вывод содержимого map
	for (auto itMap = values.begin(); itMap != values.end(); itMap++)
		cout << itMap->first << " == " << itMap->second << endl;
}