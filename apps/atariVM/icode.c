#include "icode.h"
#include "stack.h"

const char *op_array[] = { 0, "adc", "and", "asl", "bcc", "bcs", "beq", "bit", "bmi", "bne", "bpl", "brk", "bvc",
"bvs", "clc", "cld", "cli", "clv", "cmp", "cpx", "cpy", "dec", "dex", "dey", "eor", "inc", "int", "inx", "iny", "jmp", "jsr",
"lda", "ldm", "ldx", "ldy","lsr", "nop", "ora", "pha", "php", "pla", "plp", "rol", "ror", "rti", "rts", "sbc", "sec",
"sed", "sei", "sta", "stx", "sty", "tax", "tay", "tsx", "txa", "txs", "tya", 0 };

// machine code op-codes                
struct machine_code code[] = {
// ADC
{ 0x69, IMMEDIATE, TOK_ADC }, { 0x65, ZEROPAGE, TOK_ADC },
{ 0x75, ZEROPAGE_X, TOK_ADC }, { 0x6D, ABSOULTE, TOK_ADC }, {0x7D, ABSOULTE_X, TOK_ADC }, { 0x79, ABSOULTE_Y, TOK_ADC},
{ 0x61, INDEXED_I, TOK_ADC }, { 0x71, INDIRECT_I, TOK_ADC }, 
// AND
{ 0x29, IMMEDIATE, TOK_AND }, {0x25, ZEROPAGE, TOK_AND}, {0x35, ZEROPAGE_X, TOK_AND}, {0x2D, ABSOULTE, TOK_AND},
{ 0x3D, ABSOULTE_X, TOK_AND }, {0x39, ABSOULTE_Y, TOK_AND }, {0x21, INDEXED_I, TOK_AND}, {0x31, INDIRECT_I, TOK_AND},
// ASL
{ 0x0A, ACCUMULATOR, TOK_ASL }, {0x06, ZEROPAGE, TOK_ASL}, {0x16, ZEROPAGE_X, TOK_ASL}, {0x0E, ABSOULTE, TOK_ASL},
{ 0x1E, ABSOULTE_X, TOK_ASL },
// BCC
{ 0x90, RELATIVE, TOK_BCC},
// BCS
{ 0xB0, RELATIVE, TOK_BCS},
// BEQ
{ 0xF0, RELATIVE, TOK_BEQ},
// BIT
{ 0x24, ZEROPAGE, TOK_BIT}, {0x2C, ABSOULTE, TOK_BIT},
// BMI
{ 0x30, RELATIVE, TOK_BMI},
// BNE
{ 0xD0, RELATIVE, TOK_BNE},
// BPL
{ 0x10, RELATIVE, TOK_BPL},
// BRK
{ 0x00, IMPLIED, TOK_BRK},
// BVC
{ 0x50, RELATIVE, TOK_BVC},
// BVS
{ 0x70, RELATIVE, TOK_BVC},
// CLC
{ 0x18, IMPLIED, TOK_CLC},
// CLD
{ 0xD8, IMPLIED, TOK_CLD},
// CLI
{ 0x58, IMPLIED, TOK_CLI},
// CLV
{ 0xB8, IMPLIED, TOK_CLV},
// CMP
{ 0xC9, IMMEDIATE, TOK_CMP}, {0xC5, ZEROPAGE, TOK_CMP}, { 0xD5, ZEROPAGE_X, TOK_CMP }, { 0xCD, ABSOULTE, TOK_CMP},
{ 0xDD, ABSOULTE_X, TOK_CMP}, {0xD9, ABSOULTE_Y, TOK_CMP}, {0xD9, ABSOULTE_Y, TOK_CMP}, { 0xC1, INDEXED_I, TOK_CMP},
{ 0xD1, INDIRECT_I, TOK_CMP},
// CPX
{ 0xE0, IMMEDIATE, TOK_CPX}, {0xE4, ZEROPAGE, TOK_CPX}, {0xEC, ABSOULTE, TOK_CPX},
// CPY
{ 0xC0, IMMEDIATE, TOK_CPY}, {0xC4, ZEROPAGE, TOK_CPY}, {0xCC, ABSOULTE, TOK_CPY},
// DEC
{ 0xC6, ZEROPAGE, TOK_DEC}, {0xD6, ZEROPAGE_X, TOK_DEC}, {0xCE, ABSOULTE, TOK_DEC}, {0xDE, ABSOULTE_X, TOK_DEC},
// DEX
{ 0xCA, IMPLIED, TOK_DEX},
// DEY
{ 0x88, IMPLIED, TOK_DEY},
// EOR
{ 0x49, IMMEDIATE, TOK_EOR}, {0x45, ZEROPAGE, TOK_EOR}, {0x55, ZEROPAGE_X, TOK_EOR}, {0x4D, ABSOULTE, TOK_EOR},
{ 0x5D, ABSOULTE_X, TOK_EOR}, {0x59, ABSOULTE_Y, TOK_EOR}, {0x41, INDEXED_I, TOK_EOR}, {0x51, INDIRECT_I, TOK_EOR},
// INC
{0xE6, ZEROPAGE, TOK_INC}, {0xF6, ZEROPAGE_X, TOK_INC}, {0xEE, ABSOULTE, TOK_INC}, {0xFE, ABSOULTE_X, TOK_INC},
// INX
{0xE8, IMPLIED, TOK_INX},
// INY
{0xC8, IMPLIED, TOK_INY},
// JMP
{0x4C, ABSOULTE, TOK_JMP}, {0x6C, INDIRECT, TOK_JMP},
// JSR
{0x20, ABSOULTE, TOK_JSR},
// LDA 
{ 0xA9, IMMEDIATE, TOK_LDA}, {0xA5, ZEROPAGE, TOK_LDA}, {0xB5, ZEROPAGE_X, TOK_LDA}, {0xAD, ABSOULTE, TOK_LDA},
{ 0xBD, ABSOULTE_X, TOK_LDA}, {0xB9, ABSOULTE_Y, TOK_LDA}, {0xA1, INDEXED_I, TOK_LDA}, {0xB1, INDIRECT_I, TOK_LDA},
// LDX
{0xA2, IMMEDIATE, TOK_LDX}, {0xA6, ZEROPAGE, TOK_LDX}, {0xB6, ZEROPAGE_Y, TOK_LDX}, {0xAE, ABSOULTE, TOK_LDX},
{0xA1, INDEXED_I, TOK_LDX},{0xB1, INDIRECT_I, TOK_LDX},
// LDY
{0xA0, IMMEDIATE, TOK_LDY}, {0xA4, ZEROPAGE, TOK_LDY}, {0xB4, ZEROPAGE_X, TOK_LDY}, {0xAC, ABSOULTE, TOK_LDY},
{0xBC, ABSOULTE_X, TOK_LDY}, 
// LSR
{0x4A, ACCUMULATOR, TOK_LSR}, {0x46, ZEROPAGE, TOK_LSR}, {0x56, ZEROPAGE_X, TOK_LSR}, {0x4E, ABSOULTE, TOK_LSR},
{0x5E, ABSOULTE_X, TOK_LSR},
// NOP
{0xEA, IMPLIED, TOK_NOP},
// ORA
{0x09, IMMEDIATE, TOK_ORA}, {0x05, ZEROPAGE, TOK_ORA}, {0x15, ZEROPAGE_X, TOK_ORA}, {0x0D, ABSOULTE, TOK_ORA},
{0x1D, ABSOULTE_X, TOK_ORA}, {0x19, ABSOULTE_Y, TOK_ORA}, {0x01, INDEXED_I, TOK_ORA}, {0x11, INDIRECT_I, TOK_ORA},
// PHA
{0x48, IMPLIED, TOK_PHA},
// PHP
{0x08, IMPLIED, TOK_PHP},
// PLA
{0x68, IMPLIED, TOK_PLA},
// PLP
{0x28, IMPLIED, TOK_PLP},
// ROL
{0x21, ACCUMULATOR, TOK_ROL},{0x26, ZEROPAGE, TOK_ROL}, {0x36, ZEROPAGE_X, TOK_ROL}, {0x2E, ABSOULTE, TOK_ROL},
{0x3E, ABSOULTE_X, TOK_ROL},
// ROR 
{0x6A, ACCUMULATOR, TOK_ROR}, {0x66, ZEROPAGE, TOK_ROR}, {0x76, ZEROPAGE_X, TOK_ROR}, {0x6E, ABSOULTE, TOK_ROR},
{0x7E, ABSOULTE_X, TOK_ROR},
// RTI
{0x40, IMPLIED, TOK_RTI},
// RTS
{0x60, IMPLIED, TOK_RTS},
// SBC
{ 0xE9, IMMEDIATE, TOK_SBC}, {0xE5, ZEROPAGE, TOK_SBC}, {0xF5, ZEROPAGE_X, TOK_SBC}, {0xED, ABSOULTE, TOK_SBC},
{ 0xFD, ABSOULTE_X, TOK_SBC}, {0xF9, ABSOULTE_Y, TOK_SBC}, {0xE1, INDEXED_I, TOK_SBC}, {0xF1, INDIRECT_I, TOK_SBC},
// SEC
{0x38, IMPLIED, TOK_SEC},
// SED
{0xF8, IMPLIED, TOK_SED},
// SEI
{0x78, IMPLIED, TOK_SEI},
// STA
{ 0x85, ZEROPAGE, TOK_STA}, {0x95, ZEROPAGE_X, TOK_STA}, {0x8D, ABSOULTE, TOK_STA}, {0x9D, ABSOULTE_X, TOK_STA},
{ 0x99, ABSOULTE_Y, TOK_STA}, {0x81, INDEXED_I, TOK_STA}, {0x91, INDIRECT_I, TOK_STA},
// STX
{ 0x86, ZEROPAGE, TOK_STX}, {0x96,  ZEROPAGE_Y, TOK_STX}, {0x8E, ABSOULTE, TOK_STX},
// STY
{ 0x84, ZEROPAGE, TOK_STY}, {0x94, ZEROPAGE_X, TOK_STY}, {0x8C, ABSOULTE, TOK_STY},
// TAX
{ 0xAA, IMPLIED, TOK_TAX},
// TAY
{ 0xA8, IMPLIED, TOK_TAY},
// TSX
{ 0xBA, IMPLIED, TOK_TSX},
// TXA
{ 0x8A, IMPLIED, TOK_TXA},
// TXS
{ 0x9A, IMPLIED, TOK_TXS},
// TYA
{ 0x98, IMPLIED, TOK_TYA},

0

};



