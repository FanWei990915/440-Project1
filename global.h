#ifndef GLOBAL_H
#define GLOBAL_H
#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include <unistd.h>

typedef struct Node{
	int x;
	int y;
	struct Node *next;
}Node;

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
		int a = randomnum % n;
		int b = randomnum / n;
		if(a == 0 && mazeMap[b][n] == '0'){
			mazeMap[b][n] = '1';
			temp++;
		}
		else if(mazeMap[b + 1][a] == '0'){
			mazeMap[b + 1][a] = '1';
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
			else if(maze[i][j] == '*') printf("\033[01;30m *\033[0m");
			else printf(" %c", maze[i][j]);
		}
		printf("\n");
	}
}

//Maze optimization 
void optimization(char** maze, int dim){
	int size = 0, total = 0;
	for(int i = 1; i <= dim; i++){
		for(int j = 1; j <= dim; j ++){
			if(maze[i][j] == '0'){
				total++;
				if(!((maze[i - 1][j] == '1' && maze[i + 1][j] == '1') || (maze[i][j + 1] == '1' && maze[i][j - 1] == '1'))){
					maze[i][i] = '2';
					size++;
				}
			
			}
		}
	}
	printf("%d %d\n", total, size);
	//printMaze(maze, dim);
}
#endif















