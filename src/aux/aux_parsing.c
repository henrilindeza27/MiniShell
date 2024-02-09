/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:42:38 by hlindeza          #+#    #+#             */
/*   Updated: 2024/01/24 04:15:54 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	skip_spaces(char *input, int *i, int value)
{
	int	x;

	x = value;
	while (input[x] && (input[x] == ' ' || input[x] == '\t'))
		x++;
	*i = x;
}

int	get_len_env(char *content)
{
	int	i;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	return (i + 1);
}

int	check_in_env(char *content, char **env)
{
	int		size;
	int		i;
	char	*tmp;

	i = -1;
	size = get_len_env(content);
	tmp = ft_strjoin(content, "=");
	while (env[++i])
	{
		if (!ft_strncmp(env[i], tmp, size))
		{
			free(tmp);
			return (i);
		}
	}
	free(tmp);
	return (-1);
}
