#include "ChocolateFactory.h"
void *oompaLoompa(void* info) {
	candy_t *data = (candy_t *)info;
	for (int i = 1; i < data->num + 1; ++i) {
		// printf("Making a %s candy.\n", data->color);
		// lock the mutex
		// check if the buffer is full
		// wait for it to empty
		// add a thing
		pthread_mutex_lock(&mutex);
		if (!isFull()) {
			printf("oompaLoompa %s is inserting onto buffer\n", data->color);
			candy_t *info = malloc(sizeof(candy_t));
			info->color = data->color;
			info->num = i;
			insertCandy(info);
			// printf("%d\n", i);
		}
		else {
			--i;
		}
		pthread_mutex_unlock(&mutex);
		// 
	}
	// here I loop and try to add candies to the buffer once i have created the correct number of candies i can exit.
	free(data);
	pthread_exit(NULL);
}