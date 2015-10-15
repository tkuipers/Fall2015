//
//  ChocolateFactory.h
//  ChocolateFactory
//  CMPT 330 -- Fall 2013
//
//  Tyler Kuipers
//  October 14, 2015
//
#include "ChocolateFactory.h"
void *oompa(void* info) {
	for (int i = 1; i < ((candy_struct *)info)->num + 1; ++i) {
		// printf("On loop %d\n", i);
		pthread_mutex_lock(&mutex);
		if (!fullBuffer()) {
			candy_struct *oompaInfo = malloc(sizeof(candy_struct));
			oompaInfo->color = ((candy_struct *)info)->color;
			oompaInfo->num = i;
			// printf("inserting candy:\n\tColor: %s\n\tNumber: %d\n", oompaInfo->color, oompaInfo->num);
			insertCandy(oompaInfo);
		}
		else {
			--i;
		}
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}