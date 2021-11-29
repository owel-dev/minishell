NAME = minishell
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -lreadline -L /usr/local/opt/readline/lib -I/usr/local/opt/readline/include
INCS = -I./src/libft -I./ -I/usr/local/opt/readline/include

# CFLAGS = -Wall -Wextra -Werror -lreadline -L /Users/ulee/Downloads/readline/lib -I/Users/ulee/Downloads/readline/include
# INCS = -I./src/libft -I./ -I/Users/ulee/Downloads/readline/include

LIBFT = -L./src/libft -lft
RM = rm -f

FILE =	main \
		builtin/ft_cd \
		builtin/ft_echo \
		builtin/ft_env \
		builtin/ft_export \
		builtin/ft_getenv \
		builtin/ft_pwd \
		builtin/ft_unset \
		command/is_bin \
		execute/check_cmd \
		execute/execute_cmd \
		exit/free_exit \
		exit/print_error \
		iohandler/pipe_handler \
		iohandler/redir_handler \
		iohandler/set_redir_fd \
		parsing/parsing_bundles \
		parsing/parsing_tokens \
		parsing/parsing_str \
		parsing/set_token \
		utils/list_utils \
		utils/str_utils \
		utils/split_utils \
		utils/fd_utils \
		utils/token_utils \

FILE_T =	test \
			builtin/ft_cd \
			builtin/ft_echo \
			builtin/ft_env \
			builtin/ft_export \
			builtin/ft_getenv \
			builtin/ft_pwd \
			builtin/ft_unset \
			command/is_bin \
			execute/check_cmd \
			execute/execute_cmd \
			exit/free_exit \
			exit/print_error \
			iohandler/pipe_handler \
			iohandler/redir_handler \
			iohandler/set_redir_fd \
			parsing/parsing_bundles \
			parsing/parsing_tokens \
			parsing/parsing_str \
			parsing/set_token \
			utils/list_utils \
			utils/str_utils \
			utils/split_utils \
			utils/fd_utils \
			utils/token_utils \

SRCS = $(addprefix ./src/, $(addsuffix .c, $(FILE)))
OBJS = $(addprefix ./src/, $(addsuffix .o, $(FILE)))

SRCS_T = $(addprefix ./src/, $(addsuffix .c, $(FILE_T)))
OBJS_T = $(addprefix ./src/, $(addsuffix .o, $(FILE_T)))

%.o: %.c
	$(CC) $(INCS) -c $< -o $@

all : $(NAME)
$(NAME) : $(OBJS)
	make -C ./src/libft
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $@
	@echo "\033[31m⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣷⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "\033[33m⠀⠀⠀⠀⠀⠀⠀⣀⣶⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣦⣀⡀⠀⢀⣴⣇⠀⠀⠀⠀"
	@echo "\033[32m⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "\033[34m⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "\033[35m⠀⠀⠀⣴⣿⣿⣿⣿⠛⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀"
	@echo "\033[37m⠀⠀⣾⣿⣿⣿⣿⣿⣶⣿⣯⣭⣬⣉⣽⣿⣿⣄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀"
	@echo "\033[31m⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄"
	@echo "\033[33m⢸⣿⣿⣿⣿⠟⠋⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⣿⣿⣿⣿⡿⠛⠉⠉⠉⠉⠁"
	@echo "\033[32m⠘⠛⠛⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠃⠀⠀⠀⠀⠀"
# https://snskeyboard.com/dotart/

test : $(OBJS_T)
	make -C ./src/libft
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS_T) -o $(NAME)

clean:
	make -C ./src/libft clean
	$(RM) $(OBJS)
	$(RM) ./src/test.o

fclean: clean
	make -C ./src/libft fclean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re bonus
