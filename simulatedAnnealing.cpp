/* 
 * File:   simulatedAnnealing.cpp
 * Authors: Cícero Camargo, Douglas Rosa e Lucas Fonseca
 *
 * Created on May 27, 2009, 02:15 AM
 */

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <set>
#include <queue>
#include <time.h> // por causa do srand
#include <math.h> // por causa da exponenciação

const int finalState = 123804765;
const double e = 2.718281; // numero de euler

using namespace std;

struct nodo {
    int state; // O estado é representado por um numero inteiro de 9 digitos
    int pai; // Guarda a posicao do pai
    int posicao; // Guarda sua posicao na fila convencional, não é a fila de prioridade
    int gx; // guarda profundidade do nodo na arvore, equivalente ao numero de passos, é usado para calcular fx
    int hx; // resultado da funcao heuristica, armazena o numero de pecas fora do lugar
    int fx; // fx = gx + hx;
}; //estados[181440], pq[181440];

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

int countHeuristic(int state) {
    int hx = 0;
    int m[3][3];
    int i, j;
    int aux = finalState;

    intToMatrix(state, m);

    for (i = 2; i > -1; i--) {
        for (j = 2; j > -1; j--) {
            if (m[i][j] != aux % 10)
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

int compare(const void *a, const void *b) {
    struct nodo *a2, *b2;
    a2 = (struct nodo*) a;
    b2 = (struct nodo*) b;
    return (a2->fx - b2->fx);
}

void sliding8Puzzle() {
    int matrix[3][3];
    struct nodo *estados = (nodo *) malloc(181440 * sizeof (nodo));
    struct nodo *pq = (nodo *) malloc(181440 * sizeof (nodo));
    int state;
    int aux;
    int final = 0;
    int atual = 0;
    int i, j;
    set <int> visitedStates;

    int range, index; //para o nodo randomico a ser escolhido
    struct nodo temp;
    double probabilidade, delta, sorte; //para implementar a probabilidade de pegar outro nodo

    estados[0].state = getInicialState();
    estados[0].pai = -1;
    estados[0].posicao = 0;
    estados[0].gx = 0;
    estados[0].hx = countHeuristic(estados[0].state);
    estados[0].fx = estados[0].gx + estados[0].hx;
    visitedStates.insert(estados[0].state);
    pq[0] = estados[0];

    for (; atual <= final; atual++) {

        state = pq[atual].state; // receber da PQ;

        if (state == finalState) {
            printf("\nO computador achou o resultado!\n");
            printf("Foram testados %d estados!\n", visitedStates.size());
            printf("Sao necessarios %d movimentos para chegar ao estado final!\n", pq[atual].gx);

            aux = pq[atual].gx;

            for (i = pq[atual].posicao, j = pq[atual].gx; i != -1; i = estados[i].pai, j--) {
                pq[j] = estados[i];
            }

            printf("\n***** Solucao *****\n");

            printf("Estado Inicial ==> %09d", pq[0].state);
            intToMatrix(pq[0].state, matrix);
            printMatrix(matrix);

            for (i = 1; i <= aux; i++) {
                printf("\nPasso %d ==> %09d", i, pq[i].state);
                intToMatrix(pq[i].state, matrix);
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
                estados[final].state = state;
                estados[final].pai = pq[atual].posicao;
                estados[final].posicao = final;
                estados[final].gx = pq[atual].gx + 1;
                estados[final].hx = countHeuristic(state);
                estados[final].fx = estados[final].gx + estados[final].hx;
                pq[final] = estados[final];
                visitedStates.insert(state);
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
                estados[final].state = state;
                estados[final].pai = pq[atual].posicao;
                estados[final].posicao = final;
                estados[final].gx = pq[atual].gx + 1;
                estados[final].hx = countHeuristic(state);
                estados[final].fx = estados[final].gx + estados[final].hx;
                pq[final] = estados[final];
                visitedStates.insert(state);
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
                estados[final].state = state;
                estados[final].pai = pq[atual].posicao;
                estados[final].posicao = final;
                estados[final].gx = pq[atual].gx + 1;
                estados[final].hx = countHeuristic(state);
                estados[final].fx = estados[final].gx + estados[final].hx;
                pq[final] = estados[final];
                visitedStates.insert(state);
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
                estados[final].state = state;
                estados[final].pai = pq[atual].posicao;
                estados[final].posicao = final;
                estados[final].gx = pq[atual].gx + 1;
                estados[final].hx = countHeuristic(state);
                estados[final].fx = estados[final].gx + estados[final].hx;
                pq[final] = estados[final];
                visitedStates.insert(state);
            }
            moveLeft(matrix);
            state = aux;
        }
        //AQUI QUE FICA O PULO DO GATO!!
        while (true) { //fica neste laço até conseguir um próximo nodo
            srand(time(NULL));
            range = final - atual; // dá o tamanho do intervalo de onde um candidato a ser próximo nodo
            index = rand() % range + atual + 1; // o "mais um" é por que o número gerado está no intervalo fechado de 0+atual até (range-1)+atual

            delta = (double) (pq[atual].hx - pq[index].hx); // usa-se somente a função heurística para o calculo do delta...
            if (delta > 0) { // o candidato está mais próximo da solução
                temp = pq[atual + 1];
                pq[atual + 1] = pq[index]; //este trecho posiciona o candidato como o próximo a ser pego
                pq[index] = temp;
                break; // para encerrar o laço while
            } else {
                sorte = (double) (rand() % 100 + 1) / 100;
                probabilidade = pow(e, delta / (double) pq[index].hx);
                if (sorte < probabilidade) {
                    temp = pq[atual + 1];
                    pq[atual + 1] = pq[index]; //este trecho posiciona o candidato como o próximo a ser pego
                    pq[index] = temp;
                    break; // para encerrar o laço while
                }
            }

        }//end while

    }

    printf("\nForam testados %d estados!\n", visitedStates.size());
    printf("O computador nao encontrou solucao para o problema!");
    printf("\nVerifique se o estado inicial eh valido!\n");

    return;

}

int main() {
    sliding8Puzzle();

    return (EXIT_SUCCESS);
}
