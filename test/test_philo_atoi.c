#include <stdio.h>

int main(void)
{
	printf("-2, %d\n", philo_atoi("-2"));
	printf("-1, %d\n", philo_atoi("-1"));
	printf("0, %d\n", philo_atoi("0"));
	printf("1, %d\n", philo_atoi("1"));
	printf("2, %d\n", philo_atoi("2"));
	printf("2147483647, %d\n", philo_atoi("2147483647"));
	printf("2147483648, %d\n", philo_atoi("2147483648"));
	printf("2147483649, %d\n", philo_atoi("2147483649"));
	printf("-2147483648, %d\n", philo_atoi("-2147483648"));
	printf("-2147483649, %d\n", philo_atoi("-2147483649"));
	printf("-2147483650, %d\n", philo_atoi("-2147483650"));
	printf("-2147483651, %d\n", philo_atoi("-2147483651"));
	printf("4294967295, %d\n", philo_atoi("4294967295"));
	printf("4294967296, %d\n", philo_atoi("4294967296"));
	printf("4294967297, %d\n", philo_atoi("4294967297"));
	printf("-4294967295, %d\n", philo_atoi("-4294967295"));
	printf("-4294967296, %d\n", philo_atoi("-4294967296"));
	printf("-4294967297, %d\n", philo_atoi("-4294967297"));
	return (0);
}