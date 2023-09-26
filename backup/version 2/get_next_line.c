#include "get_next_line.h"

void	ft_extract_backup(t_list *lst, char *read_line)
{
	size_t	i;
	size_t	len_backup;
	char	*temp;

	i = 0;
	if (!read_line || !lst || *read_line == '\0')
	{
		lst->backup = lst->read_line;
		return ;
	}
	while (read_line[i] != '\n' && read_line[i] != '\0')
		i++;
	i = i + (read_line[i] == '\n');
	len_backup = ft_lstclear_strlen(read_line, 1, &lst) - i;
	temp = (char *)ft_calloc(i + 1, 1);
	if (!temp)
	{
		free(read_line);
		lst->read_line = NULL;
		return ;
	}
	lst->backup = (char *)ft_calloc(len_backup + 1, 1);
	if (!lst->backup)
	{
		free(temp);
		return ;
	}
	ft_memmove(temp, read_line, i);
	ft_memmove(lst->backup, read_line + i, len_backup);
	free(read_line);
	read_line = NULL;
	lst->read_line = temp;
}

char	*ft_addcontent(char	*read_line, char *buf, t_list *lst)
{
	char	*temp;
	int		len_read_line;
	int		len_buf;

	len_read_line = ft_lstclear_strlen(read_line, 1, &lst);
	len_buf = ft_lstclear_strlen(buf, 1, &lst);
	temp = (char *)ft_calloc((len_read_line + len_buf + 1), 1);
	if (!temp)
		return (NULL);
	ft_memmove(temp, read_line, len_read_line);
	ft_memmove(temp + len_read_line, buf, len_buf);
	free(read_line);
	read_line = NULL;
	return (temp);
}

void	*ft_readline(t_list *lst, int fd)
{
	char	*buf;
	int		rd_buf;

	rd_buf = 1;
	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (rd_buf > 0)
	{
		rd_buf = read(fd, buf, BUFFER_SIZE);
		if (rd_buf == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rd_buf] = 0;
		if (*buf == '\0')
			break ;
		lst->read_line = ft_addcontent(lst->read_line, buf, lst);
		if (ft_strchr(buf, '\n') != NULL && ft_strchr(buf, '\0') != NULL)
			break ;
	}
	ft_extract_backup(lst, lst->read_line);
	free(buf);
	return (lst);
}

t_list	*ft_backup_multifd(t_list *lst, int fd)
{
	t_list	*current;

	current = lst;
	while (1)
	{
		if (!current)
		{
			current = ft_lstadd_back(&lst, fd);
			if (!current)
				return (NULL);
			break ;
		}
		if (current->fd_id == fd)
			break ;
		current = current->next;
	}
	current->read_line = current->backup;
	ft_readline(current, fd);
	return (current);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	t_list			*current;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (lst != NULL)
			ft_lstclear_strlen("", 0, &lst);
		return (NULL);
	}
	if (!lst)
	{
		lst = ft_lstadd_back(&lst, fd);
		if (!lst)
			return (NULL);
	}
	if (lst->read_line != NULL)
		lst->read_line = NULL;
	current = ft_backup_multifd(lst, fd);
	if (!current)
		return (NULL);
	if (current->read_line == NULL || *current->read_line == '\0')
	{
		ft_lstclear_strlen("", 0, &lst);
		return (NULL);
	}
	return (current->read_line);
}