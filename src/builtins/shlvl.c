/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:54:42 by hlindeza          #+#    #+#             */
/*   Updated: 2023/12/14 23:04:33 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*shlvl(void)
{
	int		num;
	char	*num_str;
	char	*var;

	num = ft_atoi(getenv("SHLVL")) + 1;
	num_str = ft_itoa(num);
	var = ft_strjoin("SHLVL=", num_str);
	free(num_str);
	return (var);
}
