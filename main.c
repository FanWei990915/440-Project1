#include "global.h"
int main(){
	//printMaze(mazeGenerator(10,0.23),10);
	//const int N = 1e2;
//	clock_t start, end;
 //   start = clock();
	int Sx = 0, Sy = 0, Gx = 0, Gy = 0, a, b;
	int dim = 500;
	int allcell = dim * dim;
	int **maze;
	maze = mazeGenerator(dim,0.15);


	srand((int)time(NULL));
	while(maze[Sx][Sy] == 1){
		a = rand() % allcell + 1;
		if((a % dim) == 0){
			Sx = a / dim;
			Sy = dim;
		}else{
			Sx = a / dim + 1;
			Sy = a % dim;
		}
	}
	while(maze[Gx][Gy] == 1){
		a = rand() % allcell + 1;
		if((a % dim) == 0){
			Gx = a / dim;
			Gy = dim;
		}else{
			Gx = a / dim + 1;
			Gy = a % dim;
		}
	}
	printf("%d %d %d %d\n" ,Sx,Sy,Gx,Gy);
	reachable(maze, dim, Sx, Sy, Gx, Gy);

	for(int i = 0; i < dim + 2; i++){
		free(maze[i]);
	}

 //   end = clock();
  //  printf("time: %f s\n", ((double)(end - start)) / CLOCKS_PER_SEC / N);
    return 0;

}