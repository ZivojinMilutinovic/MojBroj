#include <iostream>
#include <fstream>
#include <string>
#include "Runda.h"
#include <vector>
using namespace std;
#pragma once
class FileReader
{
	string naziv_fajla;
public:
	FileReader(string naziv_fajla);
	void readFromFile(vector<Runda> &niz_rundi);
};

