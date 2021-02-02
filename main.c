#include"global.h"
#include"BFS.h"
#include"DFS.h"
#include"queue.h"
#include"stack.h"
int main(){
	//printMaze(mazeGenerator(10,0.23),10);

	int dim = 20;
	float density = 0.25;
	char **maze;

	maze = mazeGenerator(dim, density);



	clock_t start, end, start1;
    start1 = clock();
	
    BFS(maze, dim);
	start = clock();
	printf("time: %f s\n", ((double)(start - start1)) / CLOCKS_PER_SEC);
	//reachable(maze, dim);

	//optimization(maze, dim);

	//BBFS(maze, dim);
	//freememory(maze, dim + 2);


    end = clock();
    printf("time: %f s\n", ((double)(end - start)) / CLOCKS_PER_SEC);

   
    return 0;
}