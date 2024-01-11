/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:03:21 by ssghioua          #+#    #+#             */
/*   Updated: 2023/12/30 16:03:24 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static Stash_list	*Stash;
	Stash_list			*Current_fd_stash;
	char				*line;

	if (fd < 0 || !BUFFER_SIZE || BUFFER_SIZE <= 0)
		return (NULL);
	if (!Stash)
	{
		printf("FD %d NOT EXIST\n", fd);
		Stash = ft_init_stash(fd);
	}
	Current_fd_stash = ft_check_fd_stash(&Stash, fd);
	if (!Current_fd_stash)
		return (NULL);
	Stash = ft_read_file(&Stash, fd);
	if (!Stash)
		return (NULL);
	line = ft_get_line(Current_fd_stash);
	Stash = ft_update_fd_stash(&Stash, fd, ft_strlen(line));
	return (line);
}

Stash_list	*ft_update_fd_stash(Stash_list **Stash, int fd, int line_lengh)
{
	char		*old;
	Stash_list	*Current_fd_stash;

	Current_fd_stash = ft_check_fd_stash(Stash, fd);
	old =  Current_fd_stash -> Fd_stash -> buffer;
	printf("old |%s|\n", old);
	free(Current_fd_stash -> Fd_stash -> buffer);
	Current_fd_stash -> Fd_stash -> buffer = ft_substr(old + line_lengh, 0, ft_strlen(old) - line_lengh);
	printf("(Current -> Fd_stash -> buffer: |%s| \n", Current_fd_stash -> Fd_stash -> buffer);
	return (*Stash);
}

char	*ft_get_line(Stash_list *Stash)
{
	char	*line;
	char	*buffer;

	buffer = Stash -> Fd_stash -> buffer;
	if (ft_strchr(buffer, '\n'))
		line = ft_substr(buffer, 0, ft_strlen(buffer) - ft_strlen(ft_strchr(buffer, '\n')) + 1 );
	else
		line = ft_substr(buffer, 0, ft_strlen(buffer));
	return (line);
}

Stash_list	*ft_read_file(Stash_list **Stash, int fd)
{
	ssize_t		read_bytes;
	char		*temp_buffer;
	char		*stash_buffer;
	Stash_list	*Current_fd_stash;

	Current_fd_stash = ft_check_fd_stash(Stash, fd); 
	temp_buffer = malloc(BUFFER_SIZE);
	if (!temp_buffer)
		return (NULL);
	stash_buffer = Current_fd_stash -> Fd_stash -> buffer;
	read_bytes = 1;
	while (read_bytes && !ft_strchr(temp_buffer, '\n'))
	{
		read_bytes = read(fd, temp_buffer, BUFFER_SIZE);
		printf("read_bytes %zu\n", read_bytes);
		if ((read_bytes == 0 
			&&	*stash_buffer == '\0')
			||	read_bytes == -1)
		{
			Stash_list	*last;
			Stash_list	*Current;
			printf("FREEING...\n");
			Current = *Stash;
			last = *Stash;
			free(temp_buffer);
			if (Current -> Fd_stash -> fd == fd)
			{
				*Stash = Current -> next;
				free(Current -> Fd_stash -> buffer);
				free(Current -> Fd_stash);
				free(Current);
				return (NULL);
			}
			while (Current != NULL)
			{
				if (Current -> Fd_stash -> fd == fd)
				{
					last -> next = Current -> next;
					free(Current -> Fd_stash -> buffer);
					free(Current -> Fd_stash);
					free(Current);
					return (NULL);
				}
				if (Current -> next -> Fd_stash -> fd != fd)
				{
					Current = Current -> next;
					last = Current;
				}
				else
					Current = Current -> next;
			}
			return (NULL);
		}
		temp_buffer[read_bytes] = '\0';
		stash_buffer = ft_strjoin(stash_buffer, temp_buffer);
	}
	Current_fd_stash -> Fd_stash -> buffer = ft_substr(stash_buffer, 0, ft_strlen(stash_buffer));
	return (*Stash);
}

Stash_list	*ft_check_fd_stash(Stash_list **Stash, int fd)
{
	Stash_list	*Current;
	Stash_list	*Updated_Stash;
		
	if (!*Stash)
		return (NULL);
	Current = *Stash;
	Updated_Stash = Current;
	while (Current != NULL)
	{
		if (Current -> Fd_stash -> fd == fd)
			return (Current);
		Current = Current -> next;
	}
	if (!Current)
	{
		printf("FD %d NOT FOUND \n", fd);
		Current = malloc(sizeof(Stash_list));
		if (!Current)
			return (NULL);
		Current -> Fd_stash = malloc(sizeof(Fd_stash));
		if (!Current -> Fd_stash)
		{
			free(Current);
			return (NULL);
		}
		while (Updated_Stash -> next != NULL)
			Updated_Stash = Updated_Stash -> next;
		Current -> Fd_stash -> fd = fd;
		Current -> Fd_stash -> buffer = malloc(1);
		*(Current -> Fd_stash -> buffer) = '\0';
		Current -> next = NULL;
		Updated_Stash -> next = Current;
		printf("FD %d CREATED\n", fd);
		return (Updated_Stash -> next);
	}
	return (NULL);
}

Stash_list	*ft_init_stash(int fd)
{
	Stash_list	*New;
	
	New = malloc(sizeof(Stash_list));
	if (!New)
		return (NULL);
	New -> Fd_stash = malloc(sizeof(Fd_stash));
	if (!New -> Fd_stash)
	{
		free(New);
		return (NULL);
	}
	New -> Fd_stash -> fd = fd;
	New -> Fd_stash -> buffer = malloc(1);
	*(New -> Fd_stash -> buffer) = '\0';
	New -> next = NULL;
	printf("FD %d CREATED\n", fd);
	return  (New);
}
