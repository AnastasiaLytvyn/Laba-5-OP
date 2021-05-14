#pragma once
#include "AST.h"
#include <map>

void calculate(Node*, vector<string>);
void forEvery(Node*, int, vector<string>, map<string, float>&, map<string, float>::iterator);
float getNodeData(Node*, map<string, float>&, map<string, float>::iterator);
float getResult(Node*, int, map<string, float>&, map<string, float>::iterator);