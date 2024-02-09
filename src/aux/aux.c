/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:10:47 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 15:28:57 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	len_mtz(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	check_echo_flags(char *arg, t_token *token)
{
	size_t	i;

	i = 0;
	if (ft_strlen(arg) == 1)
		return (0);
	while (arg[i] && arg[0] == '-' && arg[i + 1] == 'n')
		i++;
	if (ft_strlen(arg) == ++i)
	{
		token->builtin_flag = 1;
		return (1);
	}
	return (0);
}

int	count_dollars(char *input, int *i)
{
	int	dollar_count;

	dollar_count = 1;
	while (input[(*i)] == '$')
	{
		dollar_count++;
		(*i)++;
	}
	return (dollar_count);
}
