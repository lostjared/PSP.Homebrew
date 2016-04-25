#include "symtab.h"
int jmp_types[] = { TOK_JMP, TOK_JSR, TOK_BNE, TOK_BEQ, TOK_BCC, TOK_BCS, TOK_BVC, TOK_BVS , TOK_BPL, TOK_BMI,  0 };

struct sym_node *sym_add(struct sym_table *table, char *text, int type, int i, int z, int scope) {

	struct sym_node *node = 0, **pnode = 0;
	struct sym_list *top = 0, **prev = 0;

	if(table->head == 0) {
		table->head = (struct sym_node*) malloc( sizeof(struct sym_node) );
		table->head->left = table->head->right = 0;
		table->count++;
		table->head->text = strdup(text);
		table->head->scope = scope;
		table->head->op_code = trans_opcode(text);
		table->head->i = i, table->head->z = z, table->head->type = type;
		table->node_list = (struct sym_list*) malloc ( sizeof(struct sym_list) );
		table->node_list->node = table->head;
		table->node_list->next = 0;
		table->count++;
		table->tail = table->node_list;
		return table->head;
	}

	node = table->head;
	pnode = &node;

	while (( node = *pnode) != 0) {
		int cmp = strcmp(node->text, text);
		if(cmp == 0) {
			prev = &table->node_list;
			while ((top = *prev)!=0) 
				prev = &top->next;

			top = (struct sym_list*) malloc ( sizeof(struct sym_list ) );
			top->next = 0;
			top->node = node;
			*prev = top;
			table->count++;
			return node;
		}
		pnode = (cmp > 0) ? &node->left : &node->right;
	}

	node = (struct sym_node*) malloc ( sizeof(struct sym_node) );
	node->left = node->right = 0;
	node->i = i, node->z = z, node->text = strdup(text), node->type = type, node->scope = scope;
	node->op_code = trans_opcode(text);
	*pnode = node;
	
	prev = &table->node_list;
	while ((top = *prev)!=0) 
		prev = &top->next;

	top = (struct sym_list*) malloc ( sizeof(struct sym_list ) );
	top->next = 0;
	top->node = node;
	*prev = top;
	table->tail = top;
	table->count++;
	return node;
}

struct sym_node *sym_look(struct sym_table *table, char *text) {

	struct sym_node *node, **pnode = &table->head;
	while( (node = *pnode) != 0 ) {
		int cmp = strcmp(node->text, text);
		if(cmp == 0)
			return node;
		pnode = (cmp > 0) ? &node->left : &node->right;
	}
	return 0;
}

struct sym_list *sym_list_look(struct sym_table *table, struct sym_list *start,  char *text) {
	struct sym_list *start_pos = start, *next_pos = start->next, *prev_pos = start;

	for(start_pos=start; start_pos != 0; start_pos = start_pos->next) {
		if(next_pos == 0)
			return start_pos;
		if(strcmp(start_pos->node->text, text) == 0) {

			int i,jmp_ok = 1;
			for(i = 0; jmp_types[i] != 0; i++)
			{
				if(jmp_types[i] == prev_pos->node->op_code) {
					jmp_ok = 0;
					break;
				}
				else {
					jmp_ok = 1;
				}
			}

			if(jmp_ok == 1)
			return start_pos;
			else continue;
		}
		if(next_pos)
		next_pos = next_pos->next;
		if(prev_pos)
		prev_pos = start_pos;
	}
	return 0;
}

void sym_init(struct sym_table *table) {
	table->count = 0;
	table->head = 0, table->node_list = 0;
	table->tail = 0;
}

void node_free(struct sym_node *node) {

	if(node && node->left)
		node_free(node->left);

	if(node && node->right)
		node_free(node->right);

	if(node) {
		free(node->text);
		free(node);
		node = 0;
	}

}

char *trans_type(int type) {
	switch(type) {
		case TOK_SYMBOL:
			return "Symbol";
		case TOK_CHAR:
			return "Word";
		case TOK_DIGIT:
			return "Digit";
		case TOK_QUOTE:
			return "String";
		case TOK_HEX:
			return "Hexadecimal";
		case TOK_ADMODE:
			return "Address Mode";
		case TOK_NUMERIC:
			return "Numeric Constant";
		case TOK_REGISTER:
			return "Register Variable";

	}
	return "";
}

void list_free(struct sym_list *lst) {
	if(lst->next)
		list_free(lst->next);

	if(lst)
	free(lst);
}

void node_print(struct sym_node *node) {
	if(node->left)
		node_print(node->left);
	
	printf("token [%s] of type [%s] with opcode [%x] at position %d,%d scope[%d]\n", node->text, trans_type(node->type), node->op_code, node->i, node->z, node->scope);

	if(node->right)
		node_print(node->right);

	

}

void list_print(struct sym_list *lst) {
	struct sym_list *i;
	for(i = lst; i != 0; i = i->next)
		printf("%s\n", i->node->text);
}

void sym_print(struct sym_table *table) {
	printf("symbols:\n");
	node_print(table->head);
	printf("tokens [%d]\n", table->count);
	list_print(table->node_list);
}

void sym_free(struct sym_table *table) {

	node_free(table->head);
	list_free(table->node_list);
}
