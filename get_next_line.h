/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvudthic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:33:43 by pvudthic          #+#    #+#             */
/*   Updated: 2023/10/03 15:50:32 by pvudthic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_list
{
	char			*data;
	int				fd_id;
	struct s_list	*next;
}					t_list;

t_list	*ft_clearnode_eof(t_list *lst);
t_list	*ft_update_backup(t_list *c_lst, char *new_line);
size_t	ft_strlen_nl(char *s, size_t mode);
char	*ft_checkread_malloc_t(char *old_str, char *buf, int mode);
t_list	*ft_newnode(int fd, t_list **lst);
char	*get_next_line(int fd);

#endif
