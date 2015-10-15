//
//  children.c
//  ChocolateFactory
//  CMPT 330 -- Fall 2013
//
//  Tyler Kuipers
//  October 14, 2015
//

#include "ChocolateFactory.h"
void printBox(candy_struct* in, int size){
	printf("Wonka, I have: ");
	for(int i = 0; i < size; i++){
		printf("%s %d", in[i].color, in[i].num);
		if(i != size-1){
			printf(", ");
		}
		else{
			printf(".");
		}
	}
		printf("\n");
	return;
}
void *oompaChild(void *boxSize) {
	int size = ((candy_struct *)boxSize)->num;
	candy_struct* box = malloc(size * sizeof(candy_struct));
	while (1){
		//grab the stuff off the assembly line
		for (int i = 0; i < size; ++i) {
			pthread_mutex_lock(&mutex);
			if (!emptyBuffer()) {
				box[i] = removeCandy();
			}
			else {
				--i;
			}
			// pthread_mutex_unlock(&mutex);
			// print the contents of the box
			if (i == size - 1) {
				// pthread_mutex_lock(&mu`tex);
				printBox(box, size);
			}
			pthread_mutex_unlock(&mutex);
		}
	}
	pthread_exit(NULL);
}
