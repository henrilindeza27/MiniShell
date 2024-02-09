/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:45:27 by hlindeza          #+#    #+#             */
/*   Updated: 2024/01/24 04:15:01 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_matriz(char ***mrtz)
{
	int	i;

	i = 0;
	if (*mrtz)
	{
		while ((*mrtz)[i])
		{
			free((*mrtz)[i]);
			i++;
		}
	}
	free(*mrtz);
	*mrtz = NULL;
}

void	free_linked_list(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		if (token->content)
			free_matriz(&token->content);
		if (token->redir)
			free_matriz(&token->redir);
		if (token->heredoc)
			free_matriz(&token->heredoc);
		if (token->std_in != -1)
			close(token->std_in);
		if (token->std_out != -1)
			close(token->std_out);
		free(token);
		token = next;
	}
}

void	free_everything(int env, int fds, int token)
{
	if (env)
		free_matriz(&mini()->env);
	if (fds)
	{
		close(2);
		close(1);
		close(0);
	}
	if (token)
		free_linked_list(mini()->token);
}
