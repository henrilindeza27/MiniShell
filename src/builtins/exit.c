/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:24:20 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 17:57:31 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_mega_error(int flag)
{
	if (!flag)
		ft_putendl_fd("SillyShell😿: exit: too many arguments", 2);
	else
		ft_putendl_fd("SillyShell😿: exit: numeric argument required", 2);
}

int	check_all_number(char *content)
{
	int	i;

	i = 0;
	if (content[0] == '-' || content[0] == '+')
	{
		if (content[1] == '-' && content[2] == '\0')
			return (1);
		i++;
	}
	if (!ft_isdigit(content[i]))
		return (0);
	while (content[i])
	{
		if (!ft_isdigit(content[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **content)
{
	int	len;

	len = len_mtz(content);
	ft_printf("exit\n");
	if (len > 2)
	{
		print_mega_error(0);
		mini()->status = 1;
		return ;
	}
	else
	{
		mini()->loop = 0;
		if (len == 2)
		{
			if (!check_all_number(content[1]))
			{
				print_mega_error(1);
				mini()->status = 2;
				return ;
			}
			else
				mini()->status = ft_atoi(content[1]);
		}
	}
}
