#include "global.h"
#include"queue.h"

int main(){
	//printMaze(mazeGenerator(10,0.23),10);

/*	clock_t start, end, start1;
    start1 = clock();
	int Sx = 0, Sy = 0, Gx = 0, Gy = 0, a, b;
	int dim = 750;
	int allcell = dim * dim;
	char **maze;

	maze = mazeGenerator(dim,0.30);



	start = clock();
	printf("time: %f s\n", ((double)(start - start1)) / CLOCKS_PER_SEC);
	reachable(maze, dim);
	freememory(maze, dim + 2);


    end = clock();
    printf("time: %f s\n", ((double)(end - start)) / CLOCKS_PER_SEC);*/

    Queue *queue = NULL;
    queue = push(queue, 1, 2);
    printf("%d\n", queue->size);
    printf("%d %d\n", queue->front->x, queue->back->y); 
    queue = push(queue, 3, 4);
    printf("%d\n", queue->size);
    printf("%d %d\n", queue->front->x, queue->back->y);
    queue = push(queue, 7, 6);
    printf("%d\n", queue->size);
    printf("%d %d\n", queue->front->x, queue->back->y);
    pop(queue);
    printf("%d\n", queue->size);
    printf("%d %d\n", queue->front->x, queue->back->y);
    pop(queue);
    printf("%d\n", queue->size);
    printf("%d %d\n", queue->front->x, queue->back->y);
  	pop(queue);

   
    return 0;

}