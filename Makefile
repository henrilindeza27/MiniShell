NAME_PROJECT = minishell

SRCS = src/main/minishell.c src/builtins/pwd.c src/builtins/env.c src/builtins/echo.c \
		src/builtins/cd.c src/builtins/export.c src/aux/free.c src/exec/exec.c \
		src/builtins/unset.c src/exec/signal.c src/exec/builtins.c src/aux/aux.c \
		src/builtins/shlvl.c src/aux/aux_parsing.c src/parsing/expander.c \
		src/builtins/exit.c  src/exec/cmdpath.c src/aux/aux2.c src/pipex/pipex.c \
		src/pipex/redir.c src/pipex/aux_redir.c src/pipex/heredoc.c src/parsing/join_parser.c \
		src/parsing//linkedlist.c src/parsing/main_parsing.c\
		src/parsing/parser_utils.c src/parsing/split_pipe.c src/aux/aux3.c \
		src/parsing/aux_main_p.c

OBJS = $(SRCS:.c=.o)

#valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes
FLAGS = -Wall -Wextra -Werror -Iinc/ #-fsanitize=address -g 
RLFLAG = -lreadline
LIBFT = libft/libft.a
all: $(NAME_PROJECT)

.PHONY: all clean fclean re

$(NAME_PROJECT): $(OBJS)
	@make -s -C libft/
	@cc $(FLAGS) $(OBJS) $(RLFLAG) $(LIBFT) -o $(NAME_PROJECT)
	@echo  "$(CYAN)Build ($(NAME_PROJECT)): $(GREEN)[Success]$(RESET)"

%.o: %.c
	@cc -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make fclean -s -C libft/

fclean: clean
	@rm -f $(NAME_PROJECT) 
	@echo  "$(YELLOW)Cleaned $(CYAN)$(NAME_PROJECT): $(RED)[Success]$(RESET)"

re: fclean all

rv:
	@make re && valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell
v:
	@make && clear && valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RED	= \033[1;31m
RESET = \033[0m
