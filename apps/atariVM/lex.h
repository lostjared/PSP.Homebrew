#ifndef __LEX__H_
#define __LEX__H_
#include<SDL.h>
#include "symtab.h"

typedef struct file_buffer {
	FILE *fptr;
	int cpos;
	int cline;
};

extern char token_map[256];
extern struct sym_table symbols;

typedef struct token {
	char tok[tok_size];
	int   type;
	int i,z,scope;
};

typedef struct call_back {
	void (*func)();
	unsigned int address;
};

extern struct token cur_token;


extern int mlex_init_file(struct file_buffer *buf, const char *src);
extern int mlex_close(struct file_buffer *buf);
extern char mlex_getc(struct file_buffer *buf);
extern void mlex_gettoken(struct file_buffer *buf);
extern void mlex_anaylize(struct file_buffer *buf);
extern void mlex_addtoken();
extern void parse();
extern void build_icode(const char *);
extern void build_debug(const char *);
extern unsigned char get_machine_opcode(struct sym_list *, int *);
extern unsigned char set_bit(unsigned char, unsigned char);
extern unsigned char clr_bit(unsigned char, unsigned char);
extern unsigned char get_bit(unsigned char, unsigned char);
extern struct call_back *get_callback(unsigned int address);
extern struct call_back *callbacks;
extern int compile;
extern void build_c(const char *output);
extern int term(int *type);
extern SDL_Surface *getfront();

#endif
