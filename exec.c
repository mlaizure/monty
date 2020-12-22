#include "monty.h"

/**
 * run_command - make stack and call function handlers
 * @commands: opcodes and args from monty byte file
 * @num_cmds: number of instructions from monty byte file
 * Return: none
 */
void run_command(command_t **commands, int num_cmds)
{
	int i = 0;
	instruction_t **funcs;
	stack_t *stack = NULL;

	funcs = malloc_or_exit(sizeof(instruction_t) * (num_cmds + 1));
	for (i = 0; commands[i]; ++i)
		funcs[i] = get_str_func(commands[i]->opcode);
	funcs[i] = NULL;
	for (i = 0; funcs[i]; ++i)
		funcs[i]->f(&stack, commands[i]->ln_num);
	for (i = 0; funcs[i]; ++i)
		free(funcs[i]);
	free(funcs);
	free_stack(stack);
}

/**
 * get_str_func - adds opcode and function pointer to instruction struct
 * @opcode: opcode to add
 * Return: pointer to allocated and filled struct
 */
instruction_t *get_str_func(enum opcodes opcode)
{
	instruction_t *current_func;

	current_func = malloc_or_exit(sizeof(instruction_t));
	switch (opcode)
	{
	case push:
		current_func->opcode = "push";
		current_func->f = &exec_push;
		return (current_func);
	case pall:
		current_func->opcode = "pall";
		current_func->f = &exec_pall;
		return (current_func);
	default:
		break;
	}
	return (NULL);
}
