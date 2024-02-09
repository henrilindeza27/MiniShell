/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:25:32 by rfontes-          #+#    #+#             */
/*   Updated: 2024/02/07 15:05:30 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*new_token(void)
{
	t_token	*newnode;

	newnode = (t_token *)malloc(sizeof(t_token));
	if (!newnode)
		return (NULL);
	newnode->content = NULL;
	newnode->redir = NULL;
	newnode->heredoc = NULL;
	newnode->std_in = -1;
	newnode->std_out = -1;
	newnode->builtin_flag = 0;
	newnode->next = NULL;
	return (newnode);
}

t_token	*last_token(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
	{
		token = token->next;
	}
	return (token);
}

void	tokenadd_back(t_token **token, t_token *new)
{
	t_token	*a;

	if (!*token)
		*token = new;
	else
	{
		a = *token;
		a = last_token(*token);
		a->next = new;
	}
}

void	tokenadd_front(t_token **token, t_token *new)
{
	if (!token || !new)
		return ;
	new->next = *token;
	*token = new;
}
