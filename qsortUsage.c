#include <stdio.h>
#include <stdlib.h>

struct test{
       int x;
       };

int compare(struct test *a, struct test *b){
    /*if (a->x > b->x) return 1;
    else if (a->x == b->x) return 0;
    else return -1;*/
    return (a->x - b->x);
}

void imprime(test *vector){
     int i;
     for (i=0; i<10; i++) printf("%d  ",vector[i].x);
     printf("\n\n");
}
 
int main(){
/*    struct test a, b;
    a.x = 69;
    b=a;
    printf("%d\n", b.x);
    system("PAUSE");*/
    int i;
    struct test vector[10];
    for (i=0; i<10; i++) vector[i].x = 10-i;
    imprime(vector);
    int atual = 2;
    qsort( &(vector[atual + 1]), 7, sizeof(struct test),compare);
    imprime(vector);
    system("PAUSE");
    
    
}
    
