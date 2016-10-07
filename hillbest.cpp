/* 
 * File:   hillClimbing.cpp
 * Author: douglas
 *
 * Created on May 26, 2009, 10:21 PM
 */

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <math.h>

const int finalState = 123804765;

using namespace std;

struct nodo {
    int state; // O estado é representado por um numero inteiro de 9 digitos
    int hx; // armazena o numero de pecas no lugar
};

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

int contaPecas(int state) {
    int hx = 0;
    int m[3][3];
    int i, j;
    int aux = finalState;

    intToMatrix(state, m);

    for (i = 2; i > -1; i--) {
        for (j = 2; j > -1; j--) {
            if (m[i][j] == aux % 10)
                hx++;
            aux = aux / 10;
        }
    }
    return hx;
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

int getInitialState() {
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

int iOnde(int state, int x) {
    int m[3][3];
    int i, j;

    intToMatrix(state, m);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (m[i][j] == x)
                return i;
        }
    }
}

int jOnde(int state, int x) {
    int m[3][3];
    int i, j;

    intToMatrix(state, m);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (m[i][j] == x)
                return j;
        }
    }
}

int calculaDistancia(int state) {
    int i, j;
    int dist = 0;

    printf("dist %d\n", dist);

    i = iOnde(state, 0);
    j = jOnde(state, 0);
    dist = dist + abs(i - 1) + abs(j - 1);
    printf("dist 0 %d\n", dist);

    i = iOnde(state, 1);
    j = jOnde(state, 1);
    dist = dist + abs(i - 0) + abs(j - 0);
    printf("dist 1 %d\n", dist);

    i = iOnde(state, 2);
    j = jOnde(state, 2);
    dist = dist + abs(i - 0) + abs(j - 1);
    printf("dist 2 %d\n", dist);

    i = iOnde(state, 3);
    j = jOnde(state, 3);
    dist = dist + abs(i - 0) + abs(j - 2);
    printf("dist 3 %d\n", dist);

    i = iOnde(state, 4);
    j = jOnde(state, 4);
    dist = dist + abs(i - 1) + abs(j - 2);
    printf("dist 4 %d\n", dist);

    i = iOnde(state, 5);
    j = jOnde(state, 5);
    dist = dist + abs(i - 2) + abs(j - 2);
    printf("dist 5 %d\n", dist);

    i = iOnde(state, 6);
    j = jOnde(state, 6);
    dist = dist + abs(i - 2) + abs(j - 1);
    printf("dist 6 %d\n", dist);

    i = iOnde(state, 7);
    j = jOnde(state, 7);
    dist = dist + abs(i - 2) + abs(j - 0);
    printf("dist 7 %d\n", dist);

    i = iOnde(state, 8);
    j = jOnde(state, 8);
    dist = dist + abs(i - 1) + abs(j - 0);

    printf("dist 8 %d\n", dist);
    return dist;
}

void sliding8Puzzle() {
    int matrix[3][3];
    struct nodo *estados = (nodo *) malloc(181440 * sizeof (nodo));
    struct nodo vizinho;
    int state;
    int final = 0;
    int cont = 1;
    int i, j;

    vizinho.state = getInitialState();
    vizinho.hx = calculaDistancia(vizinho.state);

    for (;; final++) {
        estados[final] = vizinho;

        if (estados[final].state == finalState) {
            printf("\nO computador achou o resultado!\n");
            printf("Foram testados %d estados!\n", cont);
            printf("Sao necessarios %d movimentos para chegar ao estado final!\n", final);

            printf("\n***** Solucao *****\n");

            printf("Estado Inicial ==> %09d", estados[0].state);
            intToMatrix(estados[0].state, matrix);
            printMatrix(matrix);

            for (i = 1; i <= final; i++) {
                printf("\nPasso %d ==> %09d", i, estados[i].state);
                intToMatrix(estados[i].state, matrix);
                printMatrix(matrix);
                getchar();
            }
            return;
        }

        vizinho.state = 1000000;
        vizinho.hx = 1000000;

        intToMatrix(estados[final].state, matrix);

        i = lineOfZero(matrix);
        j = columnOfZero(matrix);

        if (i > 0) {
            moveUp(matrix);
            state = matrixToInt(matrix);
            if (calculaDistancia(state) < estados[final].hx) {
                vizinho.state = state;
                vizinho.hx = calculaDistancia(state);
            }
            moveDown(matrix);
            cont++;
        }
        if (i < 2) {
            moveDown(matrix);
            state = matrixToInt(matrix);
            if (calculaDistancia(state) < estados[final].hx) {
                vizinho.state = state;
                vizinho.hx = calculaDistancia(state);
            }
            moveUp(matrix);
            cont++;
        }
        if (j > 0) {
            moveLeft(matrix);
            state = matrixToInt(matrix);
            if (calculaDistancia(state) < estados[final].hx) {
                vizinho.state = state;
                vizinho.hx = calculaDistancia(state);
            }
            moveRight(matrix);
            cont++;
        }
        if (j < 2) {
            moveRight(matrix);
            state = matrixToInt(matrix);
            if (calculaDistancia(state) < estados[final].hx) {
                vizinho.state = state;
                vizinho.hx = calculaDistancia(state);
            }
            moveLeft(matrix);
            cont++;
        }

        if (vizinho.hx > estados[final].hx) {
            printf("\nForam testados %d estados!\n", cont);
            printf("O computador nao encontrou uma solucao ideal para o problema!\n");
            printf("Sao necessarios %d movimentos para chegar a solucao parcial!\n", final);
            printf("Verifique se o estado inicial eh valido!\n");

            printf("\n***** Solucao Parcial *****\n");

            printf("Estado Inicial ==> %09d", estados[0].state);
            intToMatrix(estados[0].state, matrix);
            printMatrix(matrix);

            for (i = 1; i <= final; i++) {
                printf("\nPasso %d ==> %09d", i, estados[i].state);
                intToMatrix(estados[i].state, matrix);
                printMatrix(matrix);
                getchar();
            }
            return;
        }
    }
}

int main() {

    sliding8Puzzle();

    return (EXIT_SUCCESS);
}
