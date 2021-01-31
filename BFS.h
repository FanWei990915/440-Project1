
#ifndef BFS_H
#define BFS_H

#include"global.h"
#include"queue.h"
//a BFS algorithm to find the shortest path
Queue* shortpath(char** maze, int dim){
	if(maze[dim][dim] == '0'){
		printf("No Solution for this Maze!\n");
		return NULL;
	}
	int x, y;
	Queue *queue = NULL;
	queue = push(queue,dim ,dim);
	x = queue->back->x; 
	y = queue->back->y;
	while(!(x == 1 && y == 1)){
		if(maze[x][y] == 'z') y--;
		else if(maze[x][y] == 's') x--;
		else if(maze[x][y] == 'y') y++;
		else if(maze[x][y] == 'x') x++;
		queue = push(queue, x, y);
		//printf("%d %d\n", x, y);
	};
	return queue;
}

void printBFS(char** maze, Queue *queue){
	int dim = queue->front->x;
	while(queue != NULL){
		maze[queue->front->x][queue->front->y] = '2';
		queue = pop(queue);
	}
	printMaze(maze, dim);
}
void rBFS(char** maze, int dim, Queue* queue){
/*	if(queue == NULL || maze[dim][dim] != '0') return;
	int n = queue->size;
	for(int i = 0; i < n; i++){
		int Sx = queue->front->x, Sy = queue->front->y;
		if(maze[Sx][Sy + 1] == '0' && maze[dim][dim] == '0'){
			maze[Sx][Sy + 1] = 'z';//previous is left
			queue = push(queue, Sx, Sy + 1);
		}
		if(maze[Sx + 1][Sy] == '0' && maze[dim][dim] == '0'){
			maze[Sx + 1][Sy] = 's';//previous is up
			queue = push(queue, Sx + 1, Sy);
		}
		if(maze[Sx][Sy - 1] == '0' && maze[dim][dim] == '0'){
			maze[Sx][Sy - 1] = 'y';//previous is right
			queue = push(queue, Sx, Sy - 1);
		}
		if(maze[Sx - 1][Sy] == '0' && maze[dim][dim] == '0'){
			maze[Sx - 1][Sy] = 'x';//previous is down
			queue = push(queue, Sx - 1, Sy);
		}
		queue = pop(queue);
	}
	rBFS(maze, dim, queue);	*/
	while(((queue!= NULL) && (maze[dim][dim] == '0'))){
		int n = queue->size;
		for(int i = 0; i < n; i++){
			int Sx = queue->front->x;
			int Sy = queue->front->y;
			if(maze[Sx][Sy + 1] == '0'){
				maze[Sx][Sy + 1] = 'z';//previous is left
				queue = push(queue, Sx, Sy + 1);
			}
			if(maze[Sx + 1][Sy] == '0'){
				maze[Sx + 1][Sy] = 's';//previous is up
				queue = push(queue, Sx + 1, Sy);
			}
			if(maze[Sx][Sy - 1] == '0'){
				maze[Sx][Sy - 1] = 'y';//previous is right
				queue = push(queue, Sx, Sy - 1);
			}
			if(maze[Sx - 1][Sy] == '0'){
				maze[Sx - 1][Sy] = 'x';//previous is down
				queue = push(queue, Sx - 1, Sy);
			}
			queue = pop(queue);
		}
	}
}



void BFS(char** maze, int dim){
	Queue *queue = NULL;
	queue = push(queue, 1, 1);
	char **mazeCopy = initial(dim + 2);
	for(int i = 0; i < dim + 2; i++){
		for(int j = 0; j < dim + 2; j++) mazeCopy[i][j] = maze[i][j];
	}
	mazeCopy[1][1] = '3';
	rBFS(mazeCopy, dim, queue);
	queue = shortpath(mazeCopy, dim);
//	printMaze(mazeCopy, dim);
	for(int i = 0; i < dim + 2; i++){
		for(int j = 0; j < dim + 2; j++) mazeCopy[i][j] = maze[i][j];
	}
//	if(queue != NULL) printBFS(mazeCopy, queue);
	freememory(mazeCopy, dim + 2);
}
#endif