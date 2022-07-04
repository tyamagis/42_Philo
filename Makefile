CFLAGS		= -Wall -Wextra -Werror
LDFLAGS		= -pthread
SNTZ_FLAGS	= -g -fsanitize=thread
NAME		= philo
SRCS		= \
	$(NAME).c \
	philo_utils.c \
	philo_inits.c \
	philo_simulation.c \
	philosophy.c

OBJS		= $(SRCS:.c=.o)

.PHONY: all re clean fclean

$(NAME): $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

sanitize: $(OBJS)
	$(CC) $(CFLAGS) $(SNTZ_FLAGS) $(OBJS) -lasan $(LDFLAGS) -o $(NAME)