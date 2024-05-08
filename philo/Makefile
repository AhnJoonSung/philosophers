CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD

NAME = philo

SRCS_DIR = srcs
OBJS_DIR = objs
INCLUDES = -I./includes

SRCS := $(shell find $(SRCS_DIR) -type f -name '*.c')
OBJS := $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))
DEP := $(OBJS:%.o=%.d)

#-----------------------------------rules--------------------------------------#
all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $^ -o $@

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(@D);
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

-include $(DEP)

clean :
	rm -f $(OBJS) $(DEP)

fclean : clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
