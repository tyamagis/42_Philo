CFLAGS		= -Wall -Wextra -Werror
LDFLAGS		= -pthread
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
