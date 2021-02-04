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
	char status;
}da;
void pushh(int x, int y, float total, int size, pnode heap[]){

}
void poph(){

}

float distance(int dim, int x, int y){
	return sqrt((dim - x) * (dim - x) + (dim - y) * (dim - y));
}

void initialmc(int x, int y, int dis, da **maze, char prev, int size, pnode heap[]){
	maze[x][y]->distance = dis;
	maze[x][y]->prev = prev;
	pushh(x, y, distance(dim, x, y) + dis, size, heap);
}


void Astar(char** maze, int dim, pnode heap[]){
	int x, y, tempdis, size = 1;
	heap[1].x = 1;
	heap[1].y = 1;
	float total = distance(dim, 1, 1);
	heap[1].total = total;

	da **mazeCopy = (da**)malloc((dim + 1) * sizeof(da*));
	for(int i = 0; i <= dim; i++){
		mazeCopy[i] = (da*)malloc((dim + 1) * sizeof(da));
		for(int j  = 0; j <= dim; j++){
			da[i][j]->status = '0';
			da[i][j]->distance = 0;
			da[i][j]->prev = '0';
	}
	
	while(size > 0){
		x = heap[1].x
		y = heap[1].y
		if(mazeCopy[x][y]->status == '0'){
			tempdis = mazeCopy[x][y]->distacnce;
			if(mazeCopy[x][y + 1]->status == '0' && maze[dim][dim] == '0'){
				if(mazeCopy[x][y + 1]->prev == '0') initialmc(x, y + 1, tempdis + 1, mazeCopy, 'z', ++size, heap);
				else if(mazeCopy[x][y + 1]->distance > (tempdis + 1)) initialmc(x, y + 1, tempdis + 1, mazeCopy, 'z', ++size, heap);
			}
			if(maze[x + 1][y] == '0' && maze[dim][dim] == '0'){
				if(mazeCopy[x + 1][y]->prev == '0') initialmc(x + 1, y, tempdis + 1, mazeCopy, 's', ++size, heap);
				else if(mazeCopy[x + 1][y]->distance > (tempdis + 1)) initialmc(x + 1, y, tempdis + 1, mazeCopy, 's', ++size, heap);
			}
			if(maze[x][y - 1] == '0' && maze[dim][dim] == '0'){
				if(mazeCopy[x][y - 1]->prev == '0') initialmc(x, y - 1, tempdis + 1, mazeCopy, 'y', ++size, heap);
				else if(mazeCopy[x][y - 1]->distance > (tempdis + 1)) initialmc(x, y - 1, tempdis + 1, mazeCopy, 'y', ++size, heap);				
			}
			if(maze[x - 1][y] == '0' && maze[dim][dim] == '0'){
				if(mazeCopy[x - 1][y]->prev == '0') initialmc(x - 1, y, tempdis + 1, mazeCopy, 'x', ++size, heap);
				else if(mazeCopy[x - 1][y]->distance > (tempdis + 1)) initialmc(x - 1, y, tempdis + 1, mazeCopy, 'x', ++size, heap);›››
			}
		}
		pop()
		size--;
	}
}


#endif