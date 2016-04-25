#ifndef __STACK__H_
#define __STACK__H_

#include "symtab.h"

#define stack_size 0xFF

typedef struct mas_stack {
	struct sym_list *_stack[stack_size];
	int stack_pointer;
};

typedef struct mas_int_stack {
	unsigned char _stack[stack_size];
	int stack_pointer;
};


extern struct mas_stack the_stack;
extern struct mas_int_stack int_stack;
extern void stack_init(struct mas_stack *);
extern void stack_push(struct mas_stack *, struct sym_list *);
extern struct sym_list *stack_pop(struct mas_stack *);
extern void int_stack_init(struct mas_int_stack *);
extern void int_stack_push(struct mas_int_stack *, unsigned char );
extern unsigned char int_stack_pop(struct mas_int_stack *);


#endif