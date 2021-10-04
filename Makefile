NAME = minishell
CC = gcc -lreadline
CFLAGS = -Wall -Wextra -Werror
INCS = -I./libft -I./
LIBFT = -L./libft -lft
RM = rm -f

FILE = 	main\
		print_error

SRCS = $(addprefix ./, $(addsuffix .c, $(FILE)))
OBJS = $(addprefix ./, $(addsuffix .o, $(FILE)))

%.o: %.c
	$(CC) $(INCS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	make -C ./libft
	$(CC) $(LIBFT) $(OBJS) -o $@

clean:
	make -C ./libft clean
	$(RM) $(OBJS)

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re bonus
