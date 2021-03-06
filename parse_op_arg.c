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
	enum opcodes current_opcode = invalid;

	if (**line == '\0')
		return (nop);
	while ((*line)[len] != ' ' && (*line)[len] != '\0')
		++len;
	(!strncmp("push", *line, len)) && (current_opcode = push);
	(!strncmp("pall", *line, len)) && (current_opcode = pall);
	(!strncmp("pint", *line, len)) && (current_opcode = pint);
	(!strncmp("pop", *line, len)) && (current_opcode = pop);
	(!strncmp("swap", *line, len)) && (current_opcode = swap);
	(!strncmp("add", *line, len)) && (current_opcode = add);
	(!strncmp("nop", *line, len)) && (current_opcode = nop);
	(!strncmp("sub", *line, len)) && (current_opcode = sub);
	(!strncmp("div", *line, len)) && (current_opcode = divide);
	(!strncmp("mul", *line, len)) && (current_opcode = mul);
	(!strncmp("mod", *line, len)) && (current_opcode = mod);
	(!strncmp("pchar", *line, len)) && (current_opcode = pchar);
	(!strncmp("pstr", *line, len)) && (current_opcode = pstr);
	(!strncmp("rotl", *line, len)) && (current_opcode = rotl);
	(!strncmp("rotr", *line, len)) && (current_opcode = rotr);

	if (current_opcode == invalid)
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
 * @ln_num: line number
 * @did_err: error indicator
 * Return: argument from line
 */
int get_arg(char **line, enum opcodes opcode, int ln_num, int *did_err)
{
	int arg;

	chomp_spaces(line);
	switch (opcode)
	{
	case push:
		if (is_numeric(*line))
			arg = atoi(*line);
		else
		{
			*did_err = 1;
			dprintf(STDERR_FILENO, "L%d: usage: push integer\n",
				ln_num);
		}
		break;
	default:
		break;
	}
	return (arg);
}

/**
 * is_numeric - checks to see if arg is int
 * @line: line containing arg to check
 * Return: 1 if int, 0 if not
 */
int is_numeric(char *line)
{
	if (!*line)
		return (0);

	if (*line == '-')
		++line;

	while (*line && *line != ' ')
	{
		if (*line >= '0' && *line <= '9')
			++line;
		else
			return (0);
	}
	return (1);
}