void strlower(char *buf) {
	int i;
	for( i = 0; buf[i] != 0; i++)
		buf[i] = (char)tolower(buf[i]);
}

int trans_opcode(const char *op_code) {
	int i;
	strlower((char*)op_code);
	for(i = 1; op_array[i] != 0; i++)
		if(strcmp(op_array[i], op_code) == 0) {
			return i;
		}
	return TOK_NULL;
}

void build_icode(const char *icode) {

	struct sym_list *lst;
	FILE *fptr = fopen(icode,"w");
	if(!fptr)
		return;

	fwrite(&symbols.count, 1, sizeof(symbols.count), fptr);

	for(lst = symbols.node_list; lst != 0; lst = lst->next) {
		
		if(lst->node->op_code == 0) {
			unsigned int ival = atoi(lst->node->text);
			fwrite(&ival, 1, sizeof(ival), fptr);
		}
		else {
			fwrite(&lst->node->op_code, 1, sizeof(lst->node->op_code), fptr);
		}
	}

	fclose(fptr);
}
unsigned char get_machine_opcode(struct sym_list *l, int *address_mode) {

	int i;
	for(i = 0; code[i].p_code != 0; i++) {


		if(code[i].p_code == l->node->op_code && (code[i].address_mode == *address_mode || code[i].address_mode == IMPLIED || code[i].address_mode == RELATIVE)) {

			*address_mode = code[i].address_mode;
			return code[i].op_code;
		}
	}

	return 0;
}

