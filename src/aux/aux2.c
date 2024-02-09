/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:25:54 by hlindeza          #+#    #+#             */
/*   Updated: 2024/01/22 20:16:13 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_isredir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_valid_char(char input)
{
	if (((ft_isdigit(input) || (!ft_isalpha(input))) && (input != '_'
				&& input != '$' && input != '?')))
		return (0);
	return (1);
}

void	add_dollars(char **str, int dollar_count)
{
	while (dollar_count / 2 > 0)
	{
		join_char(str, '$');
		dollar_count--;
	}
}
