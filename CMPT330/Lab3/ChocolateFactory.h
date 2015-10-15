//
//  ChocolateFactory.h
//  ChocolateFactory
//  CMPT 330 -- Fall 2013
//
//  Tyler Kuipers
//  October 14, 2015
//


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/signal.h>


typedef struct candy {
	char* color;
	int num;
} candy_struct;

void *oompa(void*);
void *oompaChild(void*);
void insertCandy(candy_struct* data);
candy_struct removeCandy();
int fullBuffer();
int emptyBuffer();

pthread_mutex_t mutex;
pthread_cond_t condC, condO;

