#include"global.h"
#include"BFS.h"
#include"DFS.h"
#include"queue.h"
#include"stack.h"
#include"Astar.h"

int main(){
	srand((int)time(NULL));
	for(int i = 0; i < 50; i++){
	
		float n = (float)rand()/RAND_MAX;
		printf("%f\n",n);
	}


	return 0;
}