#include"global.h"
#include"BFS.h"
#include"DFS.h"
#include"queue.h"
#include"stack.h"
int main(){
	//printMaze(mazeGenerator(10,0.23),10);

	int Sx = 0, Sy = 0, Gx = 0, Gy = 0, a, b;
	int dim = 20000;
	int allcell = dim * dim;
	char **maze;

	maze = mazeGenerator(dim,0.25);



	clock_t start, end, start1;
    start1 = clock();
	
    BFS(maze, dim);
	start = clock();
	printf("time: %f s\n", ((double)(start - start1)) / CLOCKS_PER_SEC);
	//reachable(maze, dim);

	//optimization(maze, dim);

	BBFS(maze, dim);
	//freememory(maze, dim + 2);


    end = clock();
    printf("time: %f s\n", ((double)(end - start)) / CLOCKS_PER_SEC);

   
    return 0;
}