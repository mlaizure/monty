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
		{
			funcs[i] = malloc_or_exit(sizeof(instruction_t));
			get_str_func(commands[i]->opcode, funcs[i]);
		}
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
 * @current_func: pointer to instruction struct
 * Return: none
 */
void get_str_func(enum opcodes opcode, instruction_t *current_func)
{
	switch (opcode)
	{
	case push:
		current_func->opcode = "push", current_func->f = &exec_push;
		break;
	case pall:
		current_func->opcode = "pall", current_func->f = &exec_pall;
		break;
	case pint:
		current_func->opcode = "pint", current_func->f = &exec_pint;
		break;
	case pop:
		current_func->opcode = "pop", current_func->f = &exec_pop;
		break;
	case swap:
		current_func->opcode = "swap", current_func->f = &exec_swap;
		break;
	case add:
		current_func->opcode = "add", current_func->f = &exec_add;
		break;
	case nop:
		current_func->opcode = "nop", current_func->f = &exec_nop;
		break;
	case sub:
		current_func->opcode = "sub", current_func->f = &exec_sub;
		break;
	case divide:
		current_func->opcode = "div", current_func->f = &exec_div;
		break;
	case mul:
		current_func->opcode = "mul", current_func->f = &exec_mul;
		break;
	case mod:
		current_func->opcode = "mod", current_func->f = &exec_mod;
		break;
	default:
		get_str_func1(opcode, current_func);
	}
}

/**
 * get_str_func1 - adds opcode and function pointer to instruction struct
 * @opcode: opcode to add
 * @current_func: pointer to instruction struct
 * Return: none
 */
void get_str_func1(enum opcodes opcode, instruction_t *current_func)
{
	switch (opcode)
	{
	case pchar:
		current_func->opcode = "pchar", current_func->f = &exec_pchar;
		break;
	case pstr:
		current_func->opcode = "pstr", current_func->f = &exec_pstr;
		break;
	case rotl:
		current_func->opcode = "rotl", current_func->f = &exec_rotl;
		break;
	case rotr:
		current_func->opcode = "rotr", current_func->f = &exec_rotr;
		break;
	default:
		break;
	}
}
