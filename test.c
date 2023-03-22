#include "philosopher.h"

int main()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	printf("tv_sec: %ld\ntv_usec: %d\n", t.tv_sec, t.tv_usec);
}