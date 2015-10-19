//
//  children.c
//  ChocolateFactory
//  CMPT 330 -- Fall 2013
//
//  Tyler deBoon 120030
//  October 7, 2015
//

#include "ChocolateFactory.h"

void *child(void *boxSize) {
	candy_t *data = (candy_t *)boxSize;
	int stillWorking = 1;
			// buffer = malloc(bufferSize * sizeof(candy_t));
	candy_t* box = malloc(data->num * sizeof(candy_t));
	while (stillWorking) {
		// create a box
		for (int i = 0; i < data->num; ++i) {
			pthread_mutex_lock(&mutex);
			if (!isEmpty()) {
				// printf("%d\n", i);
				box[i] = removeCandy();
			}
			else {
				--i;
			}
			// print box 
			if (i == data->num - 1) {
				printf("Wonka, I have: ");
				printf("%s %d", box[0].color, box[0].num);
				for (int i = 1; i < data->num; ++i)
				{
					printf(", %s %d", box[i].color, box[i].num);
				}
				printf("\n");
			}
			pthread_mutex_unlock(&mutex);
		}
		// start a new box
	}
	printf("Killed\n");
	free(data);
	pthread_exit(NULL);
}