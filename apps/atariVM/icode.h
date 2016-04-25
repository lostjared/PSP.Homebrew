#ifndef __ICODE__H_
#define __ICODE__H_


#include "lex.h"

// address modes
#define ACCUMULATOR  12
#define IMMEDIATE    1
#define ZEROPAGE     2
#define ZEROPAGE_X   3
#define ZEROPAGE_Y   4
#define ABSOULTE     5
#define ABSOULTE_X   6
#define ABSOULTE_Y   7
#define IMPLIED      8
#define RELATIVE     9
#define INDIRECT_I   10
#define INDEXED_I    11
#define INDIRECT     13


// opcode mnemoics array
extern const char *op_array[];

// struct to stand for the machine code
typedef struct machine_code {
	unsigned char op_code;
	int address_mode;
	int p_code;
};



extern struct machine_code code[];
extern int debug_mode;
extern void set_callback(struct call_back *);
extern void do_quit();
extern void do_init();

#endif