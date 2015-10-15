#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/signal.h>


typedef struct candy {
	char* color;
	int num;
} candy_t;

void *oompaLoompa(void*);
void *child(void*);
void insertCandy(candy_t* data);
candy_t removeCandy();
int isFull();
int isEmpty();

pthread_mutex_t mutex;
pthread_cond_t condC, condO;