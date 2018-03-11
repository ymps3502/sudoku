#pragma once
#include <string>
#include "Solver.h"
#include "Generator.h"

using namespace std;
class CSudokuHelper
{
public:
	CSudokuHelper();
	~CSudokuHelper();
	string getPuzzle(string level);
private:
	CSolver solver;
	CGenerator generator;
	int index;
public:
	string getAnswer();
};

