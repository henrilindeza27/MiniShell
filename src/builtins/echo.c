/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:33:02 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 17:10:06 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(char **str, t_token *token)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (!str)
	{
		printf("\n");
		return ;
	}
	while (str[i])
	{
		if (!flag && check_echo_flags(str[i], token))
			i++;
		else
		{
			flag = 1;
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
			i++;
		}
	}
	if (!mini()->token->builtin_flag)
		printf("\n");
}
