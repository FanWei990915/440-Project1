#ifndef flamingFire_H
#define flamingFire_H
#include "global.h"
//It is too time consuming to traverse all the points of the maze, so I store all cells that are flaming by a linklist.
int neighbor(int x, int y, char** maze){
	int temp = 0;
	if(maze[x][y + 1] == '*') temp++;
	if(maze[x][y - 1] == '*') temp++;
	if(maze[x + 1][y] == '*') temp++;
	if(maze[x - 1][y] == '*') temp++;
	return temp;
}

Node* ini(Node *newFireCopy, int x, int y){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->x = x;
	temp->y = y;
	temp->next = NULL;
	newFireCopy->next = temp;
	return newFireCopy->next;
}

Node* flaming(char** maze, int dim, Node *linklist, float q, char** mazeC){
	char **visit = initial(dim + 2);
	Node *temp1 = (Node*)malloc(sizeof(Node));
	temp1->next = linklist;
	Node *temp = temp1;
	int x, y;
	float prob;
	Node *newFire = (Node*)malloc(sizeof(Node));
	newFire->next = NULL;
	Node *newFireCopy = newFire;

	srand((int)time(NULL));
	while(temp->next != NULL){
		 int around = 0;
		 x = temp->next->x;
		 y = temp->next->y;
		 
		 if(visit[x][y + 1] == '2' || maze[x][y + 1] != '0') around++;
		 else if(maze[x][y + 1] == '0' && visit[x][y + 1] != '1'){
		 	prob = 1 - pow(1 - q, neighbor(x, y + 1, maze));
		 	float n = (float)rand()/RAND_MAX;
		 	if(n <= prob){
		 		newFireCopy = ini(newFireCopy, x, y + 1);
		 		around++;
		 		visit[x][y + 1] = '2';
		 	}else visit[x][y + 1] = '1';
		 }
		 
		 if(visit[x][y - 1] == '2' || maze[x][y - 1] != '0') around++;
		 else if(maze[x][y - 1] == '0' && visit[x][y - 1] != '1'){
		 	prob = 1 - pow(1 - q, neighbor(x, y - 1, maze));
		 	float n = (float)rand()/RAND_MAX;
		 	if(n <= prob){
		 		newFireCopy = ini(newFireCopy, x, y - 1);
		 		around++;
		 		visit[x][y - 1] = '2';
		 	}else visit[x][y - 1] = '1';
		 }
		 
		 if(visit[x - 1][y] == '2' || maze[x - 1][y] != '0') around++;
		 else if(maze[x - 1][y] == '0' && visit[x - 1][y] != '1'){
		 	prob = 1 - pow(1 - q, neighbor(x - 1, y, maze));
		 	float n = (float)rand()/RAND_MAX;
		 	if(n <= prob){
		 		newFireCopy = ini(newFireCopy, x - 1, y);
		 		around++;
		 		visit[x - 1][y] = '2';
		 	}else visit[x - 1][y] = '1';
		 }
		 
		 if(visit[x + 1][y] == '2' || maze[x + 1][y] != '0') around++;
		 else if(maze[x + 1][y] == '0' || visit[x + 1][y] != '1'){
		 	prob = 1 - pow(1 - q, neighbor(x + 1, y, maze));
		 	float n = (float)rand()/RAND_MAX;
		 	if(n <= prob){
				newFireCopy = ini(newFireCopy, x + 1, y);
		 		around++;
		 		visit[x + 1][y] = '2';
		 	}else visit[x + 1][y] = '1';
		 }

		 if(around == 4) temp->next = temp->next->next;
		 else temp = temp->next;
	}	

	while(newFire->next != NULL){
		x = newFire->next->x;
		y = newFire->next->y;
		if(maze[x][y] != '*'){
			maze[x][y] = '*';
			mazeC[x][y] = '*';
			Node *tempp = (Node*)malloc(sizeof(Node));
			tempp->x = x;
			tempp->y = y;
			tempp->next = NULL;
			temp->next = tempp;
			temp = temp->next;
		}
		newFire = newFire->next;
	}
	linklist = temp1->next;
	return linklist;
}

#endif