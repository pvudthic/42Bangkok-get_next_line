#include "get_next_line.h"

t_list	*ft_clearnode_eof(t_list *lst)
{
	t_list	*temp;

	if (lst->data != NULL)
	{
		free(lst->data);
		lst->data = NULL;
	}
	lst->fd_id = 0;
	if (lst->next != NULL)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
	}
	else if (lst->next == NULL)
	{
		free(lst);
		lst = NULL;
	}
	return (lst);
}

size_t	ft_strlen_nl(char *s, size_t mode)
{
	size_t	count;

	count = 0;
	if (!s)
		return (0);
	if (mode == 1)
	{
		while (s[count] != '\0')
			count++;
	}
	else if (mode == 2)
	{
		if (s[0] == '\0')
			return (0);
		while (s[count] != '\0' && s[count] != '\n')
			count++;
		if (s[count] == '\n')
			count++;
	}
	return (count);
}
void	*ft_update_backup(t_list *c_lst)
{
	char	*temp;
	char	*current;
	size_t	i;
	size_t	count_newmem;


	current = c_lst->data;
	current = current + ft_strlen_nl(current, 2);
	count_newmem = ft_strlen_nl(current, 1);
	temp = (char *)malloc(count_newmem + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (current[i] != '\0')
	{
		temp[i] = current[i];
		i++;
	}
	temp[i] = '\0';
	free(c_lst->data);
	c_lst->data = temp;
	return (temp);
}

int	ft_check_read(char *s)
{
	size_t	i;

	i = 0;
	//Reaching EOF
	if (s[0] == '\0')
		return (0);
	//Finding just the newline
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

t_list	*ft_newnode(int fd, t_list **lst)
{
	t_list	*current;
	t_list	*n_node;

	n_node = (t_list *)malloc(sizeof(t_list));
	if (!n_node)
		return (NULL);
	n_node->data = (char *)malloc(1);
	if (!n_node->data)
	{
		free(n_node);
		return (NULL);
	}
	n_node->data[0] = 0;
	n_node->fd_id = fd;
	n_node->next = NULL;
	if (*lst == NULL)
	{
		*lst = n_node;
		return (*lst);
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = n_node;
	return (current->next);
}
