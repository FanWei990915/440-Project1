#include "global.h"
int main(){
	//printMaze(mazeGenerator(10,0.23),10);

	clock_t start, end, start1;
    start1 = clock();
	int Sx = 0, Sy = 0, Gx = 0, Gy = 0, a, b;
	int dim = 750;
	int allcell = dim * dim;
	char **maze;
	for(int i = 0; i < 1000; i++){
	maze = mazeGenerator(dim,0.30);



	start = clock();
	printf("time: %f s\n", ((double)(start - start1)) / CLOCKS_PER_SEC);
	reachable(maze, dim);



    end = clock();
    printf("time: %f s\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    }
    return 0;

}