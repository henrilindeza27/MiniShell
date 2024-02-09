/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:10:20 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 15:29:00 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define RESET "\x1b[0m"

typedef struct s_token
{
	char			**content;
	char			**redir;
	char			**heredoc;

	pid_t			pid;
	int				pipe_fd[2];

	int				builtin_flag;

	int				std_in;
	int				std_out;

	struct s_token	*next;
}					t_token;

typedef struct s_geral
{
	int				status;
	int				loop;
	int				here_fd[2];
	int				redir_error;

	char			**env;
	t_token			*token;

}					t_geral;

/*                    src/main/                    */

t_geral				*mini(void);
/*                   src/builtins/                 */

char				*ft_getenv(char *var, char **env);
void				ft_cd(char *dirpath);
void				ft_echo(char **str, t_token *token);
char				**save_env(char **env);

void				ft_print_env(char **env);
int					get_len_env(char *content);
void				ft_export(char ***envp, char *content);
void				ft_run_export(char **content);
void				ft_pwd(void);
char				*shlvl(void);
void				ft_run_unset(char **content);
void				ft_exit(char **content);

/*                     src/aux/                   */

int					count_dollars(char *input, int *i);
void				skip_spaces(char *input, int *i, int value);
int					check_echo_flags(char *arg, t_token *token);
int					len_mtz(char **env);
void				free_matriz(char ***mrtz);
void				free_linked_list(t_token *token);
void				free_everything(int env, int fds, int token);
int					ft_isspace(char c);
int					ft_isredir(char c);
int					ft_isquote(char c);
int					is_valid_char(char input);
void				add_dollars(char **str, int dollar_count);
int					check_in_env(char *content, char **env);
int					check_heredoc(char *input, int j);

/*                     src/exec/                   */

void				run_builtins(t_geral *mini, t_token *token);
int					is_builtins(char *input);
char				*get_cmdpath(char *cmd);
void				run(t_geral *mini);
void				ft_sigint(int sig);
void				ft_sigtemp(int sig);
void				ft_signal(void);

void				run_cmd_pipe(char **cmds);

void				ft_expander(char **str, char *input, int *i);
void				join_char(char **str, char c);
void				add_str_to_array(char ***array, char *str);

/*                     src/pipex/                   */

void				run_multi_cmd(t_token *token);
void				ft_openredirs(t_token *tokens, int i);
void				run_one_builtin(t_token *token);
int					check_tokens_redir(t_token *node);
int					run_heredoc(t_token *token);
void				handle_heredoc(t_token *token);
void				remove_enter(char **str);
void				ft_handler(int sig);
void				ft_sigtemp(int sig);
void				close_hdpipe(t_token *token, int i, int flag);
void				expande_var_heredoc(char **input);

/*                      parser                      */

char				*ft_strjoin_parser(char *s1, char *s2);
t_token				*new_token(void);
t_token				*last_token(t_token *token);
void				tokenadd_back(t_token **token, t_token *new);
void				tokenadd_front(t_token **token, t_token *new);
char				*handle_q(char *str, char *input, char c, int *i);
char				*str_addchar(char *str, char c);
char				**addstring(char *str, char **matrix);
char				*handle_redir_p(char *str, char *input, int *i);
char				*handle_content(char *str, char *input, int *i);
void				handle_node(t_token *node, char *input, int i);
t_token				*parse(char *input, int i);
int					skip_spaces_p(char *str, int i);
int					unclosedq(char *str);
int					rules(char *input);
char				*r_str(char *input, int *i);
char				**split_pipes(char *input);

#endif
