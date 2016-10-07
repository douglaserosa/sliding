/* 
 * File:   8puzzle-profundidade.cpp
 * Author: douglas
 *
 * Created on May 3, 2009, 12:26 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <set>

#define finalState 123804765

using namespace std;

void intToMatrix(int state, int matrix[3][3]) {
    int i, j;

    for (i = 2; i > -1; i--) {
        for (j = 2; j > -1; j--) {
            matrix[i][j] = state % 10;
            state = state / 10;
        }
    }
}

int matrixToInt(int matrix[3][3]) {
    int i, j;
    int state = 0;
    int control = 1;

    for (i = 2; i > -1; i--) {
        for (j = 2; j > -1; j--) {
            state = state + (matrix[i][j] * control);
            control = control * 10;
        }
    }
    return state;
}

void printMatrix(int matrix[3][3]) {
    int i, j;

    printf("\n");
    for (i = 0; i < 3; i++) {
        printf("| ");
        for (j = 0; j < 3; j++) {
            if (matrix[i][j] == 0) {
                printf("  ");
            } else {
                printf("%d ", matrix[i][j]);
            }
        }
        printf("|\n");
    }
}

int getInicialState() {
    int state;
    printf("\nDigitar estado inicial:\n\n");
    printf("Exemplo: Digitando 123804765 eh equivalente ao ESTADO META ==> | 1 2 3 |\n");
    printf("                                                               | 8   4 |\n");
    printf("                                                               | 7 6 5 |\n");
    printf("\nDigite o Estado Inicial do 8-Puzzle: ");
    scanf("%d", &state);
    printf("\nEstado capturado: %09d\n", state);
    return state;
}

int columnOfZero(int matrix[3][3]) {
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (matrix[i][j] == 0)
                return j;
        }
    }
}

int lineOfZero(int matrix[3][3]) {
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (matrix[i][j] == 0)
                return i;
        }
    }
}

void moveUp(int matrix[3][3]) {
    int i, j;

    i = lineOfZero(matrix);
    j = columnOfZero(matrix);

    matrix[i][j] = matrix[i - 1][j];
    matrix[i - 1][j] = 0;
}

void moveDown(int matrix[3][3]) {
    int i, j;

    i = lineOfZero(matrix);
    j = columnOfZero(matrix);

    matrix[i][j] = matrix[i + 1][j];
    matrix[i + 1][j] = 0;
}

void moveRight(int matrix[3][3]) {
    int i, j;

    i = lineOfZero(matrix);
    j = columnOfZero(matrix);

    matrix[i][j] = matrix[i][j + 1];
    matrix[i][j + 1] = 0;
}

void moveLeft(int matrix[3][3]) {
    int i, j;

    i = lineOfZero(matrix);
    j = columnOfZero(matrix);

    matrix[i][j] = matrix[i][j - 1];
    matrix[i][j - 1] = 0;
}

void sliding8Puzzle() {
    int matrix[3][3];
    int estados[362880];
    int passos[362880];
    int pai[362880];
    int state;
    int aux, flag;
    int final = 0;
    int atual = 0;
    int i, j;
    set <int> visitedStates;

    estados[final] = getInicialState();
    visitedStates.insert(estados[final]);
    passos[final] = 0;
    pai[final] = -1;

    for (; atual > -1; atual = final) {

        state = estados[atual];

        flag = 0;

        if (state == finalState) {
            printf("\nO computador achou o resultado!\n");
            printf("Foram testados %d estados!\n", visitedStates.size());
            printf("Sao necessarios %d movimentos para chegar ao estado final!\n", passos[atual]);

            aux = passos[atual];

            for (i = atual, j = passos[atual]; i != -1; i = pai[i], j--) {
                passos[j] = estados[i];
            }

            printf("\n***** Solucao *****\n");

            printf("Estado Inicial ==> %09d", passos[0]);
            intToMatrix(passos[0], matrix);
            printMatrix(matrix);

            for (i = 1; i <= aux; i++) {
                printf("\nPasso %d ==> %09d", i, passos[i]);
                intToMatrix(passos[i], matrix);
                printMatrix(matrix);
                getchar();
            }
            return;
        }

        intToMatrix(state, matrix);

        i = lineOfZero(matrix);
        j = columnOfZero(matrix);


        if (i > 0) {
            aux = state;
            moveUp(matrix);
            state = matrixToInt(matrix);
            if (visitedStates.find(state) == visitedStates.end()) {
                final++;
                estados[final] = state;
                visitedStates.insert(state);
                passos[final] = passos[atual] + 1;
                pai[final] = atual;
                flag = 1;
            }
            moveDown(matrix);
            state = aux;
        }
        if (i < 2) {
            aux = state;
            moveDown(matrix);
            state = matrixToInt(matrix);
            if (visitedStates.find(state) == visitedStates.end()) {
                final++;
                estados[final] = state;
                visitedStates.insert(state);
                passos[final] = passos[atual] + 1;
                pai[final] = atual;
                flag = 1;
            }
            moveUp(matrix);
            state = aux;

        }
        if (j > 0) {
            aux = state;
            moveLeft(matrix);
            state = matrixToInt(matrix);
            if (visitedStates.find(state) == visitedStates.end()) {
                final++;
                estados[final] = state;
                visitedStates.insert(state);
                passos[final] = passos[atual] + 1;
                pai[final] = atual;
                flag = 1;
            }
            moveRight(matrix);
            state = aux;
        }
        if (j < 2) {
            aux = state;
            moveRight(matrix);
            state = matrixToInt(matrix);
            if (visitedStates.find(state) == visitedStates.end()) {
                final++;
                estados[final] = state;
                visitedStates.insert(state);
                passos[final] = passos[atual] + 1;
                pai[final] = atual;
                flag = 1;
            }
            moveLeft(matrix);
            state = aux;
        }

        if (flag == 0) {
            final--;
        }
    }

    printf("\nForam testados %d estados!\n", visitedStates.size());
    printf("O computador nao encontrou solucao para o problema!");
    printf("\nVerifique se o estado inicial eh valido!\n");
    return;

    /* set <int>::iterator it;

    for (it = visitedStates.begin(); it != visitedStates.end(); it++)
        cout << *it << endl;
     */
}

int main() {

    sliding8Puzzle();

    return (EXIT_SUCCESS);
}
