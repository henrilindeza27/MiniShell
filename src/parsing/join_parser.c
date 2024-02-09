/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:25:32 by rfontes-          #+#    #+#             */
/*   Updated: 2024/02/07 15:04:53 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*handle_null_strings(char *s1, char *s2)
{
	char	*newstr;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
	{
		newstr = ft_strdup(s1);
		free(s1);
		return (newstr);
	}
	if (!s1 && s2)
	{
		newstr = ft_strdup(s2);
		free(s2);
		return (newstr);
	}
	return (NULL);
}

char	*allocate_new_string(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*newstr;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	newstr = (char *)malloc(len1 + len2 + 1);
	if (!newstr)
		return (NULL);
	return (newstr);
}

void	copy_strings(char *newstr, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (s1[++i])
		newstr[i] = s1[i];
	while (s2[j])
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
}

char	*ft_strjoin_parser(char *s1, char *s2)
{
	char	*newstr;

	newstr = handle_null_strings(s1, s2);
	if (newstr)
		return (newstr);
	newstr = allocate_new_string(s1, s2);
	if (!newstr)
		return (NULL);
	copy_strings(newstr, s1, s2);
	free(s1);
	free(s2);
	return (newstr);
}