char *trans_admode(int *mode) {

	switch(*mode) {
		case ACCUMULATOR:
			return "Accumulator";
		case ZEROPAGE:
			return "Zero Page";
		case ZEROPAGE_X:
			return "Zero Page (X)";
		case ZEROPAGE_Y:
			return "Zero Page (Y)";
		case INDEXED_I:
			return "Indexed Indirect";
		case INDIRECT_I:
			return "Indirect Index";
		case ABSOULTE:
			return "*Absoulte*";
		case ABSOULTE_X:
			return "Absoulte X";
		case ABSOULTE_Y:
			return "Absoulte Y";
		case IMMEDIATE:
			return "Immediate";
		case RELATIVE:
			return "Realtive";
		case IMPLIED:
			return "Implied";
	}

	return "Null";
}


/*
void build_c(const char *output) {

	// proccess the symbol table and find all the string variables
	// loop through and print each token to the correct c function
	
	FILE *fptr = fopen(output, "w");
	int index = 0;
	if(!fptr) return;

	fprintf(fptr, "#include<stdio.h>\n#include<stdlib.h>\n#include<SDL.h>\n#include\"ataristd.h\"\n\n");

	for(lst = symbols.node_list; lst != 0; lst = lst->next) {
		if(lst->node->type == TOK_QUOTE) {
			lst->node->index = index;
			fprintf(fptr,"const char *strvar%d = \"%s\";\n", index++,  lst->node->text);
		}

	}
	
	stack_init(&the_stack);
	fprintf(fptr,"extern int SDL_main(int argc, char **argv) {\n\n");
	fprintf(fptr,"SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);\n\n");
		lst = symbols.node_list;
		while(lst != 0) {
			char op_code = lst->node->op_code;
		switch(lst->node->op_code) {
			case TOK_LDA:
			case TOK_LDX:
			case TOK_LDY:
			case TOK_CMP:
			case TOK_CPX:
			case TOK_CPY:
			case TOK_ADC:
			case TOK_AND:
			case TOK_ROR:
			case TOK_ROL:
			case TOK_ASL:
				{
					int op_type = 0, op1 = term(&op_type);
					if(op_type == TOK_HEX) {

						fprintf(fptr, "\n%s(_reg.memory_map[0x%x]);\n", op_array[op_code], op1);

					} else {
						fprintf(fptr, "\n%s(0x%x);\n", op_array[op_code], op1);
					}

				}
				break;
			case TOK_STA:
			case TOK_STY:
			case TOK_STX:
				{
					int op_type = 0, op1 = term(&op_type); 
					fprintf(fptr, "\n%s(0x%x);\n", op_array[op_code], op1);

				}
				break;
			case TOK_INT:
				{
					int op_type = 0, op1 = term(&op_type); 
					fprintf(fptr, "\n%sx(0x%x);\n", op_array[op_code], op1);
					break;
				}
			case TOK_BNE:
				{
					get_next();
					fprintf(fptr, "\nif(_reg.flags[6] == 1)\n");
					fprintf(fptr, "\ngoto %s;\n", lst->node->text);
				}
				break;
			case TOK_JMP:
				{
					get_next();
					fprintf(fptr,"\ngoto %s;\n", lst->node->text);
				}
				break;
			case TOK_JSR:
				{
					get_next();
					fprintf(fptr,"\ngoto %s;\n", lst->node->text);
					stack_push(&the_stack, lst);
				}
				break;
			case TOK_RTS:
				{
					struct sym_list *l = stack_pop(&the_stack);
					if(l) fprintf(fptr,"\ngoto %s\n", l->node->text);
				}
				break;
			case TOK_INX:
			case TOK_INY:
			case TOK_DEX:
			case TOK_DEY:
			case TOK_INC:
			case TOK_DEC:
				{
					fprintf(fptr,"\n%s();\n", op_array[lst->node->op_code]);
				}
				break;
			default:
				{
					if(lst && lst->node->type == TOK_CHAR) {
						fprintf(fptr, "\n%s:\n", lst->node->text);
					}
				}
				break;
				
		
		}

		get_next();

	}

	fprintf(fptr, "\nreturn 0;\n}\n");

	fclose(fptr);

}*/

