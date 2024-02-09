/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:13:02 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/06 15:54:05 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	run_builtins(t_geral *mini, t_token *token)
{
	if (!ft_strcmp("pwd", token->content[0]))
		ft_pwd();
	else if (!ft_strcmp("env", token->content[0]))
		ft_print_env(mini->env);
	else if (!ft_strcmp("echo", token->content[0]))
		ft_echo(token->content, token);
	else if (!ft_strcmp("cd", token->content[0]))
		ft_cd(token->content[1]);
	else if (!ft_strcmp("export", token->content[0]))
		ft_run_export(token->content);
	else if (!ft_strcmp("unset", token->content[0]))
		ft_run_unset(token->content);
	else if (!ft_strcmp("exit", token->content[0]))
		ft_exit(token->content);
}

int	is_builtins(char *input)
{
	int	i;

	i = 0;
	if (!ft_strcmp("pwd", input) || !ft_strcmp("env", input))
		i = 1;
	else if (!ft_strcmp("echo", input) || !ft_strcmp("cd", input))
		i = 1;
	else if (!ft_strcmp("export", input) || !ft_strcmp("unset", input))
		i = 1;
	else if (!ft_strcmp("exit", input))
		i = 1;
	return (i);
}

void	handle_redirections(t_token *token, int *in, int *out)
{
	if (token->std_in != -1)
	{
		*in = dup(STDIN_FILENO);
		dup2(token->std_in, STDIN_FILENO);
		close(token->std_in);
	}
	if (token->std_out != -1)
	{
		*out = dup(STDOUT_FILENO);
		dup2(token->std_out, STDOUT_FILENO);
		close(token->std_out);
	}
}

void	restore_io(int in, int out)
{
	if (in != -1)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != -1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

void	run_one_builtin(t_token *token)
{
	int	in;
	int	out;

	in = -1;
	out = -1;
	handle_redirections(token, &in, &out);
	run_builtins(mini(), token);
	restore_io(in, out);
}
