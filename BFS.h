
#ifndef BFS_H
#define BFS_H
#include <unistd.h>
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

Queue* sshort(char** maze, int dim, Node* node){
	int Q1x, Q1y, Q2x, Q2y, Q1 = node->x - dim, Q2 = node->y - dim;
		if((Q1 % dim) == 0){
			Q1x = Q1 / dim;
			Q1y = dim;
		}else{
			Q1x = Q1 / dim + 1;
			Q1y = Q1 % dim;
		}
		if((Q2 % dim) == 0){
			Q2x = Q2 / dim;
			Q2y = dim;
		}else{
			Q2x = Q2 / dim + 1;
			Q2y = Q2 % dim;
		}
		Queue *queue = NULL;
		queue = push(queue, Q1x ,Q1y);
		int x = queue->back->x; 
		int y = queue->back->y;
		if(maze[x][y] == 'a' || maze[x][y] == 'b' || maze[x][y] == 'c' || maze[x][y] == 'd'){
			while(!(x == dim && y == dim)){
				if(maze[x][y] == 'a') y++;
				else if(maze[x][y] == 'b') x++;
				else if(maze[x][y] == 'c') y--;
				else if(maze[x][y] == 'd') x--;
				queue = push(queue, x, y);
			};
		}else{
			while(!(x == 1 && y == 1)){
				if(x == dim && y == dim) break;
				if(maze[x][y] == 'z') y--;
				else if(maze[x][y] == 's') x--;
				else if(maze[x][y] == 'y') y++;
				else if(maze[x][y] == 'x') x++;
				queue = push(queue, x, y);
			};
		}
		queue = push(queue, Q2x, Q2y);
		x = Q2x; 
		y = Q2y;
		if(maze[x][y] == 'a' || maze[x][y] == 'b' || maze[x][y] == 'c' || maze[x][y] == 'd'){
			while(!(x == dim && y == dim)){
				if(maze[x][y] == 'a') y++;
				else if(maze[x][y] == 'b') x++;
				else if(maze[x][y] == 'c') y--;
				else if(maze[x][y] == 'd') x--;
				queue = push(queue, x, y);
			};
		}else{
			while(!(x == 1 && y == 1)){
				if(x == dim && y == dim) break;
				if(maze[x][y] == 'z') y--;
				else if(maze[x][y] == 's') x--;
				else if(maze[x][y] == 'y') y++;
				else if(maze[x][y] == 'x') x++;
				queue = push(queue, x, y);
			};
		}
	return queue;
}

