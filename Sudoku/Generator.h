#pragma once
#include <ctime>
class CGenerator
{
public:
	CGenerator();
	~CGenerator();
	bool generatePuzzle(char* solvedPuzzle, int limitTime);
	bool generateSolvedPuzzle(clock_t startTime, int limitTime);
	char* getPuzzle();
	char* getSolvedPuzzle();
	void printPuzzle();
	void printSolvedPuzzle();
private:
	void shuffle(int* numberList, int size);
	char puzzle[81];
	char solvedPuzzle[81];
	int getRandomIndex();
	void generateEmptyPuzzle();
	bool isSolved();
};

