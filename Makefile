CC = cc
CFLAGS = 
INCLUDE = .
OBJ_DIR = obj

SRC = \
main.c \
ft_atoi.c logger.c \
simulator.c \
t_data.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

NAME = philosophers

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	
$(OBJ_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re $(NAME)