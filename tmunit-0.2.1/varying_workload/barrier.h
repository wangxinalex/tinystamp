#ifndef ______BARRIER_H________
#define ______BARRIER_H________

#include <stdio.h>
#include <pthread.h>

typedef struct barrier {
	pthread_cond_t complete;
	pthread_mutex_t mutex;
	int count;
	int crossing;
} barrier_t;

void barrier_init(barrier_t *b, int n);
void barrier_cross(barrier_t *b);
extern barrier_t barrier;


#endif
