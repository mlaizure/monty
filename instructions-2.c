#include "monty.h"

/**
 * exec_nop - adds the top two elements of the stack
 * @stack: the stack
 * @line_number: line number from monty byte file
 * Return: none
 */
void exec_nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

/**
 * exec_pchar - prints char at top of stack
 * @stack: the stack
 * @line_number: line number from monty byte file
 * Return: none
 */
void exec_pchar(stack_t **stack, unsigned int line_number)
{
	int value0;

	if (!*stack)
	{
		commands[line_number - 1]->err = 1;
		dprintf(STDERR_FILENO, "L%d: can't pchar, stack empty\n",
			line_number);
		return;
	}

	value0 = (*stack)->n;
	if (value0 < 0 || value0 > 127)
	{
		commands[line_number - 1]->err = 1;
		dprintf(STDERR_FILENO,
			"L%d: can't pchar, value out of range\n",
			line_number);
		return;
	}
	putchar(value0);
	putchar('\n');
}

/**
 * exec_pstr - prints string starting at top of stack
 * @stack: the stack
 * @line_number: line number from monty byte file
 * Return: none
 */
void exec_pstr(stack_t **stack, unsigned int line_number)
{
	int value;
	stack_t *temp = *stack;

	(void)line_number;
	if (!*stack)
	{
		putchar('\n');
		return;
	}

	for (; temp; temp = temp->next)
	{
		value = temp->n;
		if (value <= 0 || value > 127)
			break;
		putchar(value);
	}
	putchar('\n');
}

/**
 * exec_rotl - rotates the stack to the top
 * @stack: the stack
 * @line_number: line number from monty byte file
 * Return: none
 */
void exec_rotl(stack_t **stack, unsigned int line_number)
{
	(void)line_number;

	if (!*stack)
		return;
	add_dnodeint_end(stack, (*stack)->n);
	delete_dnodeint_at_index(stack, 0);
}

/**
 * exec_rotr - rotates the stack to the bottom
 * @stack: the stack
 * @line_number: line number from monty byte file
 * Return: none
 */
void exec_rotr(stack_t **stack, unsigned int line_number)
{
	size_t idx;
	stack_t *last, *temp = *stack;

	(void)line_number;

	if (!*stack)
		return;

	idx = stack_len(temp) - 1;
	last = get_dnodeint_at_index(temp, idx);
	add_dnodeint(stack, last->n);
	delete_dnodeint_at_index(stack, (idx + 1));
}
