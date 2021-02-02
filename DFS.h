#ifndef DFS_H
#define DFS_H
#include "global.h"
#include "stack.h"
/* a DFS algorithm that takes a maze and two locations within it, and determines whether one is 
   reachable from the other.*/

void printDFS(char** maze, Stack *stack, int dim){
	if(stack == NULL || maze[dim][dim] == '0'){
		printf("No Solution for this Maze!\n");
	}else{
		while(stack != NULL){
			maze[stack->head->x][stack->head->y] = '3';
			stack = popstack(stack);
		}
		printMaze(maze, dim);
	}
}

void rreachable(char** maze, /*int Sx, int Sy,*/int dim, Stack *stack){
/*	if(Sx == dim && Sy == dim){
		maze[dim][dim] = '3';
		printf("REACHABLE\n");
		return;
	}
	if(maze[Sx][Sy + 1] == '0' && maze[dim][dim] != '3'){
		maze[Sx][Sy + 1] = '2';
		rreachable(maze, Sx, Sy + 1, dim);
	}
	if(maze[dim][dim] == '3') return;
	if(maze[Sx + 1][Sy] == '0' && maze[dim][dim] != '3'){
		maze[Sx + 1][Sy] = '2';
		rreachable(maze, Sx + 1, Sy, dim);
	}
	if(maze[dim][dim] == '3') return;
	if(maze[Sx][Sy - 1] == '0' && maze[dim][dim] != '3'){
		maze[Sx][Sy - 1] = '2';
		rreachable(maze, Sx, Sy - 1, dim);
	}
	if(maze[dim][dim] == '3') return;
	if(maze[Sx - 1][Sy] == '0' && maze[dim][dim] != '3'){
		maze[Sx - 1][Sy] = '2';
		rreachable(maze, Sx - 1, Sy, dim);
	}*/
	while(stack != NULL){
		if(maze[dim][dim] != '0') break;
		int Sx = stack->head->x;
		int Sy = stack->head->y;
		if(maze[Sx][Sy + 1] == '0'){
			stack = pushstack(stack, Sx, Sy + 1);
			maze[Sx][Sy + 1] = '2';
		}
		else if(maze[Sx + 1][Sy] == '0'){
			stack = pushstack(stack, Sx + 1, Sy);
			maze[Sx + 1][Sy] = '2';
		}
		else if(maze[Sx][Sy - 1] == '0'){
			stack = pushstack(stack, Sx, Sy - 1);
			maze[Sx][Sy - 1] = '2';
		}
		else if(maze[Sx - 1][Sy] == '0'){
			stack = pushstack(stack, Sx - 1, Sy);
			maze[Sx - 1][Sy] = '2';
		}
		else stack = popstack(stack);
	}
}
void reachable(char** maze, int dim){
	Stack *stack = NULL;
	stack = pushstack(stack, 1, 1);
	char **mazeCopy = initial(dim + 2);
	for(int i = 0; i < dim + 2; i++){
		for(int j = 0; j < dim + 2; j++) mazeCopy[i][j] = maze[i][j];
	}
	mazeCopy[1][1] = '3';
	rreachable(mazeCopy, dim, stack);
	if(mazeCopy[dim][dim] == '0') printf("NO SOLUTION!\n");;
	printDFS(mazeCopy, stack,dim);
	freememory(mazeCopy, dim + 2);
}
#endif