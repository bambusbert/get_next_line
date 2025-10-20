/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:07:06 by slambert          #+#    #+#             */
/*   Updated: 2025/10/20 14:07:06 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"
#include <fcntl.h>
#include <stdio.h>

char	*shift_to_next_line(char *buf);

char	*get_next_line(int fd)
{
	static char *buf;
	static char *line;
	char *ret;

	if (!buf)
		buf = malloc(BUFFER_SIZE + 1);
	// protect against malloc fail
	read(fd, buf, BUFFER_SIZE);
	if (ft_strchr(buf, '\n'))
	{
		// full line already in buffer, no need to read
		ret = ft_substr(buf, 0, ft_strchri(buf, '\n'));
		buf = shift_to_next_line(buf);
		return (ret);
	}
	else
	{
		line = ft_strjoin(buf, "");
		while (!is_line_done(line))
		{
			read(fd, buf, BUFFER_SIZE);
			line = ft_strjoin(line, buf);
		}
		//das was nach \n kommt in den buffer, das vor \n returnen
		return line;
	}
	return (buf);
}

int	is_line_done(char *buf)
{
	if (ft_strchri(buf, '\n'))
		return (1);
	return (0);
}

char	*shift_to_next_line(char *buf)
{
	if (ft_strchr(buf, '\n'))
		return (ft_strdup(ft_strchr(buf, '\n') + 1));
	return (NULL);
}

int	main(void)
{
	int i = 0;
	int fd;
	char *p;
	char str[] = "1234";

	//printf("line done: %d\n", is_line_done(str));

	fd = open("test.txt", O_RDONLY);
	while (i < 6)
	{
		p = get_next_line(fd);
		printf("Line %d: %s\n", i, p);
		i++;
	}
}