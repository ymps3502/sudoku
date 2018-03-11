#include "stdafx.h"
#include "Solver.h"
#include <iostream>

using namespace std;

CSolver::CSolver()
{
}

CSolver::CSolver(char puzzle[81])
{
	for (int i = 0; i < 81; i++){
		CSolver::puzzle[i] = puzzle[i];
	}
}

CSolver::~CSolver()
{
}


bool CSolver::getAnswer()
{
	int row, col, index;
	//get zero grid index
	if (!findEmptyGrid(row, col, index)){
		return true; // backtrack stop here
	}
	// try number from 1 ~ 9
	for (int num = 1; num < 10; num++){
		if (checkCandidateNumber(row, col, num)){
			puzzle[index] = (char)(num + 48);
			if (getAnswer())
				return true;
			puzzle[index] = '0';
		}
	}
	return false;
}

bool CSolver::getAnswer(clock_t startTime, int limitTime)
{
	clock_t finishTime = clock();
	double takeTime = (double)(finishTime - startTime);
	if (takeTime > limitTime * 1000){
		return false;
	}
	int row, col, index;
	//get zero grid index
	if (!findEmptyGrid(row, col, index)){
		return true; // backtrack stop here
	}

	// try number from 1 ~ 9
	for (int num = 1; num < 10; num++){
		if (checkCandidateNumber(row, col, num)){
			puzzle[index] = (char)(num + 48);
			if (getAnswer())
				return true;
			puzzle[index] = '0';
		}
	}
	return false;
}

bool CSolver::getAnswer(char* puzzle, char* res)
{
	for (int i = 0; i < 81; i++)
		this->puzzle[i] = puzzle[i];
	for (int num = 1; num < 10; num++){
		for (int i = 0; i < 81; i++){
			int row = i / 9;
			int col = i % 9;
			if (this->puzzle[i] == '0' && res[i] != (char)(num + 48) && checkCandidateNumber(row, col, num)){
				this->puzzle[i] = (char)(num + 48);
				if (getAnswer()){
					return true;
				}
				this->puzzle[i] = '0';
			}
		}
	}
	return false;
}

bool CSolver::findEmptyGrid(int& row, int& col, int& index)
{
	for (row = 0; row < 9; row++){
		for (col = 0; col < 9; col++){
			index = row * 9 + col;
			if (puzzle[index] == '0')
				return true;
		}
	}
	return false;
}

bool CSolver::checkCandidateNumber(int row, int col, int candiateNumber)
{
	int index;	// = row * 9 + col
	for (int i = 0; i < 9; i++){
		//check row
		index = row * 9 + i;
		if (puzzle[index] == (char)(candiateNumber + 48))
			return false;
		//check col
		index = i * 9 + col;
		if (puzzle[index] == (char)(candiateNumber + 48))
			return false;
		//check box
		index = (row - row % 3 + i / 3) * 9 + (col - col % 3 + i % 3);
		if (puzzle[index] == (char)(candiateNumber + 48))
			return false;
	}
	return true;
}


void CSolver::printAnswer()
{
	for (int i = 0; i < 81; i++){
		cout << puzzle[i] << " ";
		if (i % 9 == 8)
			cout << endl;
	}
	cout << endl;
}