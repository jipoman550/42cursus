#include "ft_list.h"

int ft_list_size(t_list *begin_list)
{
	int i = 0;

	while (begin_list != NULL)
	{
		begin_list = begin_list->next;
		i++;
	}
	return (i);
}
/*
#include <stdio.h>

int main()
{
	t_list *head = NULL;
	t_list *node1 = NULL;
	t_list *node2 = NULL;
	t_list *node3 = NULL;

	printf("Testing ft_list_size:\n");

	// Test with an empty list
	printf("Size of empty list: %d\n", ft_list_size(head));

	// Create a list with one node
	node1 = (t_list *)malloc(sizeof(t_list));
	if (node1)
	{
		node1->data = (void *)"First";
		node1->next = NULL;
		head = node1;
		printf("Size of list with 1 node: %d\n", ft_list_size(head));
	}

	// Add a second node
	node2 = (t_list *)malloc(sizeof(t_list));
	if (node2)
	{
		node2->data = (void *)"Second";
		node2->next = NULL;
		if (node1) node1->next = node2;
		else head = node2;
		printf("Size of list with 2 nodes: %d\n", ft_list_size(head));
	}

	// Add a third node
	node3 = (t_list *)malloc(sizeof(t_list));
	if (node3)
	{
		node3->data = (void *)"Third";
		node3->next = NULL;
		if (node2) node2->next = node3;
		else if (node1) node1->next = node3;
		else head = node3;
		printf("Size of list with 3 nodes: %d\n", ft_list_size(head));
	}

	t_list *current = head;
	t_list *temp;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}

	return 0;
}*/

// ??free해주는 동작을 하지 않으면, ft_list_size.c를 실행하고 나면 정말로 내 pc의 memory에 남아있어서 메모리 누수가 나는 거임? 그렇다면 이 .c 파일을 실행하면 계속 남아 있는다면 어떻게 없앨 수 있음? 컴퓨터 운영체제가 알아서 없애주나?