/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:19:03 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/09 15:12:26 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_enter(char **str)
{
	int		i;
	int		len;
	char	*temp;

	len = ft_strlen(*str);
	temp = NULL;
	i = 0;
	if ((*str)[len - 1] == '\n')
		temp = (char *)malloc(sizeof(char) * (len));
	else
		temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return ;
	while ((*str)[i] && (*str)[i] != '\n')
	{
		temp[i] = (*str)[i];
		i++;
	}
	temp[i] = '\0';
	free(*str);
	*str = temp;
}

void	expande_var_heredoc(char **input)
{
	int		i;
	char	*temp;

	if (!(*input) || !ft_strchr(*input, '$'))
		return ;
	i = 0;
	temp = NULL;
	remove_enter(input);
	while ((*input)[i])
	{
		if ((*input)[i] == '$')
			ft_expander(&temp, *input, &i);
		else
			join_char(&temp, (*input)[i]);
		i++;
	}
	join_char(&temp, '\n');
	free(*input);
	*input = temp;
}

void	loop_heredoc(t_token *token, int i, char *input)
{
	while (1)
	{
		write(0, "> ", 2);
		input = get_next_line(0);
		if (!input)
		{
			close_hdpipe(token, i, 1);
			free_everything(1, 1, 1);
			exit(-1);
		}
		if (!(ft_strncmp(input, token->heredoc[i],
					ft_strlen(token->heredoc[i]))) && ((ft_strlen(input)
					- 1) == (ft_strlen(token->heredoc[i]))))
		{
			free(input);
			break ;
		}
		if (token->heredoc[i + 1] == NULL)
		{
			expande_var_heredoc(&input);
			write(mini()->here_fd[1], input, ft_strlen(input));
		}
		free(input);
	}
}

int	run_heredoc(t_token *token)
{
	pid_t	pid;
	int		i;

	pipe(mini()->here_fd);
	pid = fork();
	i = 0;
	
	signal(SIGINT, ft_sigtemp);
	signal(SIGQUIT, SIG_IGN);
	if (!pid)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_handler);
		while (token->heredoc && token->heredoc[i])
			loop_heredoc(token, i++, NULL);
		close_hdpipe(token, i, 0);
		free_everything(1, 1, 1);
		exit(0);
	}
	close(mini()->here_fd[1]);
	wait(&pid);
	return (mini()->here_fd[0]);
}
