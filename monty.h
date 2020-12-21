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
 * @no_op: no opcode
 * @push: push
 * @pall: pall
 */

enum opcodes
{
	invalid,
	no_op,
	push,
	pall
};

/**
 * struct command_s - opcode and its argument
 * @opcode: the opcode
 * @arg: the argument
 */
typedef struct command_s
{
	enum opcodes opcode;
	int arg;
} command_t;


/* main */
void check_ac(int ac);
void check_open(FILE *input, char *av1);
void clean_up(int ln_num, command_t **commands, int did_err);
void *malloc_or_exit(size_t n);

/* parse_op_arg */
enum opcodes get_opcode(char **line, int ln_num);
void chomp_spaces(char **line);
int get_arg(char **line, enum opcodes opcode, int ln_num, int *did_err);
int is_numeric(char *line);

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
