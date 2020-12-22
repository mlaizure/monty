#include "monty.h"

/**
 * exec_add - adds the top two elements of the stack
 * @stack: the stack
 * @line_number: line number from monty byte file
 * Return: none
 */
void exec_add(stack_t **stack, unsigned int line_number)
{
	int len = stack_len(*stack);
	int value0, value1, sum;

	if (len < 2)
	{
		commands[line_number - 1]->err = 1;
		dprintf(STDERR_FILENO, "L%d: can't add, stack too short\n",
			line_number);
		return;
	}
	value0 = (*stack)->n;
	value1 = (*stack)->next->n;
	sum = value0 + value1;
	(*stack)->next->n = sum;
	delete_dnodeint_at_index(stack, 0);
}