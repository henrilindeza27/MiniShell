/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 23:25:32 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 16:48:34 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_redir(char *redir)
{
	if (redir[0] == '>' && redir[1] == '\0')
		return (1);
	else if (redir[0] == '<' && redir[1] == '\0')
		return (1);
	else if (redir[0] == '>' && redir[1] == '<')
		return (1);
	else if (redir[0] == '<' && redir[1] == '>')
		return (1);
	else if (redir[0] == '>' && ft_isredir(redir[2]))
		return (1);
	else if (redir[0] == '<' && ft_isredir(redir[2]))
		return (1);
	return (0);
}

int	check_empty_redir(char *redir)
{
	int	i;

	i = 0;
	while (ft_isredir(redir[i]))
		i++;
	if (redir[i] == '\0')
		return (0);
	return (1);
}

void	print_error_msg(char *redir)
{
	ft_printf("SillyShell😿: ");
	ft_printf("syntax error near unexpected token `%s'\n", redir);
	mini()->status = 2;
}

int	check_tokens_redir(t_token *node)
{
	t_token	*current;
	int		i;

	current = node;
	while (current)
	{
		if (current->redir)
		{
			i = 0;
			while (current->redir[i])
			{
				if (check_redir(current->redir[i])
					|| !check_empty_redir(current->redir[i]))
				{
					mini()->status = 2;
					print_error_msg(current->redir[i]);
					return (0);
				}
				i++;
			}
		}
		current = current->next;
	}
	return (1);
}
