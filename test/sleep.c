#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

void	print_time(int l, int sec, struct timeval s, struct timeval e)
{
	unsigned long	ms = (e.tv_usec - s.tv_usec);
	ms += (e.tv_sec - s.tv_sec) * 1000000;

	double	avg = (double)ms / l;
	double	ratio = avg / sec;
	double	sub = avg - sec;

	printf("%d times %8d(usec) : %8lu", l, sec, ms);
	printf("(avg usleep(%d)\t: %8.2lf)\t", sec, avg);
	printf("ratio : %lf, sub : %lf\n", ratio, sub);
}

void	good_night(int l, int s)
{
	struct timeval start;
	struct timeval end;
	int sec = s;
	int j = 0;

	while (j++ < 10)
	{
		int i = 0;
		gettimeofday(&start, NULL);
		while (i++ < l)
		{
			usleep(sec);
		}
		gettimeofday(&end, NULL);
		print_time(l, sec, start, end);
		sec += s;
	}
}

int main(int ac, char **av)
{
	int i = 0;
	if (ac < 3)
	{
		printf("run with [num of sleep] [usec to sleep]\n");
		return (EXIT_FAILURE);
	}
	int lim = atoi(av[ac - 2]);
	int	usec = atoi(av[ac - 1]);

	good_night(lim, usec);

	return (0);
}