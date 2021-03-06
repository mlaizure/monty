#include "monty.h"

/**
 * exec_push - pushes an arg onto the top of the stack
 * @stack: the stack
 * @line_number: line number from monty byte file
 * Return: none
 */
void exec_push(stack_t **stack, unsigned int line_number)
{
	add_dnodeint(stack, commands[line_number - 1]->arg);
}

/**
 * exec_pall - prints the whole stack
 * @stack: the stack
 * @line_number: line number from monty byte file
 * Return: none
 */
void exec_pall(stack_t **stack, unsigned int line_number)
{
	(void)line_number;
	print_stack(*stack);
}

/**
 * exec_pint - prints the value at the top of the stack
 * @stack: the stack
 * @line_number: line number from monty byte file
 * Return: none
 */
void exec_pint(stack_t **stack, unsigned int line_number)
{
	if (!*stack)
	{
		commands[line_number - 1]->err = 1;
		dprintf(STDERR_FILENO, "L%d: can't pint, stack empty\n",
			line_number);
		return;
	}
	printf("%d\n", (*stack)->n);
}

/**
 * exec_pop - removes top element of the stack
 * @stack: the stack
 * @line_number: line number from monty byte file
 * Return: none
 */
void exec_pop(stack_t **stack, unsigned int line_number)
{
	if (!*stack)
	{
		commands[line_number - 1]->err = 1;
		dprintf(STDERR_FILENO, "L%d: can't pop an empty stack\n",
			line_number);
		return;
	}
	delete_dnodeint_at_index(stack, 0);
}

/**
 * exec_swap - swaps the top two elements of the stack
 * @stack: the stack
 * @line_number: line number from monty byte file
 * Return: none
 */
void exec_swap(stack_t **stack, unsigned int line_number)
{
	int len = stack_len(*stack);
	int value0, value1;

	if (len < 2)
	{
		commands[line_number - 1]->err = 1;
		dprintf(STDERR_FILENO, "L%d: can't swap, stack too short\n",
			line_number);
		return;
	}
	value0 = (*stack)->n;
	value1 = (*stack)->next->n;
	(*stack)->n = value1;
	(*stack)->next->n = value0;
}
