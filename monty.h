#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * enum opcodes - possible opcodes
 * @invalid: invalid opcode
 * @nop: no operation
 * @push: push
 * @pall: print all
 * @pint: print top
 * @pop: pop
 * @swap: swap top 2
 * @add: add top 2
 * @sub: subtract top 2
 * @divide: divide top 2
 * @mul: multiply top 2
 * @mod: remainder of division of top 2
 * @pchar: prints int from top as char
 */

enum opcodes
{
	invalid,
	nop,
	push,
	pall,
	pint,
	pop,
	swap,
	add,
	sub,
	divide,
	mul,
	mod,
	pchar
};

/**
 * struct command_s - opcode and its argument
 * @opcode: the opcode
 * @arg: the argument
 * @ln_num: line number of the instruction
 * @err: error flag
 */
typedef struct command_s
{
	enum opcodes opcode;
	int arg;
	unsigned int ln_num;
	int err;
} command_t;

extern command_t **commands;

/* main */
void check_ac(int ac);
FILE *check_open(char *av1);
int line_count(FILE *input);

/* utilities */
void clean_up(int ln_num, command_t **commands, char *line, FILE *input,
	      int did_err);
void *malloc_or_exit(size_t n);

/* parse_op_arg */
enum opcodes get_opcode(char **line, int ln_num);
void chomp_spaces(char **line);
int get_arg(char **line, enum opcodes opcode, int ln_num, int *did_err);
int is_numeric(char *line);

/* exec */
int run_command(command_t **commands, int num_cmds);
void get_str_func(enum opcodes opcode, instruction_t *current_func);
void get_str_func1(enum opcodes opcode, instruction_t *current_func);

/* instructions-0 */
void exec_push(stack_t **stack, unsigned int line_number);
void exec_pall(stack_t **stack, unsigned int line_number);
void exec_pint(stack_t **stack, unsigned int line_number);
void exec_pop(stack_t **stack, unsigned int line_number);
void exec_swap(stack_t **stack, unsigned int line_number);

/* instructions-1 */
void exec_add(stack_t **stack, unsigned int line_number);
void exec_sub(stack_t **stack, unsigned int line_number);
void exec_div(stack_t **stack, unsigned int line_number);
void exec_mul(stack_t **stack, unsigned int line_number);
void exec_mod(stack_t **stack, unsigned int line_number);

/* instructions-2 */
void exec_nop(stack_t **stack, unsigned int line_number);
void exec_pchar(stack_t **stack, unsigned int line_number);

/* 0-dlinked_lists */
size_t print_stack(const stack_t *h);
size_t stack_len(const stack_t *h);
stack_t *add_dnodeint(stack_t **head, const int n);
stack_t *add_dnodeint_end(stack_t **head, const int n);
void free_stack(stack_t *head);

/* 1-dlinked_lists */
stack_t *get_dnodeint_at_index(stack_t *head, unsigned int index);
int sum_stack(stack_t *head);
stack_t *insert_dnodeint_at_index(stack_t **h, unsigned int idx, int n);
int delete_dnodeint_at_index(stack_t **head, unsigned int index);

#endif /* MONTY_H */
