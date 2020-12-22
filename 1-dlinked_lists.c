#include "monty.h"

/**
 * get_dnodeint_at_index - returns the nth node of a stack_t linked list
 * @head: pointer to head of list
 * @index: index of the node to get starting from 0
 * Return: nth node of list
 */

stack_t *get_dnodeint_at_index(stack_t *head, unsigned int index)
{
	unsigned int i;

	if (!head)
		return (NULL);

	for (i = 0; head && i < index; ++i)
		head = head->next;
	if (i == index)
		return (head);
	else
		return (NULL);
}

/**
 * sum_stack - returns sum of all the data in a stack_t linked list
 * @head: pointer to head of list
 * Return: sum of data in list, 0 if list is empty
 */

int sum_stack(stack_t *head)
{
	int sum = 0;

	if (!head)
		return (sum);

	for (; head; head = head->next)
		sum += head->n;

	return (sum);
}

/**
 * insert_dnodeint_at_index - inserts a new node at a given position
 * @h: pointer to head of list
 * @idx: index of the list where the new node should be added (starts at 0)
 * @n: data to insert in new node
 * Return: address of the new node or NULL on failure
 */

stack_t *insert_dnodeint_at_index(stack_t **h, unsigned int idx, int n)
{
	stack_t *new, *addr, *temp = *h;
	unsigned int i;

	if (idx == 0)
	{
		addr = add_dnodeint(h, n);
		return (addr);
	}
	if (!temp)
		return (NULL);

	for (i = 0; temp && i < idx; ++i)
		temp = temp->next;
	if (i != idx)
		return (NULL);
	if (!temp)
	{
		addr = add_dnodeint_end(h, n);
		return (addr);
	}

	new = malloc_or_exit(sizeof(stack_t));

	new->n = n;

	temp->prev->next = new;
	new->next = temp;
	new->prev = temp->prev;
	temp->prev = new;
	return (new);
}

/**
 * delete_dnodeint_at_index - deletes the node at index index of a stack_t
 * linked list
 * @head: pointer to head of list
 * @index: index of hte node to be deleted (starts at 0)
 * Return: 1 on success, -1 on failure
 */

int delete_dnodeint_at_index(stack_t **head, unsigned int index)
{
	unsigned int i;
	stack_t *temp = *head;

	if (!temp)
		return (-1);

	for (i = 0; temp && i < index; ++i)
		temp = temp->next;

	if (temp == NULL)
		return (-1);

	if (*head == temp)
		*head = temp->next;

	if (temp->next)
		temp->next->prev = temp->prev;

	if (temp->prev)
		temp->prev->next = temp->next;

	free(temp);
	return (1);
}
