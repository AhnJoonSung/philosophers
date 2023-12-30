CC = cc
LFLAGS = -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror -MMD -MP
INCLUDE = .
OBJ_DIR = obj

SRC = \
forks.c \
logger.c \
main.c \
death_monitor.c full_monitor.c\
mutex.c \
philo.c \
simulator.c \
t_data.c t_philo.c \
timer.c \
utils.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
DEP = $(OBJ:%.o=%.d)

NAME = philo

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(LFLAGS) $^ -o $@

$(OBJ_DIR)/%.o : %.c
	$(CC) $(LFLAGS) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

-include $(DEP)

clean :
	rm -f $(OBJ) $(DEP)

fclean : clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
