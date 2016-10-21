/* 
 * File:   slidingPuzzle.cpp
 * Author: douglas
 *
 * Created on Oct 7, 2016, 3:20 AM
 */

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <climits>
#include <cmath>
#include <time.h>

using namespace std;

int size = 3;
int empty = 9;
double T = 0;
std::vector< std::vector<int> > initialBoard;
std::vector< std::vector<int> > finalBoard;
std::set <std::vector< std::vector<int> > > createdStates;

class Puzzle
{
public:
	std::vector< std::vector<int> > board;
	int emptyPosition;
	int energy;
	Puzzle *parent;
	Puzzle();
	Puzzle(std::vector< std::vector<int> > state, Puzzle *p);
	void printPuzzle();
	void move(int i, int j, int r, int c);
	void moves();
	void swapEmpty (std::vector< std::vector<int> > &auxBoard, int i, int j, int r, int c);
	int printResult(int step);
	int calcEnergy ();
	int calcEnergy2 ();
	int numberPosition(int n);
};

std::vector<Puzzle> queue;
Puzzle *initialState, *finalState;

Puzzle::Puzzle (std::vector< std::vector<int> > state, Puzzle *p) {
	int i, j;
	board.resize(size);
	for(int k = 0 ; k < size ; ++k) {
		board[k].resize(size);
	}
	board = state;
	parent = p;
	for (int k = 0; k < size * size; ++k) {
		i = k / size;
		j = k % size;
		if (board[i][j] == empty) {
			emptyPosition = i * size + j;
		}
	}
	// energy = calcEnergy();
	energy = calcEnergy2();
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
	std::vector< std::vector<int> > auxBoard = board;
	Puzzle *newState;

	swapEmpty(auxBoard, i, j, r, c);
	if (createdStates.find(auxBoard) == createdStates.end()) {
		createdStates.insert(auxBoard);
		newState = new Puzzle(auxBoard,this);
		queue.push_back(*newState);
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

int Puzzle::calcEnergy () {
	int e = 0;
	int i, j, k, r, c;
	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j) {
			if (finalBoard[i][j] != board[i][j]) {
				k = numberPosition(finalBoard[i][j]);
				if (k != -1) {
					r = k / size;
					c = k % size;
					e += (i > r ? i - r : r - i ) + (j > c ? j - c : c -j);
				}
			}
		}
	}
	return e;
}

int Puzzle::calcEnergy2 () {
	int e = 0;
	int i, j, k, r, c;
	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j) {
			if (board[i][j] != finalBoard[i][j]) {
				e += 1;
			}
		}
	}
	return e;
}

int Puzzle::numberPosition(int n) {
	int i, j;
	for (int k = 0; k < size * size; ++k) {
		i = k / size;
		j = k % size;
		if (board[i][j] == n) {
			return k;
		}
	}
	return -1;
}

unsigned long long int fat (int n) {
	unsigned long long int f = 1;
	for (n = n; n > 1; --n) {
		f *= n;
	}
	return f;
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
	// T = fat(size * size) / 2;
	// T = (double) (size - 1) * 2 * size * size;
	T = (double) size * size;
}

int main()
{
	Puzzle *current, *candidate;
	int delta, index, next, max, min;
	unsigned long long int maxStates;
	double random, probability, reduction;

	srand(time(NULL));
	getInitialAndfinalBoards();

	maxStates = fat(size*size) / 2;
	reduction = (double) T / maxStates;

	initialState = new Puzzle(initialBoard, NULL);
	finalState = new Puzzle(finalBoard, NULL);

	if (initialState->board == finalState->board) {
		initialState->printResult(0);
		return 0;
	}

	queue.reserve(maxStates);
	queue.push_back(*initialState);
	createdStates.insert(initialState->board);

	for (index = 0, T = T; index < queue.size() && T > 0 && finalState->parent == NULL; T-=reduction, index++) {
		current = &queue[index];
		current->moves();
		if (index + 1 < queue.size()) {
			max = queue.size() - 1;
			min = index + 1;
			next = min + rand() % (max - min + 1);
	  		candidate = &queue[next];
	        delta = current->energy - candidate->energy;
	        if (delta > 0) {
	        	queue.insert(queue.begin() + index + 1, queue[next]);
				queue.erase(queue.begin() + next + 1);
        	} else {
        		probability = pow(M_E, (double) delta / (double) T);
        		random = (double) (rand() % 100) / 100;
	        	// probability = pow(M_E, (double) delta / (double) current->energy);
	        	if (random > probability) {
	        		queue.insert(queue.begin() + index + 1, queue[next]);
					queue.erase(queue.begin() + next + 1);
	        	}
        	}
		}
	}
	if (finalState->parent != NULL) {
		printf("ACHOU\n");
		finalState->printResult(0);
	} else {
		printf("NO RESULT\n");
	}
	return 0;
}