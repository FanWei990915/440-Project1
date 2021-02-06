#include"global.h"
#include"BFS.h"
#include"DFS.h"
#include"queue.h"
#include"stack.h"
#include"Astar.h"

pnode heap[100000000];
int main(){
	//printMaze(mazeGenerator(10,0.23),10);

	int dim = 50;
	float density = 0.30;
	char **maze;

	maze = mazeGenerator(dim, density);

//printf("%d\n", RAND_MAX);

	clock_t start, end, start1;
    start1 = clock();
	
  //  BFS(maze, dim);
	start = clock();
	printf("time: %f s\n", ((double)(start - start1)) / CLOCKS_PER_SEC);
	//reachable(maze, dim);

	//optimization(maze, dim);
	
	BFS(maze, dim);
	//freememory(maze, dim + 2);

	Astar(maze, dim, heap);
	
    end = clock();
    printf("time: %f s\n", ((double)(end - start)) / CLOCKS_PER_SEC);

   
    return 0;
}