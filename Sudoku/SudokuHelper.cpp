#include "stdafx.h"
#include "SudokuHelper.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

CSudokuHelper::CSudokuHelper()
{
	index = -1;
}


CSudokuHelper::~CSudokuHelper()
{
}


string CSudokuHelper::getPuzzle(string level)
{
	srand(time(NULL));
	string str;
	do{
		ifstream sudoku_puzzle("puzzle.txt");
		int line = (rand() % 9999);
		int count = 0;
		while (getline(sudoku_puzzle, str)){
			if (count < line){
				count++;
				continue;
			}
			stringstream ss;
			ss.str(str);
			string item;
			vector<string> elems;
			while (getline(ss, item, ',')) {
				elems.push_back(item);
			}
			if (elems.at(2).compare(level)){
				index = count;
				sudoku_puzzle.close();
				return elems.at(0);
			}
			count++;
		}
		sudoku_puzzle.close();
	} while (true);
}


string CSudokuHelper::getAnswer()
{
	string str = "";
	int count = 0;
	if (index = -1){
		return str;
	}
	ifstream sudoku_exam("solved puzzle.txt");
	while (getline(sudoku_exam, str)){
		if (count == index)
			return str;
		else
			count++;
	}
}
