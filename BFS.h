
#ifndef BFS_H
#define BFS_H
#include <unistd.h>
#include"global.h"
#include"queue.h"
//a BFS algorithm to find the shortest path
Queue* shortpath(char** maze, int dim, int x1, int y1){
	if(maze[dim][dim] == '0'){
//		printf("No Solution for this Maze!\n");
		return NULL;
	}
	int x, y;
	Queue *queue = NULL;
	queue = push(queue,dim ,dim);
	x = queue->back->x; 
	y = queue->back->y;
	while(!(x == x1 && y == y1)){
		if(maze[x][y] == 'z') y--;
		else if(maze[x][y] == 's') x--;
		else if(maze[x][y] == 'y') y++;
		else if(maze[x][y] == 'x') x++;
		queue = push(queue, x, y);
		//printf("%d %d\n", x, y);
	};
	return queue;
}



void printBFS(char** maze, Queue *queue, int dim){
	while(queue != NULL){
		maze[queue->front->x][queue->front->y] = '2';
		printMaze(maze, dim);
	//	sleep(1);
		queue = pop(queue);
	//	system("cls");
	}
	//printMaze(maze, dim);
}
void rBFS(char** maze, int dim, Queue* queue){
	if(queue == NULL || maze[dim][dim] != '0') return;
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
	//	printMaze(maze, dim);
	//	sleep(1);
		queue = pop(queue);
	//	system("cls");
	}
	rBFS(maze, dim, queue);	

}

Queue* BFS(char** maze, int dim, int x, int y){
	Queue *queue = NULL;
	queue = push(queue, x, y);
	char **mazeCopy = initial(dim + 2);
	for(int i = 0; i < dim + 2; i++){
		for(int j = 0; j < dim + 2; j++) mazeCopy[i][j] = maze[i][j];
	}
	mazeCopy[x][y] = '3';
	rBFS(mazeCopy, dim, queue);
	queue = shortpath(mazeCopy, dim, x, y);
	return queue;
	//printMaze(mazeCopy, dim);
	//printf("\n");
//	for(int i = 0; i < dim + 2; i++){
//		for(int j = 0; j < dim + 2; j++) mazeCopy[i][j] = maze[i][j];
//	}
//	if(queue != NULL) printBFS(mazeCopy, queue, dim);
	//freememory(mazeCopy, dim + 2);
}
#endif