#include <sys/time.h>
#include <stdio.h>

int main () {
	struct timeval  twoForStart, oneForStart;
    struct timeval  twoForEnd, oneForEnd;
    double          oneForTemp, twoForTemp;
    int i, j, k, size = 10000;
    
    gettimeofday(&oneForStart, NULL);
    for (int k = 0; k < size * size; ++k) {
		i = k / size;
		j = k % size;
	}
	gettimeofday(&oneForEnd, NULL);

	gettimeofday(&twoForStart, NULL);
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
		}	
	}
	gettimeofday(&twoForEnd, NULL);
	
	oneForTemp = ((oneForEnd.tv_sec + ((double) oneForEnd.tv_usec / 1000000)) -
	        (oneForStart.tv_sec + ((double) oneForStart.tv_usec / 1000000)));

	twoForTemp = ((twoForEnd.tv_sec + ((double) twoForEnd.tv_usec / 1000000)) -
	        (twoForStart.tv_sec + ((double) twoForStart.tv_usec / 1000000)));

	printf("1 FOR: %.10lf seconds.\n", oneForTemp);
	printf("2 FOR: %.10lf seconds.\n", twoForTemp);
}