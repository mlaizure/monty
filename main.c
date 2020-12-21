#include "monty.h"

/**
 *
 *
 */

int main(int ac, char *av[])
{
	char *line = NULL, *ln_start = NULL, c;
	int ln_num = 0, ln_total = 0;
	FILE *input;
	size_t len = 0;
	ssize_t n_chars = 0;
	command_t **commands, *c_command;

	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	input = fopen(av[1], "rb");
	if (!input)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	while ((c = fgetc(input)) != EOF)
		if (c == '\n')
			++ln_total;
	rewind(input);

	commands = malloc_or_exit(sizeof(command_t *) * (ln_total + 1));
	while ((n_chars = getline(&line, &len, input)) != -1)
	{
		line[n_chars - 1] = '\0';
		ln_start = line;
		++ln_num;
		chomp_spaces(&line);
		if (*line == '\0')
			continue;
		commands[ln_num - 1] = malloc_or_exit(sizeof(command_t));
		c_command = commands[ln_num - 1];
		c_command->opcode = get_opcode(&line);
		c_command->arg = get_arg(&line, c_command->opcode);
		free(ln_start);
		line = NULL;
	}
	commands[ln_num] = NULL;
	fclose(input);
	return (0);
}

enum opcodes get_opcode(char **line)
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

	*line += len;
	return (current_opcode);
}

void chomp_spaces(char **line)
{
	while (**line == ' ')
		++(*line);
}


int get_arg(char **line, enum opcodes opcode)
{
	int arg;

	switch (opcode)
	{
	case push:
		sscanf(*line, "%d", &arg);
		break;
	default:
		break;
	}
	return (arg);
}
/**
 * malloc_or_exit - returns malloc'd pointer or exits with error on failure
 * @n: number of bytes to malloc
 *
 * Return: malloc'd pointer or exits with error on failure
 */

void *malloc_or_exit(size_t n)
{
	void *result;

	result = malloc(n);
	if (!result)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	return (result);
}
