/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:25:32 by rfontes-          #+#    #+#             */
/*   Updated: 2024/02/07 15:33:31 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*r_str(char *input, int *i)
{
	char	*new;
	char	q;

	new = NULL;
	q = 0;
	while (input[*i] && ((input[*i] != '|' || q)))
	{
		if (ft_isquote(input[*i]) && !q)
		{
			q = input[(*i)];
			join_char(&new, input[(*i)]);
		}
		else if (ft_isquote(input[*i]) && input[*i] == q)
		{
			q = 0;
			join_char(&new, input[(*i)]);
		}
		else
			join_char(&new, input[(*i)]);
		(*i)++;
	}
	return (new);
}

char	**split_pipes(char *input)
{
	char	**content;
	char	*str;
	int		i;

	i = 0;
	content = NULL;
	str = NULL;
	while (i < ft_strlen(input) && input[i])
	{
		if (input[i] != '|')
		{
			str = r_str(input, &i);
			add_str_to_array(&content, str);
			free(str);
			str = NULL;
		}
		i++;
	}
	return (content);
}
