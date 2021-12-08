CC = gcc -g
FLAG = -Wall -Wextra -Werror
execute_cmd_classify = ../command/execute_cmd_classify.c
builtin = builtin_cd.o \
builtin_echo.o builtin_env.o builtin_export.o builtin_getenv.o builtin_pwd.o builtin_unset.o test.o
LIBFT = -L../libft/ -lft

# %.o: %.c
# 	$(CC) -c $< -o $@

all : $(builtin)
	$(CC) $(FLAG) $(execute_cmd_classify) $(builtin) $(LIBFT)
