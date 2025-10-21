/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/10/21 13:07:28 by slambert          #+#    #+#             */
/*   Updated: 2025/10/21 13:07:28 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include "get_next_line_utils.c"
#include <fcntl.h>
#include <stdio.h>


void	ft_strjoin_and_free(char **stash, char **read_buffer);
char	*return_handler(char **stash);
void	free_read_buffer_and_stash(char **read_buffer, char **stash);
char	*extract_stuff_after_newline(char **stash, char *newline_pointer);

char	*get_next_line(int fd)
{
	static char *stash;
	char *read_buffer;
	int read_bytes;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	read_buffer = malloc(BUFFER_SIZE + 1);
	while (1)
	{
		read_bytes = read(fd, read_buffer, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free_read_buffer_and_stash(&read_buffer, &stash);
			stash = NULL;
			return (NULL);
		}
		read_buffer[read_bytes] = '\0';
		if (read_bytes == 0)
			break ;
		ft_strjoin_and_free(&stash, &read_buffer);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	free(read_buffer);
	return (return_handler(&stash));
}

void	free_read_buffer_and_stash(char **read_buffer, char **stash)
{
	free(*read_buffer);
	free(*stash);
}

void	ft_strjoin_and_free(char **stash, char **read_buffer)
{
	char *temp;

	temp = ft_strjoin(*stash, *read_buffer);
	free(*stash);
	*stash = temp;
}

char	*return_handler(char **stash)
{
	char *newline_pointer;
	char *line_to_ret;
	char *temp;

	if (!(*stash) || (*stash)[0] == '\0')
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	newline_pointer = ft_strchr(*stash, '\n');
	if (newline_pointer)
	{
		line_to_ret = ft_substr(*stash, 0, (newline_pointer - *stash) + 1);
		temp = extract_stuff_after_newline(stash, newline_pointer);
		free(*stash);
		*stash = temp;
		return (line_to_ret);
	}
	else
	{
		line_to_ret = *stash;
		*stash = NULL;
		return (line_to_ret);
	}
}

char	*extract_stuff_after_newline(char **stash, char *newline_pointer)
{
	return (ft_substr(*stash, (newline_pointer - *stash) + 1, ft_strlen(*stash)
			- ((newline_pointer - *stash) + 1)));
}
/* 
int	main(void)
{
	int i = 0;
	int fd;
	char *p;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		p = get_next_line(fd);
		if (!p)
			break ;
		printf("Line %d: %s\n", i, p);
		free(p);
		i++;
	}
} */