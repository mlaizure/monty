#include "monty.h"

/**
 * clean_up - frees array of structs of opcodes and args and exits
 * @ln_num: line number
 * @commands: array of structs of opcodes and args
 * @did_err: error indicator
 * Return: none
 */

void clean_up(int ln_num, command_t **commands, int did_err)
{
	int i = 0;

	for (i = 0; i < ln_num; ++i)
		free(commands[i]);
	free(commands);
	if (did_err)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
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
