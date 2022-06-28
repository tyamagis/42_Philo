#include <stdio.h>
#include <sys/time.h>

void	print_time(int i, struct timeval s, struct timeval e)
{
	unsigned long	ms = (e.tv_usec - s.tv_usec);
	ms += (e.tv_sec - s.tv_sec) * 1000000;
	printf("\n%d : %lu\n", i, ms);
}

int main(int ac)
{
	int a = 0;
	int b = ac;
	int i = 0;

	struct timeval start;
	struct timeval end;

	// case 1
	gettimeofday(&start, NULL);
	while (i++ < 1000)
	{
		if (a == 0 && b == 0)
		{
			printf("1");
			continue ;
		}
		else if (a != 0 && b == 1)
		{
			printf("2");
			continue ;
		}
		printf("3");
	}
	gettimeofday(&end, NULL);
	print_time(1, start, end);

	// case 2
	gettimeofday(&start, NULL);
	i = 0;
	while (i++ < 1000)
	{
		if (a == 0)
		{
			if (b == 0)
			{
				printf("1");
				continue ;
			}
		}
		else if (b == 1)
		{
			printf("2");
			continue ;
		}
		printf("3");
	}
	gettimeofday(&end, NULL);
	print_time(2, start, end);

	return (0);
}