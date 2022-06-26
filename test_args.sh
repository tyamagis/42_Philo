#! /bin/bash

echo "============="
echo "invalid number of arguments. (argc != 4 && argc != 5)"
echo "============="
read
# No Argument
./philo

# few argument
./philo 1
./philo 1 2
./philo 1 2 3

# many argument
./philo 1 2 3 4 5 6

echo "============="
echo "non-int argument / 4"
echo "============="
read

# non-int argument / 4
#	non-int 1
./philo a 2 3 4
./philo 1 b 3 4
./philo 1 2 c 4
./philo 1 2 3 d

#	non-int 2
./philo a b 3 4
./philo a 2 c 4
./philo a 2 3 d
./philo 1 b c 4
./philo 1 b 3 d
./philo 1 2 c d

#	non-int 3
./philo a b c 4
./philo a b 3 d
./philo a 2 c d
./philo 1 b c d

#	non-int 4
./philo a b c d

echo "============="
echo "non-int argument / 5"
echo "============="
read

# non-int argument / 5
# non-int 1 : 5c1 = 5
./philo a 2 3 4 5
./philo 1 b 3 4 5
./philo 1 2 c 4 5
./philo 1 2 3 d 5
./philo 1 2 3 4 e

# non-int 2 : 5c2 = 10
./philo a b 3 4 5
./philo a 2 c 4 5
./philo a 2 3 d 5
./philo a 2 3 4 e
./philo 1 b c 4 5
./philo 1 b 3 d 5
./philo 1 b 3 4 e
./philo 1 2 c d 5
./philo 1 2 c 4 e
./philo 1 2 3 d e

# non-int 3 : 5c3 = 10
./philo a b c 4 5
./philo a b 3 d 5
./philo a b 3 4 e
./philo a 2 c d 5
./philo a 2 c 4 e
./philo a 2 3 d e
./philo 1 b c d 5
./philo 1 b c 4 e
./philo 1 b 3 d e
./philo 1 2 c d e

# non-int 4 : 5c4 = 5
./philo a b c d 5
./philo a b c 4 e
./philo a b 3 d e
./philo a 2 c d e
./philo 1 b c d e

# non-int 5 : 5c5 = 1
./philo a b c d e

echo "============="
echo "other argument format"
echo "============="
read

# string
./philo "1 2 3 4"
./philo "1 2 3 4 5"

# int smaller than 0
./philo -1 -1 -1 -1

echo "============="
echo "every invalid argument"
echo "============="
read

# each argument
# num_of_philo : no philosopher -> error
./philo 0 1 2 3

# num_of_philo : negative philosopher -> error
./philo -1 1 2 3
./philo -2147483648 1 2 3
./philo -9999999999 1 2 3

# time_to_die : negative
./philo 2 -1 1 2
./philo 2 -2147483648 1 2
./philo 2 -2147483649 1 2

# time_to_eat : negative
./philo 2 2 -1 2
./philo 2 2 -2147483648 2
./philo 2 2 -4294967296 2

# time_to_sleep : negative
./philo 2 2 2 -1
./philo 2 2 2 -2147483648
./philo 2 2 2 -4294967297

# num_must_eat : negative
./philo 2 2 2 2 -1
./philo 2 2 2 2 -2147483648
./philo 2 2 2 2 -4294967298
