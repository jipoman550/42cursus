#include "ft_list.h"

// bubble sort
t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
	t_list *current;
	t_list *head;
	int swapped;
	int temp_data;

	if (lst == NULL || lst->next == NULL)
		return (lst);

	head = lst;

	swapped = 1;

	while (swapped)
	{
		swapped = 0;
		current = head;

		while (current != NULL && current->next != NULL)
		{
			if (cmp(current->data, current->next->data) == 0)
			{
				temp_data = current->data;
				current->data = current->next->data;
				current->next->data = temp_data;
				swapped = 1;
			}
			current = current->next;
		}
	}
	return (head);
}