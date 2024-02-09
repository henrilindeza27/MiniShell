/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:25:59 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 14:50:29 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_var(char ***env, int i)
{
	free((*env)[i]);
	(*env)[i] = ft_strdup("0000");
}

void	rebuild_env(char ***env, char **new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (ft_isdigit((*env)[i][0]))
			i++;
		else
			new[j++] = ft_strdup((*env)[i++]);
	}
	new[j] = NULL;
	free_matriz(env);
	*env = new;
}

void	ft_unset(char ***env, char *content)
{
	char	**new;
	int		i;

	i = check_in_env(content, *env);
	if (i == -1)
		return ;
	new = (char **)malloc(sizeof(char *) * (len_mtz(*env)));
	if (!new)
		return ;
	if (i != -1)
		remove_var(env, i);
	rebuild_env(env, new);
}

void	ft_run_unset(char **content)
{
	int	i;

	i = 1;
	while (content[i])
		ft_unset(&mini()->env, content[i++]);
}
