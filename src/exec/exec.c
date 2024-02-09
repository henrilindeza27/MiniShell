/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:16:31 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 12:20:34 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_error_directory(char **cmds)
{
	struct stat	path_stat;

	if (stat(cmds[0], &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_printf("SillyShell😿: %s: Is a directory\n", cmds[0]);
			mini()->status = 126;
			return (1);
		}
	}
	return (0);
}

void	run_cmd_pipe(char **cmds)
{
	char	*path;
	char	*temp;

	if (check_error_directory(cmds))
		return ;
	temp = ft_getenv("PATH", mini()->env);
	path = get_cmdpath(cmds[0]);
	if (!path || !temp)
	{
		mini()->status = 127;
		if (!temp)
			ft_printf("SillyShell😿: %s: No such file or directory\n", cmds[0]);
		else if (!path)
			ft_printf("%s: command not found\n", cmds[0]);
	}
	else if (execve(path, cmds, mini()->env))
		perror(path);
	free(path);
	free(temp);
}

void	run(t_geral *mini)
{
	if (!mini->token || !check_tokens_redir(mini->token))
		return ;
	mini->status = 0;
	mini->redir_error = 0;
	ft_openredirs(mini->token, 0);
	if (!mini->token->content || mini->redir_error)
		return ;
	if (!mini->token->next && is_builtins(mini->token->content[0]))
		run_one_builtin(mini->token);
	else
		run_multi_cmd(mini->token);
}
