#ifndef Strategy2_H
#define Strategy2_H
#include "global.h"
#include "queue.h"
#include "stack.h"
#include "DFS.h"
#include "flamingFire.h"

int strategy2(char** maze, int dim, float q){
	int a, b;
	char **mazeFire = initial(dim + 2);
	char **mazeCopy = initial(dim + 2);
	for(int i = 0; i < dim + 2; i++){
		for(int j = 0; j < dim + 2; j++){
			mazeFire[i][j] = maze[i][j];
			mazeCopy[i][j] = maze[i][j];
		}
	}
	
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
		stack = popstack(stack);
		if(stack == NULL) break;
		Node *t = stack->head;
		
		/*if the new fire does not affect our original path, we do not need to search the shortest path again
			because we will get same path as the original one.*/
		while(t != NULL){
			if(mazeFire[t->x][t->y] == '*'){
				
				//search the shortest path again
				qshort = BFS(mazeFire, dim, stack->head->x, stack->head->y);
				if(qshort == NULL) return 0;
				stack = NULL;
				while(qshort != NULL){
					stack = pushstack(stack, qshort->front->x, qshort->front->y);
					qshort = pop(qshort);
				}
				break;
			}
			t = t->next;
		}
	//	printMaze(mazeCopy, dim);
	//	sleep(1);
	//	system("clear");
		
	}
	printMaze(mazeCopy, dim);
	return 1;

}
#endif