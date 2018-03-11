#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include "Generator.h"
#include "Solver.h"

using namespace std;

CGenerator::CGenerator()
{
	generateEmptyPuzzle();
}


CGenerator::~CGenerator()
{
}

bool CGenerator::generatePuzzle(char* solvedPuzzle, int limitTime)
{
	clock_t startTime = clock();
	int index[81];
	int clue = 81;
	char temp;
	srand((unsigned)time(NULL));
	//generate i~80 random list
	for (int i = 0; i < 81; i++){
		index[i] = i;
		this->puzzle[i] = solvedPuzzle[i];
	}
	shuffle(index, 81);

	//remove grid and test puzzle whether has answer
	for (int i = 0; i < 81; i++){
		clock_t finishTime = clock();
		double takeTime = (double)(finishTime - startTime);
		if (takeTime > limitTime * 1000){
			return false;
		}
		if (clue <= 17)
			break;
		temp = this->puzzle[index[i]];
		this->puzzle[index[i]] = '0';
		CSolver solver;
		if (!solver.getAnswer(this->puzzle, solvedPuzzle)){
			clue--;
			continue;
		}
		else
			this->puzzle[index[i]] = temp;
	}
	//the puzzle has too many clues
	if (clue > 51)
		return false;
	else
		return true;
}

bool CGenerator::generateSolvedPuzzle(clock_t startTime, int limitTime)
{
	clock_t finishTime = clock();
	double takeTime = (double)(finishTime - startTime);
	if (takeTime > limitTime * 1000){
		return false;
	}
	srand((unsigned)time(NULL));
	int index = getRandomIndex();
	if (index == -1){
		//puzzle has 81 clue
		return true;
	}
	CSolver solver(solvedPuzzle);
	int candidate[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int count = 0;
	int row = index / 9;
	int col = index % 9;
	for (int num = 1; num < 10; num++)
	{
		if (solver.checkCandidateNumber(row, col, num))
		{
			candidate[num - 1] = num;
			count++;
		}
	}
	//if cadidate numer are all zero -> continue
	if (count == 0)
		return false;
	shuffle(candidate, 9);

	for (int i = 0; i < 9; i++){
		if (candidate[i] == 0)
			continue;
		solvedPuzzle[index] = (char)(candidate[i] + 48);
		CSolver solver(solvedPuzzle);
		bool hasAnswer = solver.getAnswer(startTime, limitTime);
		if (hasAnswer && !isSolved()){
			if (generateSolvedPuzzle(startTime, limitTime))
				return true;
		}
		else if (hasAnswer)
			return true;
	}
	return false;
}


int CGenerator::getRandomIndex()
{
	int numberList[81];
	for (int i = 0; i < 81; i++){
		if (solvedPuzzle[i] == '0')
			numberList[i] = i; //save zero grid index
		else
			numberList[i] = -1;
	}
	shuffle(numberList, 81);
	for (int i = 0; i < 81; i++){
		if (numberList[i] != -1)
			return numberList[i];
	}
	return -1;
}

void CGenerator::shuffle(int* numberList, int size)
{
	int i, temp, num1, num2;
	int* pnum = (int*)malloc(sizeof(int) * size);
	//init pnum[size]
	for (i = 0; i < size; i++)
	{
		pnum[i] = numberList[i];
	}

	for (i = 0; i < size; i++)
	{
		num1 = (int)(rand() / (RAND_MAX + 1.0) * size);
		num2 = (int)(rand() / (RAND_MAX + 1.0) * size);

		temp = pnum[num1];
		pnum[num1] = pnum[num2];
		pnum[num2] = temp;
	}

	for (i = 0; i < size; i++)
	{
		numberList[i] = pnum[i];
	}
	free(pnum);
}


void CGenerator::generateEmptyPuzzle()
{
	for (int i = 0; i < 81; i++){
		solvedPuzzle[i] = '0';
	}
}

bool CGenerator::isSolved()
{
	for (int i = 0; i < 81; i++){
		if (puzzle[i] == '0')
			return false;
	}
	return true;
}

char* CGenerator::getPuzzle()
{
	*(puzzle + 81) = '\0';
	return puzzle;
}

char* CGenerator::getSolvedPuzzle()
{
	*(solvedPuzzle + 81) = '\0';
	return solvedPuzzle;
}


void CGenerator::printPuzzle()
{
	for (int i = 0; i < 81; i++){
		cout << puzzle[i] << " ";
		if (i % 9 == 8)
			cout << endl;
	}
	cout << endl;
}

void CGenerator::printSolvedPuzzle()
{
	for (int i = 0; i < 81; i++){
		cout << solvedPuzzle[i] << " ";
		if (i % 9 == 8)
			cout << endl;
	}
	cout << endl;
}