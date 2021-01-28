#include "global.h"
int main(){
	//printMaze(mazeGenerator(10,0.23),10);
		printMaze(reachable(mazeGenerator(10,0.15), 10, 3,3,7,9),10);
}