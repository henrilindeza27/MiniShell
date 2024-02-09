/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:40:54 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 15:15:18 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	join_char(char **str, char c)
{
	int		i;
	char	*new;

	new = NULL;
	i = 0;
	if (!(*str))
		new = malloc(sizeof(char) * 2);
	else
	{
		new = malloc(sizeof(char) * (ft_strlen(*str) + 2));
		if (!new)
			return ;
		while ((*str)[i])
		{
			new[i] = (*str)[i];
			i++;
		}
	}
	if (!new)
		return ;
	new[i] = c;
	new[i + 1] = '\0';
	free(*str);
	*str = new;
}

void	add_str_to_array(char ***array, char *str)
{
	int		i;
	char	**new_array;

	i = 0;
	if (!*array)
		new_array = (char **)malloc(sizeof(char *) * 2);
	else
	{
		i = -1;
		new_array = (char **)malloc(sizeof(char *) * (len_mtz(*array) + 2));
		if (!new_array)
			return ;
		while ((*array)[++i])
			new_array[i] = ft_strdup((*array)[i]);
	}
	if (!new_array)
		return ;
	new_array[i] = ft_strdup(str);
	new_array[i + 1] = NULL;
	free_matriz(array);
	*array = new_array;
}

void	close_hdpipe(t_token *token, int i, int flag)
{
	if (flag)
	{
		ft_printf("\nSillyShell😿: warning: here-document delimited");
		ft_printf(" by end-of-file (wanted `%s')\n", token->heredoc[i]);
	}
	close(mini()->here_fd[1]);
	close(mini()->here_fd[0]);
}

int	check_heredoc(char *input, int j)
{
	if (input[j] == '<' && input[j + 1] == '<')
		return (1);
	return (0);
}
