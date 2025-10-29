#include "ft_list.h"

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list *current;
	t_list *prev;
	t_list *temp;

	if (!begin_list || !*begin_list)
		return ;

	current = *begin_list;
	prev = NULL;

	while (current && cmp(current->data, data_ref) == 0)
	{
		temp = current;
		current = current->next;
		free(temp->data);
		free(temp);
		*begin_list = current;
	}

	while (current)
	{
		if (cmp(current->data, data_ref) == 0)
		{
			temp = current;
			prev->next = current->next;
			free(temp->data);
			free(temp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

/*void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list *tmp;

	if ((*begin_list == NULL) || (begin_list == NULL))
		return ;
	if (cmp((*begin_list)->data, data_ref) == 0x0)
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
		ft_list_remove_if(&((*begin_list)->next), data_ref, cmp);
}*/