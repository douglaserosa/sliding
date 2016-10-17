/* 
 * File:   slidingPuzzle.cpp
 * Author: douglas
 *
 * Created on Oct 7, 2016, 3:20 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
#include <list>

using namespace std;

#define up 0
#define right 1
#define down 2
#define left 3

int size = 3;
int hole = 9;

class Puzzle
{
public:
	std::vector< std::vector<int> > board;
	Puzzle *parent;
	Puzzle();
	Puzzle(std::vector< std::vector<int> > state, Puzzle *p);
	void printPuzzle();
	void move(int direction);
};

Puzzle::Puzzle (std::vector< std::vector<int> > state, Puzzle *p) {
	board.resize(size);
	for(int i = 0 ; i < size ; ++i) {
		board[i].resize(size);
	}
	board = state;
	parent = p;
}

void Puzzle::printPuzzle () {
	for(int i = 0 ; i < size ; ++i) {
		printf("|");
		for (int j = 0; j < size; ++j) {
			if (board[i][j] != hole) {
				printf("%3d",board[i][j]);
			} else {
				printf("   ");
			}
		}
		printf("  |\n");
	}
	printf("\n");
}

std::vector< std::vector<int> > initialState;
std::vector< std::vector<int> > finalState;
std::set <std::vector< std::vector<int> > > createdStates;
std::list <Puzzle> states;

void imprime (std::vector< std::vector<int> > board) {
	for(int i = 0 ; i < size ; ++i) {
		printf("|");
		for (int j = 0; j < size; ++j) {
			if (board[i][j] != hole) {
				printf("%3d",board[i][j]);
			} else {
				printf("   ");
			}
		}
		printf("  |\n");
	}
	printf("\n");
}

void getInitialAndFinalStates () {
	size = 3;
	hole = 9;
	string initial = "567498321";
	string final = "123894765";
	// ler size, hole, initial e final ;

	initialState.resize(size);
	finalState.resize(size);
	for(int i = 0 ; i < size ; ++i) {
		initialState[i].resize(size);
		finalState[i].resize(size);
	}
	initialState[0][0] = 5;
	initialState[0][1] = 6;
	initialState[0][2] = 7;
	initialState[1][0] = 4;
	initialState[1][1] = 9;
	initialState[1][2] = 8;
	initialState[2][0] = 3;
	initialState[2][1] = 2;
	initialState[2][2] = 1;
	finalState[0][0] = 1;
	finalState[0][1] = 2;
	finalState[0][2] = 3;
	finalState[1][0] = 8;
	finalState[1][1] = 9;
	finalState[1][2] = 4;
	finalState[2][0] = 7;
	finalState[2][1] = 6;
	finalState[2][2] = 5;
}

int main() {
	getInitialAndFinalStates();
	Puzzle initial(initialState, NULL);
	states.push_back(initial);
	states.push_back(initial);
	states.push_back(initial);
	for (std::list<Puzzle>::iterator it=states.begin(); it != states.end(); ++it) {
		(*it).printPuzzle();
	}

	printf("AGORA O SET\n");

	createdStates.insert(initial.board);
	createdStates.insert(initialState);
	createdStates.insert(finalState);
	createdStates.insert(initial.board);
	createdStates.insert(finalState);
	for (std::set <std::vector< std::vector<int> > >::iterator it=createdStates.begin(); it != createdStates.end(); ++it) {
		imprime(*it);
	}

}