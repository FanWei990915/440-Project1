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

void swap(pnode heap[], int a, int b){
		int tempx, tempy, temptotal;
		tempx = heap[a].x;
		tempy = heap[a].y;
		temptotal = heap[a].total;
		heap[a].x = heap[b].x;
		heap[a].y = heap[b].y;
		heap[a].total = heap[b].total;
		heap[b].x = tempx;
		heap[b].y = tempy;
		heap[b].total = temptotal;
}

//binary heap push
void pushh(int x, int y, float total, int size, pnode heap[], int dim){
	heap[size].x = x;
	heap[size].y = y;
	heap[size].total = total;
	while(size > 1){
		if(heap[size].total >= heap[size/2].total) break;
		swap(heap, size, size/2);
		size = size / 2;
	}
}

//binary heap pop
void poph(pnode heap[], int size, int dim){
	heap[1].x = heap[size].x;
	heap[1].y = heap[size].y;
	heap[1].total = heap[size].total;
	size--;
	int temp2, temp = 1;
	while((temp * 2) <= size){
		if((temp * 2 + 1) <= size){
			temp2 = (heap[temp * 2].total<heap[temp * 2 + 1].total)?(temp * 2):(temp * 2 + 1);
			if(heap[temp2].total <= heap[temp].total){
				swap(heap, temp2, temp);
				temp = temp2;
			}else break;
		}else if(heap[temp * 2].total <= heap[temp].total){
			swap(heap, temp * 2, temp);
			temp<<=1;
		}else break;
	}
}

//heuristic function(2 different formula)
float distance(int dim, int x, int y){
	//float a = (1+(float)(1/(dim*2-x-y)))*sqrt((dim - x) * (dim - x) + (dim - y) * (dim - y));
	//return a;
	return (dim * 2 - x - y);
}

void initialmc(int x, int y, int dis, da **maze, char prev, int size, pnode heap[], int dim){
	maze[x][y].distance = dis;
	maze[x][y].prev = prev;
	pushh(x, y, distance(dim, x, y) + (float)dis, size, heap, dim);
}


Node* Astar(char** maze, int dim, pnode heap[]){
	int x, y, tempdis, size = 1;
	heap[1].x = 1;
	heap[1].y = 1;

	float total = distance(dim, 1, 1);

	heap[1].total = total;

	da **mazeCopy = (da**)malloc((dim + 2) * sizeof(da*));
	for(int i = 0; i <= dim + 1; i++){
		mazeCopy[i] = (da*)malloc((dim + 2) * sizeof(da));
		for(int j  = 0; j <= dim + 1; j++){
			if(maze[i][j] == '1') mazeCopy[i][j].status = '1';
			else mazeCopy[i][j].status = '0';
			mazeCopy[i][j].distance = 0;
			mazeCopy[i][j].prev = '0';
		}
	}
	mazeCopy[dim][dim].status = '3';
	
	while(size > 0){
		x = heap[1].x;
		y = heap[1].y;
		//if(mazeCopy[x][y].status == '3')break;
		
		//if new distance is less than past or the cell is totaly unvisited, we update new data to it. store them in piroity queue
		if(mazeCopy[x][y].status == '0'){
			tempdis = mazeCopy[x][y].distance;
			//right
			if(mazeCopy[x][y + 1].status == '0'){
				if(mazeCopy[x][y + 1].prev == '0'){
					initialmc(x, y + 1, tempdis + 1, mazeCopy, 'z', ++size, heap, dim);//update
				}
				else if(mazeCopy[x][y + 1].distance > (tempdis + 1)){
					initialmc(x, y + 1, tempdis + 1, mazeCopy, 'z', ++size, heap, dim);//update
				}
			}
			if(mazeCopy[x][y + 1].status == '3') break;
			
			//down
			if(mazeCopy[x + 1][y].status == '0'){
				if(mazeCopy[x + 1][y].prev == '0'){
					initialmc(x + 1, y, tempdis + 1, mazeCopy, 's', ++size, heap, dim);
				}
				else if(mazeCopy[x + 1][y].distance > (tempdis + 1)){
					initialmc(x + 1, y, tempdis + 1, mazeCopy, 's', ++size, heap, dim);
				}
				
			}
			if(mazeCopy[x + 1][y].status == '3') break;
			//left
			if(mazeCopy[x][y - 1].status == '0'){
				if(mazeCopy[x][y - 1].prev == '0'){
					initialmc(x, y - 1, tempdis + 1, mazeCopy, 'y', ++size, heap, dim);
				}
				else if(mazeCopy[x][y - 1].distance > (tempdis + 1)){
					initialmc(x, y - 1, tempdis + 1, mazeCopy, 'y', ++size, heap, dim);		
				}		
				
			}
			if(mazeCopy[x][y - 1].status == '3') break;
			//up
			if(mazeCopy[x - 1][y].status == '0'){
				if(mazeCopy[x - 1][y].prev == '0'){
					initialmc(x - 1, y, tempdis + 1, mazeCopy, 'x', ++size, heap, dim);
				}
				else if(mazeCopy[x - 1][y].distance > (tempdis + 1)){
					initialmc(x - 1, y, tempdis + 1, mazeCopy, 'x', ++size, heap, dim);
				}
			
			}
			if(mazeCopy[x - 1][y].status == '3') break;

			
		}
		mazeCopy[x][y].status = '2';
		poph(heap, size, dim);
		size--;
	}
	if(mazeCopy[dim][dim - 1].prev != '0') mazeCopy[dim][dim].prev = 'z';
	else if(mazeCopy[dim - 1][dim].prev != '0') mazeCopy[dim][dim].prev = 's';
	else return NULL;
	//record the path
	Node *solution = (Node*)malloc(sizeof(Node));
	solution->x = dim;
	solution->y = dim;
	solution->next = NULL;
	Node *p2 = solution;
	int pathX = dim, pathY = dim;
	while(!(pathX == 1 && pathY == 1)){
		if(mazeCopy[pathX][pathY].prev == 'z') pathY--;
		else if(mazeCopy[pathX][pathY].prev == 's') pathX--;
		else if(mazeCopy[pathX][pathY].prev == 'y') pathY++;
		else if(mazeCopy[pathX][pathY].prev == 'x') pathX++;
		Node *tt = (Node*)malloc(sizeof(Node));
		tt->x = pathX;
		tt->y = pathY;
		tt->next = NULL;
		p2->next = tt;
		p2 = p2->next;
	}
	return solution;
	/*for(int i = 1; i <= dim; i++){
		for(int j = 1; j <= dim; j++){
			if(mazeCopy[i][j].status == '1') printf("\033[01;34m1 \033[0m");
			else if(mazeCopy[i][j].status == '2') printf("\033[01;32m2 \033[0m");
			else printf("%c ", mazeCopy[i][j].status);
			//printf("%c", mazeCopy[i][j].prev);
		}
		printf("\n");
	
	}
	for(int i = 1; i <= dim; i++){
		for(int j = 1; j <= dim; j++){
			//if(mazeCopy[i][j].status == '1') printf("\033[01;34m1 \033[0m");
			//else if(mazeCopy[i][j].status == '2') printf("\033[01;32m2 \033[0m");
			//else printf("%c ", mazeCopy[i][j].status);
			printf("%c", mazeCopy[i][j].prev);
		}
		printf("\n");
	
	}*/

	


}

#endif