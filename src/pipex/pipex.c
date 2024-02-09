/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:45:24 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 18:36:57 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirections_and_pipes(t_token *curr, t_token *next)
{
	if (curr->std_in != -1)
	{
		dup2(curr->std_in, STDIN_FILENO);
		close(curr->std_in);
	}
	close(curr->pipe_fd[0]);
	if (curr->std_out != -1)
	{
		dup2(curr->std_out, STDOUT_FILENO);
		close(curr->std_out);
	}
	else if (next)
		dup2(curr->pipe_fd[1], STDOUT_FILENO);
	close(curr->pipe_fd[1]);
}

void	handle_child_process(t_token *curr, t_token *next)
{
	redirections_and_pipes(curr, next);
	if (curr->content)
	{
		if (is_builtins(curr->content[0]))
		{
			run_builtins(mini(), curr);
			free_everything(1, 1, 1);
			exit(0);
		}
		else
			run_cmd_pipe(curr->content);
	}
	close(curr->pipe_fd[0]);
	close(curr->pipe_fd[1]);
	free_everything(1, 1, 1);
	exit(mini()->status);
}

void	handle_parent_process(t_token *curr, t_token *next)
{
	if (next && next->std_in == -1)
		next->std_in = dup(curr->pipe_fd[0]);
	if (curr->std_in != -1)
		close(curr->std_in);
	if (curr->std_out != -1)
		close(curr->std_out);
	close(curr->pipe_fd[0]);
	close(curr->pipe_fd[1]);
}

void	process_command(t_token *curr)
{
	t_token	*next;

	next = NULL;
	if (curr->next)
		next = curr->next;
	if (pipe(curr->pipe_fd) == -1)
		perror("");
	signal(SIGQUIT, ft_sigtemp);
	signal(SIGINT, ft_sigtemp);
	curr->pid = fork();
	if (!curr->pid)
		handle_child_process(curr, next);
	handle_parent_process(curr, next);
}

void	run_multi_cmd(t_token *token)
{
	int		status;
	t_token	*current;

	current = token;
	while (current)
	{
		process_command(current);
		current = current->next;
	}
	current = token;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		current = current->next;
	}
	mini()->status = WEXITSTATUS(status);
}
