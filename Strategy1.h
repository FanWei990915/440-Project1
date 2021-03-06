#ifndef Strategy1_H
#define Strategy1_H
#include "global.h"
#include "queue.h"
#include "stack.h"
#include "DFS.h"
#include "flamingFire.h"
int strategy1(char** maze, int dim, float q){
	int a, b;
	char **mazeFire = initial(dim + 2);
	char **mazeCopy = initial(dim + 2);
	for(int i = 0; i < dim + 2; i++){
		for(int j = 0; j < dim + 2; j++){
			mazeFire[i][j] = maze[i][j];
			mazeCopy[i][j] = maze[i][j];
		}
	}
	
	//record which cell is flaming
	Queue *qshort = NULL;
	Node *linklist = NULL;
	//randomly createa a fire and use * to represent
	srand((int)time(NULL));
	int all = dim * dim - 2;
	int randomnum;
	while(1 == 1){
		randomnum = rand() % all + 2;
	    a = randomnum % dim;
		b = randomnum / dim;
		if(a == 0 && maze[b][dim] == '0'){
			mazeFire[b][dim] = '*';
			mazeCopy[b][dim] = '*';
			Node *temp = (Node*)malloc(sizeof(Node));
			temp->x = b;
			temp->y = dim;
			temp->next = NULL;
			linklist = temp;
			break;
		}
		else if(maze[b + 1][a] == '0'){
			mazeFire[b + 1][a] = '*';
			mazeCopy[b + 1][a] = '*';
			Node *temp = (Node*)malloc(sizeof(Node));
			temp->x = b + 1;
			temp->y = a;
			temp->next = NULL;
			linklist = temp;
			break;
		}
	}
	
	//if we cannot meet the fire, we discard it
	if(reachable(maze, dim, linklist->x, linklist->y) == 0) return 3;
	
	//shortest path
	qshort = BFS(maze, dim, 1, 1);
	if(qshort == NULL) return 3;
	Stack *stack = NULL;
	while(qshort != NULL){
		stack = pushstack(stack, qshort->front->x, qshort->front->y);
		qshort = pop(qshort);
	}

	while(stack != NULL){
		linklist = flaming(mazeFire, dim, linklist, q, mazeCopy);

		if(mazeFire[stack->head->x][stack->head->y] == '*') return 0;
		mazeCopy[stack->head->x][stack->head->y] = '2';
		//printMaze(mazeCopy, dim);
		//sleep(1);
		//system("clear");
		stack = popstack(stack);
	}
	//printMaze(mazeCopy, dim);
	return 1;

}

#endif