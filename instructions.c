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
