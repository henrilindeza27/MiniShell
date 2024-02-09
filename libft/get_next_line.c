/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:23:21 by hlindeza          #+#    #+#             */
/*   Updated: 2023/12/20 15:22:45 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[BUFFER_SIZE + 1];

	line = NULL;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		ft_clean_buffer(buffer);
		return (NULL);
	}
	while (*buffer != 0 || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		line = ftgnl_strjoin(line, buffer);
		if (ft_check_buffer(buffer))
			break ;
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int i = 1;
// 	fd = open("file", O_RDONLY);
// 	while ((line = get_next_line(fd)) > 0)
// 	{
// 		ft_printf("Line %d:\n", i++);
// 		ft_printf("-> %s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }