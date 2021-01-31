#ifndef HEADER_FILE3
#define HEADER_FILE3
#include "global.h"
/* a DFS algorithm that takes a maze and two locations within it, and determines whether one is 
   reachable from the other.*/
void rreachable(char** maze, int Sx, int Sy, int dim){
	if(Sx == dim && Sy == dim){
		maze[dim][dim] = '3';
		printf("REACHABLE\n");
		return;
	}
	if(maze[Sx][Sy + 1] == '0' && maze[dim][dim] != '3'){
		maze[Sx][Sy + 1] = '2';
		rreachable(maze, Sx, Sy + 1, dim);
	}
	if(maze[Sx + 1][Sy] == '0' && maze[dim][dim] != '3'){
		maze[Sx + 1][Sy] = '2';
		rreachable(maze, Sx + 1, Sy, dim);
	}
	if(maze[Sx][Sy - 1] == '0' && maze[dim][dim] != '3'){
		maze[Sx][Sy - 1] = '2';
		rreachable(maze, Sx, Sy - 1, dim);
	}
	if(maze[Sx - 1][Sy] == '0' && maze[dim][dim] != '3'){
		maze[Sx - 1][Sy] = '2';
		rreachable(maze, Sx - 1, Sy, dim);
	}
	return;


}
void reachable(char** maze, int dim){
	char **mazeCopy = initial(dim + 2);
	for(int i = 0; i < dim + 2; i++){
		for(int j = 0; j < dim + 2; j++) mazeCopy[i][j] = maze[i][j];
	}
	mazeCopy[1][1] = '3';
	rreachable(mazeCopy, 1, 1, dim);
	freememory(mazeCopy, dim + 2);
//	printMaze(mazeCopy, dim);
}
#endif