/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_main_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:25:32 by rfontes-          #+#    #+#             */
/*   Updated: 2024/02/08 17:23:30 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*str_addchar(char *str, char c)
{
	char	*newstr;
	char	*newchar;

	newchar = malloc(2);
	newchar[0] = c;
	newchar[1] = '\0';
	newstr = ft_strjoin_parser(str, newchar);
	return (newstr);
}

char	**addstring(char *str, char **matrix)
{
	char	**new;
	int		i;

	i = 0;
	if (!str || !str[0])
		return (NULL);
	if (!matrix)
		new = malloc(2 * sizeof(char *));
	else
	{
		while (matrix[i])
			i++;
		new = malloc(sizeof(char *) * (i + 2));
		i = -1;
		while (matrix[++i])
			new[i] = ft_strdup(matrix[i]);
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free_matriz(&matrix);
	return (new);
}

char	*handle_q(char *str, char *input, char c, int *i)
{
	if (c && c == '\'' || c == '\"')
	{
		while (input[++(*i)] != c)
		{
			if (input[(*i)] && input[(*i)] == '$' && input[(*i) + 1] != '>'
				&& c == '\"')
				ft_expander(&str, input, i);
			else
				str = str_addchar(str, input[(*i)]);
		}
		(*i)++;
	}
	return (str);
}

char	*handle_redir_p(char *str, char *input, int *i)
{
	int	j;

	j = *i;
	while (input[(*i)] && *i < ft_strlen(input) && (input[(*i)] == '<'
			|| input[(*i)] == '>'))
		str = str_addchar(str, input[(*i)++]);
	*i = skip_spaces_p(input, *i);
	while (input[(*i)] && input[(*i)] != ' ' && input[(*i)] != '\t'
		&& input[(*i)] != '>' && input[(*i)] != '<')
	{
		if (input[(*i)] && input[(*i)] == '$' && input[(*i) + 1] != '>'
			&& !check_heredoc(input, j))
		{
			ft_expander(&str, input, i);
			(*i)++;
		}
		else if (input[(*i)] && (input[(*i)] == '\'' || input[(*i)] == '\"'))
			str = handle_q(str, input, input[(*i)], i);
		else
			str = str_addchar(str, input[(*i)++]);
	}
	return (str);
}

char	*handle_content(char *str, char *input, int *i)
{
	while (input[(*i)] && input[(*i)] != ' ' && input[(*i)] != '\t'
		&& input[(*i)] != '>' && input[(*i)] != '<')
	{
		if (input[(*i)] && input[(*i)] == '$' && input[(*i) + 1] != '>')
		{
			ft_expander(&str, input, i);
			(*i)++;
		}
		else if (input[(*i)] && (input[(*i)] == '\'' || input[(*i)] == '\"'))
			str = handle_q(str, input, input[(*i)], i);
		else
			str = str_addchar(str, input[(*i)++]);
	}
	return (str);
}
