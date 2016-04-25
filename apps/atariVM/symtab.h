#ifndef __SYMTAB__H_
#define __SYMTAB__H_

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

enum { TOK_NULL = 0, TOK_WORD, TOK_STRING, TOK_NUMBER, TOK_SYMBOL, TOK_CHAR, TOK_DIGIT, TOK_QUOTE, TOK_OBRACE, 
TOK_CBRACE, TOK_OPARAM, TOK_CPARAM, TOK_ADDRESS, TOK_SEMI, TOK_COMMA, TOK_NUMERIC, TOK_ADMODE, TOK_HEX, TOK_REGISTER };

#define TOK_ID 0

enum { tok_size = 1024 };
// opcode types
enum op_type { TOK_ADC = 1, TOK_AND, TOK_ASL, TOK_BCC, TOK_BCS, TOK_BEQ, TOK_BIT, TOK_BMI, TOK_BNE, TOK_BPL, TOK_BRK,
TOK_BVC, TOK_BVS, TOK_CLC, TOK_CLD, TOK_CLI, TOK_CLV, TOK_CMP, TOK_CPX, TOK_CPY, TOK_DEC, TOK_DEX, TOK_DEY, TOK_EOR, TOK_INC, TOK_INT, TOK_INX, TOK_INY, TOK_JMP, TOK_JSR,
TOK_LDA, TOK_LDM, TOK_LDX, TOK_LDY, TOK_LSR, TOK_NOP, TOK_ORA, TOK_PHA, TOK_PHP, TOK_PLA, TOK_PLP, TOK_ROL, TOK_ROR, TOK_RTI, TOK_RTS, TOK_SBC, TOK_SEC,
TOK_SED, TOK_SEI, TOK_STA, TOK_STX, TOK_STY, TOK_TAX, TOK_TAY, TOK_TSX, TOK_TXA, TOK_TXS, TOK_TYA };

extern int jmp_types[]; 


struct sym_node {
	char *text;
	int   type;
	int   i,z,scope;
	unsigned int op_code;
	struct sym_node *left, *right;
	int index;
};
struct sym_list {
	struct sym_node *node;
	struct sym_list *next;
//	int index;
};

struct sym_table {
	struct sym_node *head;
	struct sym_list *node_list,*tail;
	int count;

};

extern void sym_init(struct sym_table *table);
extern struct sym_node *sym_add(struct sym_table *table, char *text, int type, int i, int z, int scope);
extern struct sym_node *sym_look(struct sym_table *table, char *text);
extern void sym_free(struct sym_table *table);
extern void sym_print(struct sym_table *table);
extern int trans_opcode(const char *op_code);
extern struct sym_list *sym_list_look(struct sym_table *table, struct sym_list *start,  char *text);

extern int debug_mode;


#endif

