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


using namespace std;

class Puzzle
{
public:
    int size;
    std::vector< std::vector<int> > board;
	Puzzle(int n, string state);
    void printPuzzle();
};

Puzzle::Puzzle (int n, string state) {
    size = n;
    board.resize(size);
    for(int i = 0 ; i < size ; ++i)
    {
    	board[i].resize(size);
    }
    int r,c;
    for(int i = 0 ; i < size*size ; ++i ){
        r = i / size;
        c = i % size;
        board[r][c] = state[i] - '0';
        // if(v[i]==9) this->vazio=i;
    }    
}

void Puzzle::printPuzzle () {
    for(int i = 0 ; i < size ; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            printf("%4d",board[i][j]);
        }
        cout << endl;
    }
}

int main() {
	Puzzle a(3,"123456789");
	Puzzle b(4,"1234567890123456");
 //    Puzzle c(5);
 //    Puzzle d(2);
    a.printPuzzle();
    b.printPuzzle();
 //    c.printPuzzle();
 //    d.printPuzzle();
}