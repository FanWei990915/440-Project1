#ifndef HEADER_FILE
#define HEADER_FILE
#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include"queue.h"
void freememory(char** a, int n){
	for(int i = 0; i < n; i++)free(a[i]);
}

//This function will allocate for a square dynamic 2-dimensional array and initialize to 0.
char** initial(int n){
	char **temp = (char**)malloc(n*sizeof(char*));
	for(int i = 0; i < n; i++){
		temp[i] = (char*)malloc(n*sizeof(char));
		for(int j = 0; j < n; j++) temp[i][j] = '0';
	}
	return temp;	
}


/*This function will generate a maze with a given dimension n and obstacle density p. 
"1" will represent the cell in the maze is occupied and "0" will represent the cell is empty.
To make it easier to distinguish wheather it is boundary of the maze, we will add a circle of "1" to the maze.
*/
char** mazeGenerator(int n, float p){
	char **mazeMap = initial(n + 2);
	int totalNumOccupied = n * n * p, temp = 0, randomnum, allcell = n*n-2;
	
	//Add boundary to the maze
	for(int i = 0; i < n + 2; i++){
		mazeMap[0][i] = '1'; // top row
		mazeMap[n + 1][i] = '1'; // bottom row
		mazeMap[i][0] = '1'; //left side
		mazeMap[i][n + 1] = '1'; // right side
	}


	srand((int)time(NULL));

	//Randomly generate totalNumOccupied different numbers between 1 to n*n
	while(temp < totalNumOccupied){
		randomnum = rand() % allcell + 2;
		//transform them to coordinate and set it to "1"
		if((randomnum % n) == 0 && mazeMap[randomnum / n][n] == '0'){
			mazeMap[randomnum / n][n] = '1';
			temp++;
		}
		else if(mazeMap[randomnum / n + 1][randomnum % n] == '0'){
			mazeMap[randomnum / n + 1][randomnum % n] = '1';
			temp++;
		}
	}
	return mazeMap;
}


//print a maze
void printMaze(char** maze, int dim){
	for(int i = 0; i < dim + 2; i++){
		for(int j = 0; j < dim + 2; j++){
			if(maze[i][j] == '1') printf("\033[01;34m 1\033[0m");
			else if(maze[i][j] == '2') printf("\033[01;31m 2\033[0m");
			else if(maze[i][j] == '3') printf("\033[01;32m 3\033[0m");
			else printf(" %c", maze[i][j]);
		}
		printf("\n");
	}
}


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
		queue = pop(queue);
	}
	rBFS(maze, dim, queue);	
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
	if(queue != NULL) printBFS(mazeCopy, queue);
	freememory(mazeCopy, dim + 2);
}
#endif















