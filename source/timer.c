#include "../include/timer.h"

#include <time.h>

clock_t timer;

// O(1)
void timer_reset() {
	timer = clock();
}

// O(1)
double timer_get() {
	return ((double)(clock() - timer)) / CLOCKS_PER_SEC;
}