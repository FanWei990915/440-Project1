#ifndef Astar_H
#define Astar_H
#include<math.h>
#include "global.h"

typedef struct pnode{
	int x;
	int y;
	float total; //real distance plus predict
}pnode;

typedef struct da{
	char prev;
	int distance; //real distacne from source
}da;
void pushh(){

}
void poph(){

}

float distance(int dim, int x, int y){
	return sqrt((dim - x) * (dim - x) + (dim - y) * (dim - y));
}

void Astar(char** maze, int dim, pnode heap[]){
	int temp, x, y, size = 1;
	heap[1].x = 1;
	heap[1].y = 1;
	float total = distance(dim, 1, 1);
	char **mazeCopy = initial(dim + 2);
	for(int i = 0; i < dim + 2; i++){
		for(int j = 0; j < dim + 2; j++) mazeCopy[i][j] = maze[i][j];
	}
	mazeCopy[1][1] = '2';
	while(size > 0){
		x = heap[1].x
		y = heap[1].y
		if(mazeCopy[x][y + 1] == '0' && maze[dim][dim] == '0'){
			temp = 
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
	}
}


#endif