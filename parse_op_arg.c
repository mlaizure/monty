#include "monty.h"

/**
 * get_opcode - parses opcode from file
 * @line: line from monty byte code file
 * @ln_num: line number of line in monty byte code file
 * Return: opcode from line
 */
enum opcodes get_opcode(char **line, int ln_num)
{
	int len = 0;
	enum opcodes current_opcode;

	if (**line == '\0')
		return (no_op);

	while ((*line)[len] != ' ' && (*line)[len] != '\0')
		++len;

	if (!strncmp("push", *line, len))
		current_opcode = push;

	else if (!strncmp("pall", *line, len))
		current_opcode = pall;

	else
	{
		(*line)[len] = '\0';
		dprintf(STDERR_FILENO, "L%d: unknown instruction %s\n",
			ln_num, *line);
		return (invalid);
	}
	*line += len;
	return (current_opcode);
}

/**
 * chomp_spaces - moves pointer along string while there are spaces
 * @line: string to remove spaces from
 * Return: none
 */
void chomp_spaces(char **line)
{
	while (**line == ' ')
		++(*line);
}

/**
 * get_arg - gets argument from line in monty byte code file
 * @line: line from monty byte code file
 * @opcode: opcode from line
 * Return: argument from line
 */
int get_arg(char **line, enum opcodes opcode)
{
	int arg;

	switch (opcode)
	{
	case push:
		arg = atoi(*line);
		break;
	default:
		break;
	}
	return (arg);
}
