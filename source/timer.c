#include "../include/timer.h"

#include <time.h>

clock_t timer;

void timer_reset() {
	timer = clock();
}

double timer_get() {
	return ((double)(clock() - timer)) / CLOCKS_PER_SEC;
}