/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:25:32 by rfontes-          #+#    #+#             */
/*   Updated: 2024/02/07 15:46:27 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error_msg(char *input)
{
	if (rules(input))
	{
		ft_printf("Sillyshell😿: syntax error near unexpected token `|'\n");
		mini()->status = 2;
		return (1);
	}
	else if (unclosedq(input))
	{
		ft_printf("Sillyshell😿: can't handle unclosed quotes \n");
		mini()->status = 2;
		return (1);
	}
	return (0);
}

void	handle_node(t_token *node, char *input, int i)
{
	char	*str;

	while (input[i])
	{
		str = NULL;
		i = skip_spaces_p(input, i);
		if (input[i] && (input[i] == '<' || input[i] == '>'))
		{
			str = handle_redir_p(str, input, &i);
			if (str)
			{
				node->redir = addstring(str, node->redir);
				free(str);
			}
		}
		else if (input[i])
		{
			str = handle_content(str, input, &i);
			if (str)
			{
				node->content = addstring(str, node->content);
				free(str);
			}
		}
	}
}

t_token	*parse(char *input, int i)
{
	t_token	*cur;
	t_token	*head;
	char	**nodes;

	if (error_msg(input))
		return (NULL);
	nodes = split_pipes(input);
	if (!nodes)
		return (NULL);
	cur = new_token();
	i = 0;
	while (nodes[++i])
		tokenadd_back(&cur, new_token());
	head = cur;
	i = -1;
	while (cur != NULL)
	{
		handle_node(cur, nodes[++i], 0);
		cur = cur->next;
	}
	free_matriz(&nodes);
	return (head);
}
