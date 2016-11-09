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
#include <sys/time.h>

using namespace std;

int boardToInt(std::vector< std::vector<int> > &auxBoard);

int size = 3;
int empty = 9;
std::vector< std::vector<int> > initialBoard;
std::vector< std::vector<int> > finalBoard;
std::set <int> createdStates;

class Puzzle
{
public:
	std::vector< std::vector<int> > board;
	int emptyPosition;
	int intBoard;
	Puzzle *parent;
	Puzzle();
	Puzzle(std::vector< std::vector<int> > state, Puzzle *p);
	void printPuzzle();
	void move(int i, int j, int r, int c);
	void moves();
	void swapEmpty (std::vector< std::vector<int> > &auxBoard, int i, int j, int r, int c);
	int printResult(int step);
};

std::list <Puzzle> states;
Puzzle *initialState, *finalState;

Puzzle::Puzzle (std::vector< std::vector<int> > state, Puzzle *p) {
	int i, j, control = 1;
	board.resize(size);
	for(int k = 0 ; k < size ; ++k) {
		board[k].resize(size);
	}
	board = state;
	parent = p;
	intBoard = 0;
	for (i = size -1 ; i >= 0; --i) {
		for (j = size - 1; j >= 0; --j) {
			intBoard += board[i][j] * control;
			control *= 10;
			if (board[i][j] == empty) {
				emptyPosition = i * size + j;
			}
		}
	}
}

void Puzzle::printPuzzle () {
	for(int i = 0 ; i < size ; ++i) {
		printf("|");
		for (int j = 0; j < size; ++j) {
			if (board[i][j] != empty) {
				printf("%3d",board[i][j]);
			} else {
				printf("   ");
			}
		}
		printf(" |\n");
	}
	printf("\n");
}

void Puzzle::swapEmpty (std::vector< std::vector<int> > &auxBoard, int i, int j, int r, int c) {
	int swap;
	swap = auxBoard[i][j];
	auxBoard[i][j] = auxBoard[r][c];
	auxBoard[r][c] = swap;
}

void Puzzle::move(int i, int j, int r, int c) {
	std::vector< std::vector<int> > auxBoard;
	Puzzle *newState;
	int auxIntBoard;

	auxBoard = board;
	swapEmpty(auxBoard, i, j, r, c);
	auxIntBoard = boardToInt(auxBoard);
	if (createdStates.find(auxIntBoard) == createdStates.end()) {
		createdStates.insert(auxIntBoard);
		newState = new Puzzle(auxBoard,this);
		states.push_back(*newState);
		if (auxBoard == finalBoard) {
			finalState = newState;
		}
	}
}

void Puzzle::moves() {
	int i = emptyPosition / size;
	int j = emptyPosition % size;
	// mover para cima
	if (i > 0) {
		move(i,j,i-1,j);
	}
	// mover para baixo
	if (i < size - 1) {
		move(i,j,i+1,j);
	}
	// mover para esquerda
	if (j > 0) {
		move(i,j,i,j-1);
	}
	// mover para direita
	if (j < size - 1) {
		move(i,j,i,j+1);
	}
}

int Puzzle::printResult(int step) {
	if (parent != NULL) {
		step = parent->printResult(step);
	}
	printf("Step %d\n", step);
	step++;
	printPuzzle();
	return step;
}

int boardToInt(std::vector< std::vector<int> > &auxBoard) {
	int intBoard = 0;
	int i, j, control = 10;
	for (i = size - 1; i >= 0; --i)
	{
		for (j = size - 1; j >= 0; --j) {
			intBoard += auxBoard[i][j] * control;
			control *= 10;
		}
	}
	return intBoard;
}

void getInitialAndfinalBoards () {
	scanf("%d", &size);
	scanf("%d", &empty);

	initialBoard.resize(size);
	finalBoard.resize(size);

	for(int i = 0 ; i < size ; ++i) {
		initialBoard[i].resize(size);
		finalBoard[i].resize(size);
	}
	
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			scanf("%d%*c", &initialBoard[i][j]);
		}
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			scanf("%d%*c", &finalBoard[i][j]);
		}
	}
}

int main() {
	struct timeval begin, end;
	double temp;

	gettimeofday(&begin, NULL);

	getInitialAndfinalBoards();
	initialState = new Puzzle(initialBoard, NULL);
	finalState = new Puzzle(finalBoard, NULL);

	if (initialState->intBoard == finalState->intBoard) {
		initialState->printResult(0);
		return 0;
	}

	states.push_back(*initialState);
	createdStates.insert(initialState->intBoard);

	for (std::list<Puzzle>::iterator it=states.begin(); it != states.end() && finalState->parent == NULL; ++it) {
		(*it).moves();
	}
	if (finalState->parent != NULL) {
		finalState->printResult(0);
	} else {
		printf("NO RESULT\n");
	}

	gettimeofday(&end, NULL);
	temp = ((end.tv_sec + ((double) end.tv_usec / 1000000)) -
	        (begin.tv_sec + ((double) begin.tv_usec / 1000000)));

	printf("TIME: %.10lf seconds.\n", temp);
	return 0;
}