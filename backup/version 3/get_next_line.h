#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

//These should delete
//# define BUFFER_SIZE 7
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
/////////////////////

typedef struct s_buflist
{
	char				*buffer;
	struct s_buflist	*next;
}					t_buflist;

typedef struct s_fdlist
{
	int				fd_id;
	t_buflist		*read_data;
	struct s_fdlist	*next;
}					t_fdlist;

int			end_of_line(char *content);
t_fdlist	*clean_fd_list(t_fdlist *fd_list, t_fdlist *c_fd);
void		ft_clearnode(t_buflist *current, t_fdlist *current_fd);
char		*ft_strchr(const char *s, int c);
t_fdlist	*ft_addfd_back(t_fdlist **lst, int fd);
t_buflist	*ft_newnode(void);
char		*get_next_line(int fd);

#endif