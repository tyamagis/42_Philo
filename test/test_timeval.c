#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	struct timeval tv;
	struct timezone tz;

	int i = 0;
	while (i < 100)
	{
		gettimeofday(&tv, &tz);
		printf("%ld, %ld\n", tv.tv_sec, tv.tv_usec);
		usleep(i*100000);
		i++;
	}
	return 0;
}