void printBFS(char** maze, Queue *queue, int dim){
	while(queue != NULL){
		maze[queue->front->x][queue->front->y] = '2';
		printMaze(maze, dim);
		sleep(1);
		queue = pop(queue);
		system("cls");
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
/*	while(((queue!= NULL) && (maze[dim][dim] == '0'))){
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
	}*/
}

Node* rBBFS(char** maze, int dim, Queue* queue1, Queue* queue2){
	while((queue1 != NULL) && (queue2 != NULL)){
		int Q1x = queue1->front->x, Q2x = queue2->front->x, Q1y = queue1->front->y, Q2y = queue2->front->y;	
		if(maze[Q1x][Q1y + 1] == '0'){
			maze[Q1x][Q1y + 1] = 'z';//previous is left
			queue1 = push(queue1, Q1x, Q1y + 1);
		}else if((int)maze[Q1x][Q1y + 1] > 60 && (int)maze[Q1x][Q1y + 1] < 110){
				Node *temp = (Node*)malloc(sizeof(Node));
				temp->x = Q1x * dim + Q1y;
				temp->y = Q1x * dim + Q1y + 1;
				temp->next = NULL;
			return temp;
		}
		if(maze[Q1x + 1][Q1y] == '0'){
			maze[Q1x + 1][Q1y] = 's';//previous is up
			queue1 = push(queue1, Q1x + 1, Q1y);
		}else if((int)maze[Q1x + 1][Q1y] > 60 && (int)maze[Q1x + 1][Q1y] < 110){
				Node *temp = (Node*)malloc(sizeof(Node));
				temp->x = Q1x * dim + Q1y;
				temp->y = (Q1x + 1) * dim + Q1y;
				temp->next = NULL;
			return temp;
		}
		if(maze[Q1x][Q1y - 1] == '0'){
			maze[Q1x][Q1y - 1] = 'y';//previous is right
			queue1 = push(queue1, Q1x, Q1y - 1);
		}else if((int)maze[Q1x][Q1y - 1] > 60 && (int)maze[Q1x][Q1y - 1] < 110){
				Node *temp = (Node*)malloc(sizeof(Node));
				temp->x = Q1x * dim + Q1y;
				temp->y = Q1x * dim + Q1y - 1;
				temp->next = NULL;
			return temp;
		}
		if(maze[Q1x - 1][Q1y] == '0'){
			maze[Q1x - 1][Q1y] = 'x';//previous is down
			queue1 = push(queue1, Q1x - 1, Q1y);
		}else if((int)maze[Q1x - 1][Q1y] > 60 && (int)maze[Q1x - 1][Q1y] < 110){
				Node *temp = (Node*)malloc(sizeof(Node));
				temp->x = Q1x * dim + Q1y;
				temp->y = (Q1x - 1) * dim + Q1y;
				temp->next = NULL;
			return temp;
		}
		

		if(maze[Q2x][Q2y - 1] == '0'){
			maze[Q2x][Q2y - 1] = 'a';//previous is right
			queue2 = push(queue2, Q2x, Q2y - 1);
		}else if((int)maze[Q2x][Q2y - 1] > 110){
				Node *temp = (Node*)malloc(sizeof(Node));
				temp->y = Q2x * dim + Q2y - 1;
				temp->x = Q2x * dim + Q2y;
				temp->next = NULL;
			return temp;
		}
		if(maze[Q2x - 1][Q2y] == '0'){
			maze[Q2x - 1][Q2y] = 'b';//previous is down
			queue2 = push(queue2, Q2x - 1, Q2y);
		}else if((int)maze[Q2x - 1][Q2y] > 110){
				Node *temp = (Node*)malloc(sizeof(Node));
				temp->y = (Q2x - 1) * dim + Q2y;
				temp->x = Q2x * dim + Q2y;
				temp->next = NULL;
			return temp;
		}
		if(maze[Q2x][Q2y + 1] == '0'){
			maze[Q2x][Q2y + 1] = 'c';//previous is left
			queue2 = push(queue2, Q2x, Q2y + 1);
		}else if((int)maze[Q2x][Q2y + 1] > 110){
				Node *temp = (Node*)malloc(sizeof(Node));
				temp->y = Q2x * dim + Q2y;
				temp->x = Q2x * dim + Q2y + 1;
				temp->next = NULL;
			return temp;
		}
		if(maze[Q2x + 1][Q2y] == '0'){
			maze[Q2x + 1][Q2y] = 'd';//previous is up
			queue2 = push(queue2, Q2x + 1, Q2y);
		}else if((int)maze[Q2x + 1][Q2y] > 110){
				Node *temp = (Node*)malloc(sizeof(Node));
				temp->y = Q2x * dim + Q2y;
				temp->x = (Q2x + 1) * dim + Q2y;
				temp->next = NULL;
			return temp;
		}
		queue1 = pop(queue1);
		queue2 = pop(queue2);
	}
	return NULL;
}
void BBFS(char** maze, int dim){
	Queue *queue1 = NULL, *queue2 = NULL;
	queue1 = push(queue1, 1, 1);
	queue2 = push(queue2, dim, dim);
	char **mazeCopy = initial(dim + 2);
	for(int i = 0; i < dim + 2; i++){
		for(int j = 0; j < dim + 2; j++) mazeCopy[i][j] = maze[i][j];
	}
	mazeCopy[1][1] = '3';
	mazeCopy[dim][dim] = '3';
	Node *node = rBBFS(mazeCopy, dim, queue1, queue2);
	if(node == NULL) printf("NO SOLUTION!\n");
	else{
		//printf("%d %d\n" ,node->x, node->y);
	/*	int Q1x, Q1y, Q2x, Q2y, Q1 = node->x, Q2 = node->y;
		if((Q1 % dim) == 0){
			Q1x = Q1 / dim;
			Q1y = dim;
		}else{
			Q1x = Q1 / dim;
			Q1y = Q1 % dim;
		}
		if((Q2 % dim) == 0){
			Q2x = Q2 / dim;
			Q2y = dim;
		}else{
			Q2x = Q2 / dim;
			Q2y = Q2 % dim;
		}
		printMaze(mazeCopy, dim);
		printf("%c %c\n",mazeCopy[Q1x][Q1y],mazeCopy[Q2x][Q2y]);
		mazeCopy[Q1x][Q1y] = '3';
		mazeCopy[Q2x][Q2y] = '3';
		printMaze(mazeCopy, dim);*/
		//queue1 = sshort(mazeCopy, dim, node);
	
	//	for(int i = 0; i < dim + 2; i++){
	//		for(int j = 0; j < dim + 2; j++) mazeCopy[i][j] = maze[i][j];
	//	}
	//	printBFS(mazeCopy, queue1, dim);

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
	//queue = shortpath(mazeCopy, dim);
	/*printMaze(mazeCopy, dim);
	printf("\n");
	for(int i = 0; i < dim + 2; i++){
		for(int j = 0; j < dim + 2; j++) mazeCopy[i][j] = maze[i][j];
	}*/
	//if(queue != NULL) printBFS(mazeCopy, queue, dim);
	//freememory(mazeCopy, dim + 2);
}
#endif