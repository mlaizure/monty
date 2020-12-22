#include "monty.h"

/**
 * run_command - make stack and call function handlers
 * @commands: opcodes and args from monty byte file
 * @num_cmds: number of instructions from monty byte file
 * Return: 1 on failure, 0 on success
 */
int run_command(command_t **commands, int num_cmds)
{
	int i = 0, err = 0;
	instruction_t **funcs;
	stack_t *stack = NULL;

	funcs = malloc_or_exit(sizeof(instruction_t) * (num_cmds + 1));
	for (i = 0; i < num_cmds; ++i)
	{
		if (commands[i])
			funcs[i] = get_str_func(commands[i]->opcode);
		else
			funcs[i] = NULL;
	}
	funcs[i] = NULL;
	for (i = 0; i < num_cmds; ++i)
	{
		if (funcs[i])
			funcs[i]->f(&stack, commands[i]->ln_num);
		if (commands[i] && commands[i]->err)
		{
			err = commands[i]->err;
			break;
		}
	}
	for (i = 0; i < num_cmds; ++i)
		free(funcs[i]);
	free(funcs);
	free_stack(stack);
	return (err);
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
	case pint:
		current_func->opcode = "pint";
		current_func->f = &exec_pint;
		return (current_func);
	case pop:
		current_func->opcode = "pop";
		current_func->f = &exec_pop;
		return (current_func);
	case swap:
		current_func->opcode = "swap";
		current_func->f = &exec_swap;
		return (current_func);
	case add:
		current_func->opcode = "add";
		current_func->f = &exec_add;
		return (current_func);
	case nop:
		current_func->opcode = "nop";
		current_func->f = &exec_nop;
		return (current_func);
	default:
		break;
	}
	return (NULL);
}
