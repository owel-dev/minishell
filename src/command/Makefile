CC = gcc -g
FLAG = -Wall -Wextra -Werror
check_cmd = ../command/check_cmd.c
builtin = test.o
LIBFT = -L../libft/ -lft

# %.o: %.c
# 	$(CC) -c $< -o $@

all : $(builtin)
	$(CC) $(FLAG) $(check_cmd) $(builtin) $(LIBFT)
