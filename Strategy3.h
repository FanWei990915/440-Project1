#ifndef Strategy3_H
#define Strategy3_H
#include "global.h"
#include "queue.h"
#include "stack.h"
#include "DFS.h"
#include "flamingFire.h"

int strategy3(char** maze, int dim, float q){
	int a, b;
	char **mazeFire = initial(dim + 2);
	char **mazeCopy = initial(dim + 2);
	char **mazePenalty = initial(dim + 2);
	char **Visit = initial(dim + 2);
	int  **Distance = (int**)malloc((dim + 2) * sizeof(int*));
	char **Prev =  initial(dim + 2);
	for(int i = 0; i < dim + 2; i++){
		Distance[i] = (int*)malloc((dim + 2) * sizeof(int));
		for(int j = 0; j < dim + 2; j++) Distance[i][j] = 0;
	}
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
	if(reachable(maze, dim, linklist->x, linklist->y) == 0) return 3;	

	int fireX = linklist->x;
	int fireY = linklist->y;

	for(int i = 1; i <= dim; i++){
		for(int j = 1; j <= dim; j++){
			mazePenalty[i][j] = dim * 2 - 2 - abs(fireX - i) - abs(fireY - j);			
		}
	}
   	
	Node* priority = (Node*)malloc(sizeof(Node));
	priority->x = 1;
	priority->y = 1;
	priority->next = NULL;
	maze[fireX][fireY] = '1';
	while(priority != NULL){	
		int tempX = priority->x;
		int tempY = priority->y;
		int tempDistance = Distance[tempX][tempY];
		if(Visit[tempX][tempY] == '0'){
			
			if(maze[tempX][tempY + 1] == '0' && Visit[tempX][tempY + 1] == '0'){
				int newDis = tempDistance + mazePenalty[tempX][tempY + 1];
				if(newDis < Distance[tempX][tempY + 1] || Prev[tempX][tempY + 1] == '0'){
					Distance[tempX][tempY + 1] = newDis;
					Prev[tempX][tempY + 1] = 'z';
					Node *p1 = priority;
					int flag = 0;
					Node *insert = (Node*)malloc(sizeof(Node));
					insert->x = tempX;
					insert->y = tempY + 1;
					insert->next = NULL;
					while(p1->next != NULL){
						int xx = p1->next->x;
						int yy = p1->next->y;
						if(Distance[xx][yy] >= newDis){
							insert->next = p1->next;
							p1->next = insert;
							flag = 1;
							break;
						}
						p1 = p1->next;
					}
					if(flag == 0) p1->next = insert;
				}
			}

			if(maze[tempX][tempY - 1] == '0' && Visit[tempX][tempY - 1] == '0'){
				int newDis = tempDistance + mazePenalty[tempX][tempY - 1];
				if(newDis < Distance[tempX][tempY - 1] || Prev[tempX][tempY - 1] == '0'){
					Distance[tempX][tempY - 1] = newDis;
					Prev[tempX][tempY - 1] = 'y';
					Node *p1 = priority;
					int flag = 0;
					Node *insert = (Node*)malloc(sizeof(Node));
					insert->x = tempX;
					insert->y = tempY - 1;
					insert->next = NULL;
					while(p1->next != NULL){
						int xx = p1->next->x;
						int yy = p1->next->y;
						if(Distance[xx][yy] >= newDis){
							insert->next = p1->next;
							p1->next = insert;
							flag = 1;
							break;
						}
						p1 = p1->next;
					}
					if(flag == 0) p1->next = insert;
				}
			}

			if(maze[tempX + 1][tempY] == '0' && Visit[tempX + 1][tempY] == '0'){
				int newDis = tempDistance + mazePenalty[tempX + 1][tempY];
				if(newDis < Distance[tempX + 1][tempY] || Prev[tempX + 1][tempY] == '0'){
					Distance[tempX + 1][tempY] = newDis;
					Prev[tempX + 1][tempY] = 's';
					Node *p1 = priority;
					int flag = 0;
					Node *insert = (Node*)malloc(sizeof(Node));
					insert->x = tempX + 1;
					insert->y = tempY;
					insert->next = NULL;
					while(p1->next != NULL){
						int xx = p1->next->x;
						int yy = p1->next->y;
						if(Distance[xx][yy] >= newDis){
							insert->next = p1->next;
							p1->next = insert;
							flag = 1;
							break;
						}
						p1 = p1->next;
					}
					if(flag == 0) p1->next = insert;
				}
			}

			if(maze[tempX - 1][tempY] == '0' && Visit[tempX - 1][tempY] == '0'){
				int newDis = tempDistance + mazePenalty[tempX - 1][tempY];
				if(newDis < Distance[tempX - 1][tempY] || Prev[tempX - 1][tempY]){
					Distance[tempX - 1][tempY] = newDis;
					Prev[tempX - 1][tempY] = 'x';
					Node *p1 = priority;
					int flag = 0;
					Node *insert = (Node*)malloc(sizeof(Node));
					insert->x = tempX - 1;
					insert->y = tempY;
					insert->next = NULL;
					while(p1->next != NULL){
						int xx = p1->next->x;
						int yy = p1->next->y;
						if(Distance[xx][yy] >= newDis){
							insert->next = p1->next;
							p1->next = insert;
							flag = 1;
							break;
						}
						p1 = p1->next;
					}
					if(flag == 0) p1->next = insert;
				}
			}
		}
		Visit[tempX][tempY] = '1';
		priority = priority->next;
	}

	if(Prev[dim][dim] == '0') return 3;
	Node *solution = (Node*)malloc(sizeof(Node));
	solution->x = dim;
	solution->y = dim;
	solution->next = NULL;
	Node *p2 = solution;
	int pathX = dim, pathY = dim;
	while(!(pathX == 1 && pathY == 1)){
		if(Prev[pathX][pathY] == 'z') pathY--;
		else if(Prev[pathX][pathY] == 's') pathX--;
		else if(Prev[pathX][pathY] == 'y') pathY++;
		else if(Prev[pathX][pathY] == 'x') pathX++;
		Node *tt = (Node*)malloc(sizeof(Node));
		tt->x = pathX;
		tt->y = pathY;
		tt->next = NULL;
		p2->next = tt;
		p2 = p2->next;
	}
	Stack *stack = NULL;
	while(solution != NULL){
		stack = pushstack(stack, solution->x, solution->y);
		solution = solution->next;
	}

	while(stack != NULL){
		linklist = flaming(mazeFire, dim, linklist, q, mazeCopy);

		if(mazeFire[stack->head->x][stack->head->y] == '*') return 0;
		mazeCopy[stack->head->x][stack->head->y] = '2';
		printMaze(mazeCopy, dim);
		sleep(1);
		system("clear");
		stack = popstack(stack);
	}
	return 1;
}
#endif