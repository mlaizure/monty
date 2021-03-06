#include "monty.h"
command_t **commands;

/**
 * main - gets command line args and calls functions to parse and execute
 * monty byte code file
 * @ac: number of command line args
 * @av: array of strings of command line args
 * Return: always 0
 */
int main(int ac, char *av[])
{
	char *line = NULL, *ln_start = NULL;
	int ln_total = 0, did_err = 0, status = 0;
	unsigned int ln_num = 0;
	FILE *input = NULL;
	size_t len = 0;
	ssize_t n_chars = 0;
	command_t *cmd = NULL;

	check_ac(ac);
	input = check_open(av[1]);
	ln_total = line_count(input);
	commands = malloc_or_exit(sizeof(command_t *) * (ln_total));
	while ((n_chars = getline(&ln_start, &len, input)) != -1)
	{
		ln_start[n_chars - 1] = '\0';
		line = ln_start;
		++ln_num;
		chomp_spaces(&line);
		if (*line == '\0' || *line == '#')
		{
			commands[ln_num - 1] = NULL;
			continue;
		}
		cmd = commands[ln_num - 1] = malloc_or_exit(sizeof(command_t));
		cmd->opcode = get_opcode(&line, ln_num);
		if (cmd->opcode == invalid)
			clean_up(ln_num, commands, ln_start, input, 1);
		cmd->arg = get_arg(&line, cmd->opcode, ln_num, &did_err);
		if (did_err)
			clean_up(ln_num, commands, ln_start, input, did_err);
		cmd->ln_num = ln_num;
		cmd->err = 0;
		free(ln_start);
		ln_start = NULL;
	}
	status = run_command(commands, ln_total);
	clean_up(ln_num, commands, ln_start, input, status);
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
 * @av1: name of file that can't be opened
 * Return: file stream
 */
FILE *check_open(char *av1)
{
	FILE *input = fopen(av1, "rb");

	if (!input)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av1);
		exit(EXIT_FAILURE);
	}
	return (input);
}

/**
 * line_count - gets total number of lines from monty byte file
 * @input: file stream to get line count from
 * Return: number of lines
 */

int line_count(FILE *input)
{
	char c;
	int ln_total = 0;

	while ((c = fgetc(input)) != EOF)
		if (c == '\n')
			++ln_total;
	rewind(input);
	return (ln_total);

}
