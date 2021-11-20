CC = gcc -g
FLAG = -Wall -Wextra -Werror
check_cmd = ../command/check_cmd.c
builtin = ft_cd.o \
ft_echo.o ft_env.o ft_export.o ft_getenv.o ft_pwd.o ft_unset.o test.o
LIBFT = -L../libft/ -lft

# %.o: %.c
# 	$(CC) -c $< -o $@

all : $(builtin)
	$(CC) $(FLAG) $(check_cmd) $(builtin) $(LIBFT)
