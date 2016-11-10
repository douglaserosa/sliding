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

int size = 3;
int empty = 9;
set <vector<vector<int> > > createdStates;

class Puzzle {
public:
	vector<vector<int> > board;
	int emptyPosition;
	Puzzle *parent;
	Puzzle(vector<vector<int> > &state, Puzzle *p);
	void printPuzzle();
	void move(int i, int j, int r, int c);
	void moves();
	void moveEmpty (vector<vector<int> > &newBoard, int i, int j, int r, int c);
	int printResult(int step);
	int getEmptyPosition();
};

list <Puzzle> states;
Puzzle *initialState, *finalState;

Puzzle::Puzzle (vector<vector<int> > &state, Puzzle *p) {
	board = state;
	parent = p;
	emptyPosition = getEmptyPosition();
}

int Puzzle::getEmptyPosition() {
	int position = -1;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (board[i][j] == empty) {
				position = i * size + j;
				return position;
			}
		}
	}
	return position;
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

void Puzzle::moveEmpty (vector<vector<int> > &state, int i, int j, int r, int c) {
	int swap = state[i][j];
	state[i][j] = state[r][c];
	state[r][c] = swap;
}

void Puzzle::move(int i, int j, int r, int c) {
	vector<vector<int> > newBoard;
	Puzzle *newState;

	newBoard = board;
	moveEmpty(newBoard, i, j, r, c);
	if (createdStates.find(newBoard) == createdStates.end()) {
		newState = new Puzzle(newBoard,this);
		states.push_back(*newState);
		createdStates.insert(newState->board);
		if (newState->board == finalState->board) {
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

void getInitialAndfinalStates () {
	scanf("%d", &size);
	scanf("%d", &empty);
	vector<vector<int> > initialBoard(size, vector<int> (size));
	vector<vector<int> > finalBoard(size, vector<int> (size));
	
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
	initialState = new Puzzle(initialBoard, NULL);
	finalState = new Puzzle(finalBoard, NULL);
}

int main() {
	struct timeval begin, end;
	double temp;

	gettimeofday(&begin, NULL);

	getInitialAndfinalStates();

	if (initialState->board == finalState->board) {
		initialState->printResult(0);
		return 0;
	}

	states.push_back(*initialState);
	createdStates.insert(initialState->board);

	for (list<Puzzle>::iterator it = states.begin(); it != states.end() && finalState->parent == NULL; ++it) {
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

	printf("TIME: %.5lf seconds.\n", temp);
	return 0;
}