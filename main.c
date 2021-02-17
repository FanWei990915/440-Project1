#include"global.h"
#include"BFS.h"
#include"DFS.h"
#include"queue.h"
#include"stack.h"
#include"Astar.h"

pnode heap[100000000];
int main(){
/*	int dim; 
	float density; 
	char **maze;
	printf("Welcome to CS440-project-1.\nThis code is tested under macOS.\nSome libraries such as unistd may not be available on Windows or Linux\nDue to the size of the screen, we only print mazes with dimension less than 200. For larger mazes we only print running time  \nPlease enter the dimension of the maze and press enter to continue\n");
	scanf("%d", &dim);
	printf("Please enter the density of the walls in the maze and press enter to continue\n");
	scanf("%f", &density);
	maze = mazeGenerator(dim, density);
	if(dim <= 200)printMaze(maze, dim);*/

//printf("%d\n", RAND_MAX);
/*	int total = 0;
	float p;
	char **maze;
	for(int i = 20; i <=80; i++){
		p = i/200.0;
		for(int j = 0; j < 1000; j++){
			maze = mazeGenerator(500,p );
			if(reachable(maze, 500) == 1) total ++;
		}
		printf("%f,%f,,,,\n", p, total/1000.0);
		total = 0;

	}*/
	char** maze  = mazeGenerator(500, 0);
	Astar(maze, 500, heap);

/*	clock_t start, end, start1;
    start1 = clock();
	char** maze = mazeGenerator(5000, 0.5);
   // BFS(maze, dim);
	start = clock();
	printf("time: %f s\n", ((double)(start - start1)) / CLOCKS_PER_SEC);
	reachable(maze, 5000);*/

	//optimization(maze, dim);
	
	//BFS(maze, dim);
	//freememory(maze, dim + 2);

	//Astar(maze, dim, heap);



 //   end = clock();
   // printf("time: %f s\n", ((double)(end - start)) / CLOCKS_PER_SEC);

   
    return 0;
}