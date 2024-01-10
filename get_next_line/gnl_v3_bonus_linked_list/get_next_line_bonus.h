/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:03:11 by ssghioua          #+#    #+#             */
/*   Updated: 2023/12/30 16:03:14 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 55 
# endif // !BUFFER_SIZE

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct Fd_stash {
	int		fd;
	char	*buffer;
} Fd_stash;

typedef struct Base_stash {
	Fd_stash			*Fd_stash;
	struct Base_stash	*next;
} Stash_list;

char		*get_next_line(int fd);
<<<<<<< HEAD
Stash_list	*ft_init_stash(Stash_list **Stash, int fd);
Stash_list	*ft_get_file_stash(Stash_list **Stash, int fd);
=======
Stash_list	*ft_init_stash(int fd);
Stash_list	*ft_check_fd_stash(Stash_list **Stash, int fd);
<<<<<<< HEAD
>>>>>>> b7d415a (gnl_bonus: work on the ft_read_file branch. When initializing stash fd, assign an empty string to buffer fd. Todo: in ft_read_file function check that the linked lists have not lost a link when a list is freed.)
=======
>>>>>>> b7d415a (gnl_bonus: work on the ft_read_file branch. When initializing stash fd, assign an empty string to buffer fd. Todo: in ft_read_file function check that the linked lists have not lost a link when a list is freed.)
Stash_list	*ft_read_file(Stash_list **Stash, int fd);
size_t		ft_strlen(char *s);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*ft_strchr(char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlcpy(char *dst, char *src, size_t size);
size_t		ft_strlcat(char *dst, char *src, size_t size);
<<<<<<< HEAD
<<<<<<< HEAD
char		*ft_get_line(Stash_list *Stash);
Stash_list	*ft_update_file_stash(Stash_list **Stash, int fd, int len);
int			ft_release_file_stash(Stash_list **Stash, int fd);
Stash_list	*ft_create_file_stash(Stash_list **Stash, int fd);
=======
>>>>>>> b7d415a (gnl_bonus: work on the ft_read_file branch. When initializing stash fd, assign an empty string to buffer fd. Todo: in ft_read_file function check that the linked lists have not lost a link when a list is freed.)
=======
>>>>>>> b7d415a (gnl_bonus: work on the ft_read_file branch. When initializing stash fd, assign an empty string to buffer fd. Todo: in ft_read_file function check that the linked lists have not lost a link when a list is freed.)

#endif // !GET_NEXT_LINE_H
