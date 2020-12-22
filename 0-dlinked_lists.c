#include "monty.h"

/**
 * print_stack - prints all the elements of a stack_t list
 * @h: pointer to head of list
 *
 * Return: number of nodes
 */

size_t print_stack(const stack_t *h)
{
	size_t i;

	for (i = 0; h; ++i)
	{
		printf("%d\n", h->n);
		h = h->next;
	}
	return (i);
}

/**
 * stack_len - returns the number of elements in a linked stack_t list
 * @h: pointer to head of list
 * Return: number of elements in the list
 */

size_t stack_len(const stack_t *h)
{
	size_t i;

	for (i = 0; h; ++i)
		h = h->next;
	return (i);
}

/**
 * add_dnodeint - adds a new node at the beginning of a stack_t list
 * @head: head of linked list
 * @n: data in new node
 * Return: address of the new element or NULL on failure
 */

stack_t *add_dnodeint(stack_t **head, const int n)
{
	stack_t *new;

	new = malloc_or_exit(sizeof(stack_t));

	new->n = n;
	new->prev = NULL;

	new->next = *head;
	if (*head)
		(*head)->prev = new;
	*head = new;
	return (new);

}

/**
 * add_dnodeint_end - adds a new node at the end of a stack_t list
 * @head: pointer to head of list
 * @n: data for new node
 * Return: address of new element of NULL on failure
 */

stack_t *add_dnodeint_end(stack_t **head, const int n)
{
	stack_t *new, *last;

	new = malloc_or_exit(sizeof(stack_t));

	new->n = n;
	new->next = NULL;

	if (*head == NULL)
	{
		*head = new;
		new->prev = NULL;
		return (new);
	}

	last = *head;
	while (last->next)
		last = last->next;

	new->prev = last;
	last->next = new;
	return (new);
}

/**
 * free_stack - frees a stack list
 * @head: pointer to head of list
 * Return: none
 */

void free_stack(stack_t *head)
{
	stack_t *next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}
