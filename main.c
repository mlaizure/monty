#include "monty.h"

/**
 * main - gets command line args and calls functions to parse and execute
 * monty byte code file
 * @ac: number of command line args
 * @av: array of strings of command line args
 * Return: always 0
 */

int main(int ac, char *av[])
{
	char *line = NULL, *ln_start = NULL, c;
	int ln_num = 0, ln_total = 0;
	FILE *input;
	size_t len = 0;
	ssize_t n_chars = 0;
	command_t **commands, *c_command;
	enum opcodes op;

	check_ac(ac);
	input = fopen(av[1], "rb");
	check_open(input, av[1]);
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
		op = get_opcode(&line, ln_num);
		check_invalid(op, ln_num, commands);
		c_command->arg = get_arg(&line, c_command->opcode);
		free(ln_start);
		line = NULL;
	}
	commands[ln_num] = NULL;
	fclose(input);
	return (0);
}

/**
 * check_ac - checks # of command line args and prints to stderr and exits
 * on error
 * @ac: number of command line args
 * Return: none
 */
void check_ac(int ac)
{
	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
}


/**
 * check_open - makes sure file opened correctly and prints to stderr and
 * exits on error
 * @input: file stream to check
 * @av1: name of file that can't be opened
 * Return: none
 */
void check_open(FILE *input, char *av1)
{
	if (!input)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av1);
		exit(EXIT_FAILURE);
	}

}

/**
 * check_invalid - frees array of structs of opcodes and args and exits if
 * opcode is invalid (error printed to stderr in get_opcode)
 * @op: opcode to check
 * @ln_num: line number of opcode
 * @commands: array of structs of opcodes and args
 * Return: none
 */

void check_invalid(enum opcodes op, int ln_num, command_t **commands)
{
	int i = 0;

	if (op == invalid)
	{
		for (i = 0; i < ln_num; ++i)
			free(commands[i]);
		free(commands);
		exit(EXIT_FAILURE);
	}

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
