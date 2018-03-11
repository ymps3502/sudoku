// Sudoku.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "Solver.h"
#include "Generator.h"
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

using namespace std;

mutex gMutex;
int total = 0;
int totalSolved = 0;
int totalFail = 0;

void savePuzzle(int number, string puzzle){
	lock_guard<mutex> mLock(gMutex);
	fstream sudoku_puzzle;
	sudoku_puzzle.open("puzzle.txt", ios::out | ios::app);
	sudoku_puzzle << number << "=" << puzzle << "\n";
	sudoku_puzzle.close();
}

int hasSolved(int startLine, int limit){
	ifstream sudoku_puzzle("puzzle.txt");
	int x, count = 0;
	string str;
	while (getline(sudoku_puzzle, str)){
		x = stoi(str.substr(0, str.find('=')));
		if (x > startLine && x < startLine + limit)
				count++;		
	}
	//lock_guard<mutex> mLock(gMutex);
	//cout << startLine << ":\t" << count << endl;
	return count;
}

vector<int> solved(int startLine, int limit){
	ifstream sudoku_puzzle("puzzle.txt");
	int x;
	vector<int> v;
	string str;
	while (getline(sudoku_puzzle, str)){
		x = stoi(str.substr(0, str.find('=')));
		if (x >= startLine && x < startLine + limit)
			v.push_back(x);
	}
	return v;
}

void printProgress(){
	lock_guard<mutex> mLock(gMutex);
	float progress = float(totalSolved) / float(total);
	cout << "Generate puzzle ..." << "\t[" << totalSolved << "/" << total << "] " << int(progress * 100.0) << " % (" << totalSolved - totalFail << " success, " << totalFail << " fail)\r";
	cout.flush();
}

void hasTotalSolved(int hasSolved){
	lock_guard<mutex> mLock(gMutex);
	totalSolved += hasSolved;
}

void read(int startLine, int limit){
	int lineCount = 0;
	int stopLine = startLine + limit;
	int solve = hasSolved(startLine, limit);
	if (solve == -1)
		solve = 0;
		//startLine += solve;
	char puzzle[82];
	vector<int> SOLVED = solved(startLine, limit);
	CGenerator g;
	ifstream sudoku_exam("solved puzzle.txt");
	string str;
	hasTotalSolved(solve);
	while (getline(sudoku_exam, str) && lineCount < stopLine){
		if (lineCount < startLine || find(SOLVED.begin(), SOLVED.end(), lineCount) != SOLVED.end()){
			lineCount++;
			continue;
		}
		strcpy_s(puzzle, str.c_str());
		printProgress();
		if (g.generatePuzzle(puzzle, 60)){
			str = g.getPuzzle();
			savePuzzle(lineCount,str);
		}
		else{
			totalFail++;
		}
		totalSolved++;
		lineCount++;
	}
}

bool cmp(string a, string b){ return stoi(a.substr(0, a.find('='))) < stoi(b.substr(0, b.find('='))); }

void sorttxt(){
	vector<string> v;
	string str;
	ifstream sudoku_puzzle("puzzle.txt");
	while (getline(sudoku_puzzle, str)){
		v.push_back(str);
	}
	sudoku_puzzle.close();
	ofstream file("puzzle.txt");
	ostream_iterator<string> output(file, "\n");
	sort(v.begin(), v.end(), cmp);
	copy(v.begin(), v.end(), output);
	file.close();
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*const int tNumber = 10;
	int limit = 1000;
	total = tNumber * limit;
	thread mthread[tNumber];

	//while (hasSolved(0, tNumber * limit) < tNumber * limit){
		for (int i = 0; i < tNumber; i++){
			mthread[i] = thread(read, i * limit, limit);
			//mthread[i] = thread(hasSolved, i * limit, limit);
		}
		for (int i = 0; i < tNumber; i++){
			mthread[i].join();
		}
	//}*/
	cout << '\a';
	system("PAUSE");

	/*char* puzzle = "020030070103500000504000000300800095000000040005020006000970000000001239060300080";
	CSolver solver(puzzle);
	solver.getAnswer();
	solver.printAnswer();*/

	//CGenerator generate;
	/*printf("generateing solved puzzle...\n");
	for (clock_t startTime = clock(); !generate.generateSolvedBoard(startTime, 10); startTime = clock()){
	printf("generated fail! trying another...\n");
	}
	generate.printPuzzle();*/

	/*char* puzzle = "536928147489671253712435689127843965865192734394567812271384596953716428648259371";
	clock_t start = clock();
	if (generate.generatePuzzle(puzzle)){
	clock_t finish = clock();
	generate.printPuzzle();
	printf("Take time: %f\n", (double)(finish - start));
	}
	else{
	clock_t finish = clock();
	printf("Fail\n");
	printf("Take time: %f\n", (double)(finish - start));
	}
	string str(generate.getPuzzle());
	cout << str << endl;*/
	return 0;
}

