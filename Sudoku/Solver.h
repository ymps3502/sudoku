#pragma once
#include <ctime>
class CSolver
{
public:
	CSolver();
	CSolver(char puzzle[81]);
	~CSolver();
	bool getAnswer();
	bool getAnswer(clock_t startTime, int limitTime);
	bool CSolver::getAnswer(char* puzzle, char* res);
	void printAnswer();
	bool checkCandidateNumber(int row, int col, int candiateNumber);
private:
	char puzzle[81];
	bool findEmptyGrid(int& row, int& col, int& index);
};

