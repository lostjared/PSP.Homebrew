#include "stack.h"

struct mas_stack the_stack;
struct mas_int_stack int_stack;

void stack_init(struct mas_stack *s) {
	memset(s, 0, sizeof(s));

}
void stack_push(struct mas_stack *s, struct sym_list *i) {
	if(s->stack_pointer < stack_size)
	s->_stack[s->stack_pointer++] = i;
	else
		printf("*- stack overflow");

}
struct sym_list *stack_pop(struct mas_stack *s) {
	if(s->stack_pointer > 0)
		return s->_stack[--s->stack_pointer];
	else
		return 0;
}

void int_stack_init(struct mas_int_stack *s) {
	memset(s, 0, sizeof(s));
}
void int_stack_push(struct mas_int_stack *s, unsigned char i) {
	if(s->stack_pointer < stack_size)
		s->_stack[s->stack_pointer++] = i;

}
unsigned char int_stack_pop(struct mas_int_stack * s) {
	
	if(s->stack_pointer > 0) {
		--s->stack_pointer;
		return s->_stack[s->stack_pointer];
	}
	return 0;
}
