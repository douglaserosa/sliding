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

int size = 3;
int empty = 9;
std::vector< std::vector<int> > initialBoard;
std::vector< std::vector<int> > finalBoard;
std::set <std::vector< std::vector<int> > > createdStates;

class Puzzle
{
public:
	std::vector< std::vector<int> > board;
	int emptyPosition;
	Puzzle *parent;
	Puzzle();
	Puzzle(std::vector< std::vector<int> > state, Puzzle *p);
	void printPuzzle();
	void moves();
	void printResult();
};

std::list <Puzzle> states;
Puzzle *initial, *final;

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
		printf("  |\n");
	}
	printf("\n");
}

void swapEmpty (std::vector< std::vector<int> > &auxBoard, int i, int j, int r, int c) {
	int aux;
	aux = auxBoard[i][j];
	auxBoard[i][j] = auxBoard[r][c];
	auxBoard[r][c] = aux;
}

void imprime (std::vector< std::vector<int> > board) {
	for(int i = 0 ; i < size ; ++i) {
		printf("|");
		for (int j = 0; j < size; ++j) {
			if (board[i][j] != empty) {
				printf("%3d",board[i][j]);
			} else {
				printf("   ");
			}
		}
		printf("  |\n");
	}
	printf("\n");
}


void Puzzle::moves() {
	int i = emptyPosition / 3;
	int j = emptyPosition % 3;
	std::vector< std::vector<int> > auxBoard;
	Puzzle *newState;
	// mover para cima
	if (i > 0) {
		auxBoard = board;
		swapEmpty(auxBoard,i,j,i-1,j);
		if (createdStates.find(auxBoard) == createdStates.end()) {
			createdStates.insert(auxBoard);
			newState = new Puzzle(auxBoard,this);
			states.push_back(*newState);
			if (auxBoard == finalBoard) {
				final = newState;
			}
		}
	}
	// mover para direita
	if (j < size - 1) {
		auxBoard = board;
		swapEmpty(auxBoard,i,j,i,j+1);
		if (createdStates.find(auxBoard) == createdStates.end()) {
			createdStates.insert(auxBoard);
			newState = new Puzzle(auxBoard,this);
			states.push_back(*newState);
			if (auxBoard == finalBoard) {
				final = newState;
			}
		}
	}
	// mover para baixo
	if (i < size - 1) {
		auxBoard = board;
		swapEmpty(auxBoard,i,j,i+1,j);
		if (createdStates.find(auxBoard) == createdStates.end()) {
			createdStates.insert(auxBoard);
			newState = new Puzzle(auxBoard,this);
			states.push_back(*newState);
			if (auxBoard == finalBoard) {
				final = newState;
			}
		}
	}
	// mover para esquerda
	if (j > 0) {
		auxBoard = board;
		swapEmpty(auxBoard,i,j,i,j-1);
		if (createdStates.find(auxBoard) == createdStates.end()) {
			createdStates.insert(auxBoard);
			newState = new Puzzle(auxBoard,this);
			states.push_back(*newState);
			if (auxBoard == finalBoard) {
				final = newState;
			}
		}
	}
}

void Puzzle::printResult() {
	if (parent != NULL) {
		parent->printResult();
	}
	printPuzzle();
}

void getInitialAndfinalBoards () {
	size = 3;
	empty = 9;
	string stringInitial = "567498321";
	string stringFinal = "123894765";
	// ler size, empty, initial e final ;

	initialBoard.resize(size);
	finalBoard.resize(size);
	for(int i = 0 ; i < size ; ++i) {
		initialBoard[i].resize(size);
		finalBoard[i].resize(size);
	}
	initialBoard[0][0] = 5;
	initialBoard[0][1] = 6;
	initialBoard[0][2] = 7;
	initialBoard[1][0] = 4;
	initialBoard[1][1] = 9;
	initialBoard[1][2] = 8;
	initialBoard[2][0] = 3;
	initialBoard[2][1] = 2;
	initialBoard[2][2] = 1;
	finalBoard[0][0] = 1;
	finalBoard[0][1] = 2;
	finalBoard[0][2] = 3;
	finalBoard[1][0] = 8;
	finalBoard[1][1] = 9;
	finalBoard[1][2] = 4;
	finalBoard[2][0] = 7;
	finalBoard[2][1] = 6;
	finalBoard[2][2] = 5;
}

int main() {
	getInitialAndfinalBoards();
	initial = new Puzzle(initialBoard, NULL);
	final = new Puzzle(finalBoard, NULL);
	if (initial->board == finalBoard) {
		final->parent = initial;
	}
	states.push_back(*initial);
	createdStates.insert(initial->board);
	for (std::list<Puzzle>::iterator it=states.begin(); it != states.end() && final->parent == NULL; ++it) {
		(*it).moves();
	}

	if (final->parent != NULL) {
		final->printResult();
	}


	// printf("AGORA O SET\n");

	// createdStates.insert(initial.board);
	// createdStates.insert(initialBoard);
	// createdStates.insert(finalBoard);
	// createdStates.insert(initial.board);
	// createdStates.insert(finalBoard);
	// for (std::set <std::vector< std::vector<int> > >::iterator it=createdStates.begin(); it != createdStates.end(); ++it) {
	// 	imprime(*it);
	// }

}