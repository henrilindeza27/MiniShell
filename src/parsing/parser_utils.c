/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:25:32 by rfontes-          #+#    #+#             */
/*   Updated: 2024/02/07 15:33:27 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_spaces_p(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int	unclosedq(char *str)
{
	int		i;
	char	q;

	q = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !q)
			q = str[i];
		else if (str[i] == q)
			q = 0;
		i++;
	}
	if (q)
		return (1);
	return (0);
}

int	rules(char *input)
{
	int	len;
	int	i;

	if (!input[0])
		return (1);
	len = (int)ft_strlen(input);
	i = skip_spaces_p(input, 0);
	if (input[i] == '|')
		return (1);
	while (input[i] && i < len)
	{
		if (input[i] == '|')
		{
			i++;
			i = skip_spaces_p(input, i);
			if (i == len || input[i] == '|')
				return (1);
		}
		else
			i++;
	}
	return (0);
}