void build_debug(const char *output) {

	struct sym_list *lst;
	FILE *fptr = fopen(output,"w");
	if(!fptr)
		return;

	fprintf(fptr, "<HTML> <TITLE> Atari 800 Debug Output </TITLE> <BR> ");
	fprintf(fptr, "<TABLE BORDER=2>");
	fprintf(fptr, "<TR> <TH> <b>Machine Instruction <TH> P-code <TH> Mnemoic <TH> Operand <TH> Address Mode</b></TR>");
	for(lst = symbols.node_list; lst != 0; lst = lst->next) {
		struct sym_list *prev = lst;
		if(lst->node->op_code != 0) {
			unsigned char op = 0;
			int address_mode = ABSOULTE;
			fprintf(fptr, "<TR>");
			// translate p-code to machine instruction
			op = get_machine_opcode(lst, &address_mode );
			fprintf(fptr, "<TH> 0x%x", op); // for now
			fprintf(fptr, "<TH> 0x%x ", lst->node->op_code);
			fprintf(fptr, "<TH> %s ", lst->node->text);
			lst = lst->next;
			if(lst && lst->node->op_code == 0)
			fprintf(fptr, "<TH> %s ", lst->node->text);
			else { 
				fprintf(fptr, "<TH> no operand ");
				lst = prev;
			}
			fprintf(fptr, "<TH> %s", trans_admode(&address_mode));
			fprintf(fptr, "</TR>");
		}
		
	}
	fprintf(fptr,"</TABLE>");
	fprintf(fptr, "<BR></HTML>");

	fclose(fptr);
}


unsigned char set_bit(unsigned char bits, unsigned char which) {
	bits |= (1 << which);
	return bits;
}
unsigned char clr_bit(unsigned char bits, unsigned char which) {
	bits &= (1 << which);
	return bits;
}
unsigned char get_bit(unsigned char bits, unsigned char which) {
	return (bits & (1UL << which)) == 0 ? 0 : 1;
}

struct call_back *callbacks = 0;
int cp = 0;

void set_callback(struct call_back *c) {
	callbacks = c;
}

struct call_back *get_callback(unsigned int address) {
	int i;
	struct call_back *callback = callbacks;
	for(i = 0; callback != 0; callback++)
		if(callbacks->address == address)
			return callbacks;
	return 0;
}
// it dont come easy you know it dont come easy 