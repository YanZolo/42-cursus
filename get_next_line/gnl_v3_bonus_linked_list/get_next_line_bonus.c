/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
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

	if (fd < 0 || !BUFFER_SIZE || BUFFER_SIZE <= 0)
		return (NULL);
	if (!Stash)
	{
		Stash = ft_init_stash(fd);
		Current_fd_stash = Stash;
	}
	else
	{
		Current_fd_stash = ft_check_fd_stash(&Stash, fd);
		if (!Current_fd_stash)
		{
			Stash_list	*Temp;

			while (Stash != NULL)
			{
				Temp = Stash;
				free(Temp -> Fd_stash);
				free(Temp);
				Stash = Stash -> next;
			}
			return (NULL);
		}
	}
	printf("current_fd: %d\n", Current_fd_stash -> Fd_stash -> fd);
	if (Current_fd_stash -> Fd_stash -> fd)
		return ("OK");
	else
		return ("KO");
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
		{
			printf("fd stash found\n");
			break;
		}
		Current = Current -> next;
	}
	if (!Current)
	{
		printf("FD NOT FOUND\n");
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
		Current -> Fd_stash -> buffer = NULL;
		Current -> next = NULL;
		Updated_Stash -> next = Current;
		printf("fd stash created\n");
	}
	return (Current);
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
	New -> Fd_stash -> buffer = NULL;
	New -> next = NULL;
	return  (New);
}



