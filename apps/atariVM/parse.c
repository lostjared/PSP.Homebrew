#include"parse.h"
#include <SDL_mxf.h>
#include "platform.h"

void statement();
void asn(struct sym_list *lst);
int term(int *type);
void factor(struct sym_list *lst);

struct sym_list *lst = 0; // pointer to current item in chain 

void getnext();
int do_interupt(int);

#define map_size 0xFFFFF

typedef struct reg {
	unsigned char ldx,ldy;// X, Y registers
	int accum; // accumulator (A register)
	unsigned char flags[9]; // processcor status register (flags)
	/*
	0 = Negative Result Flag
	1 = Overflow Flag
	2 = Expansion Flag (Not Labeled)
	3 = Break Command Flag
	4 = Decimal Mode Flag
	5 = Intereupt disable flag
	6 = Zero result flag
	7 = Carry Flag
	*/
	int stack_pointer; // stack pointer register
	int address;// address mode (absoulte/zero page/ etc.)
	unsigned char memory_map[map_size];// memory map 
};

struct reg _reg;
int debug_mode = 0;
struct SDL_Font *the_font = 0;
int active = 0;
SDL_Surface *front = 0;

void dump_reg() {
	int i;
	printf("*********************************************************\n");
	printf("REGISTERS:\n");
	printf("Address Mode = %x Accumulator (Dec/Hex) = %d/%x\n", _reg.address, _reg.accum,(unsigned char)_reg.accum);
	printf("X = %x, Y = %x\n", _reg.ldx, _reg.ldy);
	printf("flags={");
	for(i = 0; i < 8; i++)
		printf("%x%s ", _reg.flags[i], (i <= 6) ? "," : "");
	printf("}");
	// dump memory map to stdout
	printf("\n*********************************************************\n");
}

void draw_debug(SDL_Surface *surf) {
	if(active == 1 && debug_mode == 2) {
		char buf[256];
		SDL_Rect rc = { 260, 100, 50, 50 };
		SDL_FillRect(surf, &rc, 0);
		sprintf(buf,"X = %x , Y = %x , A = %x\n Instruction: %s ", _reg.ldx, _reg.ldy, _reg.accum, lst->node->text);
		SDL_PrintText(surf, the_font, 260, 100, SDL_MapRGB(surf->format, 255, 255, 255), buf);
	}
}

void parse() {

	int add, val;
	lst = symbols.node_list;
	memset(&_reg, 0, sizeof(_reg));
	// proccess address mode
	if(lst->node->type == TOK_ADMODE) {

		while(lst && lst->node->type != TOK_HEX) {
			getnext();
		}
		if(lst) {
			sscanf(lst->node->text, "%x", &_reg.address);
			getnext();
		}
	}

	stack_init(&the_stack);
	int_stack_init(&int_stack);

	statement(lst);
	if(debug_mode == 1 || debug_mode == 2) {
		int i;
		dump_reg();
		printf("MEMORY MAP:\n");
		for(i = 0; i < map_size; i++) {
			if(_reg.memory_map[i] != 0)
				printf("\nmemory @ %x = %x\n", i, (unsigned char)_reg.memory_map[i]);
		}
	}
}

unsigned long trans_color(SDL_Surface *surface, unsigned char color) {

	unsigned char r[3] = { get_bit(color, 1), get_bit(color, 2) };
	unsigned char g[3] = { get_bit(color, 3), get_bit(color, 4) };
	unsigned char b[3] = { get_bit(color, 5), get_bit(color, 6) };

	if(r[0] == 1 && r[1] == 0) 
		r[2] = 255/2;
	if(r[0] == 1 && r[1] == 1)
		r[2] = 255;
	if(r[0] == 0 && r[1] == 1)
		r[2] = 255/3;

	if(g[0] == 1 && g[1] == 0) 
		g[2] = 255/2;
	if(g[0] == 1 && g[1] == 1)
		g[2] = 255;
	if(g[0] == 0 && g[1] == 1)
		g[2] = 255/3;
	if(b[0] == 1 && b[1] == 0) 
		b[2] = 255/2;
	if(b[0] == 1 && b[1] == 1)
		b[2] = 255;
	if(b[0] == 0 && b[1] == 1)
		b[2] = 255/3;

	return SDL_MapRGB(surface->format,r[2],g[2],b[2] );
}




void getnext() {
	if(lst) lst = lst->next;
}

SDL_Joystick *joy = 0;

void do_quit() {
	do_interupt(0x0);
}

SDL_Surface *surf = 0;
SDL_Event   e;


 int key_offset = 0xFE01;
 int memory_offset = 0x0;

int do_interupt(int interupt) {

	

	
	switch(interupt) {
		case 0x0:
			{
				_reg.ldx = 0;
				if(surf) {
					SDL_FreeSurface(surf);
					surf = 0;
				}
				if(the_font) {
					SDL_FreeFont(the_font);
					the_font = 0;
				}

				active = 0;
				SDL_Quit();
				return 1;
			}
			break;
		case 0x1: // Print Memory locations X-Y
			{
				int i = 0;
				for(i = _reg.ldx; i <= _reg.ldy; i++) 
					printf("%c", _reg.memory_map[i]);

			}
			break;
		case 0x2:// get string from stdin
			{
				unsigned int i = 0;
				char buff[256];

				scanf("%s", buff);
				for(i = 0; i < strlen(buff); i++) 
					_reg.memory_map[_reg.ldx+i] = buff[i];
				
				_reg.ldy = _reg.ldx+(unsigned char)strlen(buff);
				
			}
			break;
		case 0x3:// Get from stdin
			{
				unsigned char c =  0;
				scanf("%d", &c);
				_reg.memory_map[_reg.ldx] = c;
			}
			break;
		case 0x4:// Get from Stdin
			{
				unsigned char c = 0;
				scanf("%x", &c);
				_reg.memory_map[_reg.ldx] = c;
			}
			break;
		case 0x13: // Set Video Mode
			{
				if(surf == 0) {


#ifndef FOR_PSP
				SDL_WM_SetCaption("Atari VM",  0);
				SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), 0);
#endif

				surf = SDL_SetVideoMode(480,272,0,0);
				the_font = SDL_InitFont("t.mxf");
				joy = SDL_JoystickOpen(0);
				SDL_JoystickEventState(SDL_ENABLE);
				SDL_FillRect(surf, 0,0);
				SDL_PrintText(surf, the_font, 0,0,SDL_MapRGB(surf->format, 255, 255, 255), "Loading...");
				SDL_UpdateRect(surf, 0, 0, 480, 272);

				}
				
				if(!surf) { _reg.ldx = 0; return 1; }

				active = 1;
			}
			break;
		case 0x14: // PollEvent
			{
				if(!active) return 0;

				if(SDL_PollEvent(&e)) {
					switch(e.type) 
					{
					case SDL_QUIT:
						{
							do_interupt(0x0);
							return 1;
						}
						break;
					case SDL_KEYDOWN:
						{
							_reg.memory_map[key_offset+e.key.keysym.sym] = 0x1;
						}
						break;
					case SDL_KEYUP:
						{
							_reg.memory_map[key_offset+e.key.keysym.sym] = 0x0;
						}
						break;
					case SDL_JOYBUTTONDOWN:
						{
							_reg.memory_map[key_offset+e.jbutton.button] = 0x1;
						}
						break;
					case SDL_JOYBUTTONUP:
						{
							_reg.memory_map[key_offset+e.jbutton.button] = 0x0;
						}
						break;
					}
				}

			}
			break;
		case 0x15: // update surface with data at locations 0x0-0x1FE00
		case 0x20: // draw debug info
			{
				int i = 0,z = 0;
				void *buf;
				buf = lock(surf, surf->format->BitsPerPixel);
				
				
				for(i = 0; i < 0xFF; i++)
					for(z = 0; z < 0xFF; z++)
					{
						unsigned char color = 0;
						unsigned long final_color = 0;
						
						int pos = 0;
						pos = z*480+i;
						if(pos >= 0 && pos < map_size)
						 color = _reg.memory_map[pos];
						else
						 color = 0;

						if(color != 0)
						{
							final_color = trans_color(surf,color);
						}
						setpixel(buf,i,z,final_color,surf->format->BitsPerPixel, surf->pitch);
					}
				unlock(surf);
			//	draw_debug(surf);
				SDL_UpdateRect(surf, 0,0,480,272);
			}
			break;
		case 0x16: // set a pixel in the virtual machines memory
			{

				int pos = 0;
				pos = _reg.ldy*480+_reg.ldx;
				if(pos > 0 && pos < map_size)
				_reg.memory_map[(_reg.ldy*480+_reg.ldx)] = _reg.accum;
			}
			break;
		case 0x17: // fill accumulator with random value
			{
				_reg.accum = rand()%255;
			}
			break;
		case 0x18:// fill accumulator with random value from Range X-Y
			{
				_reg.accum = _reg.ldx+(rand()%_reg.ldy);
			}
			break;
		case 0x19: // Test key value in Y put value in Y
			{
				if(_reg.memory_map[key_offset+_reg.ldy] == 1) {
					_reg.ldy = 1;
				}
				else 
					_reg.ldy = 0;
		 	}
			break;
		case 0x56:
			{
				return 0;
				if(active == 1) {
					int i, pos = 0;
					char buffer[256];
					for(i = _reg.ldx; i < _reg.ldy; i++)
					{
						buffer[pos++] = _reg.memory_map[i+_reg.accum];
					}
					buffer[pos] = 0;
					SDL_PrintText(surf, the_font, _reg.memory_map[0xFFE13]+_reg.accum, _reg.memory_map[0xFFE14]+_reg.accum, trans_color(surf, _reg.memory_map[0x1299]), buffer);

					}
			}
			break;
		case 0x57: // call back
			{
				struct call_back *b = get_callback(_reg.ldx);
				if(b)
				b->func();

			}
			break;
		case 0x58:
			{
				if(active == 1) {
					char buf[0xFF];
					sprintf(buf, "%d", _reg.memory_map[0xFFE17]);
					SDL_PrintText(surf, the_font, _reg.ldx+_reg.accum, _reg.ldy,trans_color(surf, _reg.memory_map[0xFFE15]), buf);
				}
			}
			break;
		case 0x100:
			{
				_reg.accum = _reg.memory_map[_reg.accum];

			}
			break;
		case 0x101:
			{
				_reg.memory_map[_reg.ldx+_reg.ldy] = _reg.accum;
			}
			break;
		case 0x102:
			{
				if(_reg.memory_map[_reg.ldx+_reg.ldy] == 0xF)
					_reg.flags[6] = 0;
				else
					_reg.flags[6] = 1;
			}
			break;
		case 0x103:
			{
				
				memset(_reg.memory_map, 0, ( surf->w * surf->h )/sizeof(int));
				SDL_FillRect(surf, 0, 0);

			}
			break;
	}

	return 0;
}

void do_init() {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		_reg.ldx = 1;
	}
	else _reg.ldx = 0;
	do_interupt(0x13);
}



unsigned char do_asl(unsigned char c) {
	return c << 1;
}

unsigned char do_ror(unsigned char c) {
	unsigned char values[8],t;
	int i;
	for(i = 1; i <= 8; i++)
		values[i-1] = get_bit(c, i);
	
	t = values[7];
	values[7] = values[0];
	values[0] = values[1];
	values[1] = values[2];
	values[2] = values[3];
	values[3] = values[4];
	values[5] = values[6];
	values[6] = t;
	c = 0;
	for(i = 1; i <= 8; i++)
		c = set_bit(c, values[i-1]);
	return c;
}

unsigned char do_rol(unsigned char c) {
		unsigned char values[8],t;
	int i;
	for(i = 1; i <= 8; i++)
		values[i-1] = get_bit(c, i);
	
	t = values[0];

	values[0] = values[7];
	values[1] = values[0];
	values[2] = values[1];
	values[3] = values[2];
	values[4] = values[3];
	values[5] = values[6];
	values[7] = t;
	c = 0;
	for(i = 1; i <= 8; i++)
		c = set_bit(c, values[i-1]);

	return c;
}


void statement() {

	char op_code = 0;

	while(lst != 0) {

		if(lst)
			op_code = lst->node->op_code;
		else
			return;

		if(lst->node->type == TOK_CHAR && op_code == 0) { // proccess code label
			getnext();
			if(!lst)
				return;
		}

	
		if(op_code)
		switch(lst->node->op_code) { // proccess opcode and its operands
		case TOK_ID:
		case TOK_BRK:// exit the program
			{
				do_interupt(0x0);
				return;
			}
			break;
		case TOK_INT: // New instruction Interupt
			{
				int op_type = 0, op1 = term(&op_type);
				if(do_interupt(op1) != 0)
					return;
			}
			break;
		case TOK_JSR: // Jump to subroutine , save address
			{
				struct sym_list *lst_pointer = 0;
				getnext();
				lst_pointer = sym_list_look(&symbols, symbols.node_list, lst->node->text);
				if(lst_pointer)
				{

					stack_push(&the_stack, lst);
					lst = lst_pointer;
					continue;
				}
				
			}
			break;
		case TOK_RTS:
			{
				struct sym_list *lst_pointer = 0;
				lst_pointer = stack_pop(&the_stack);
				if(lst_pointer) {
					lst = lst_pointer;
				} else getnext();
			}
			break;
		case TOK_SEI:// set interupt flag
			{
				_reg.flags[5] = 1;
				getnext();
			}
			break;
		case TOK_SEC:// Set carry falg
			{
				_reg.flags[7] = 1;
				getnext();
			}
			break;
		case TOK_CLC: // Clear Carry Flag
			{
				_reg.flags[7] = 0;
				getnext();
			}
			break;
		case TOK_CLI: // Clear intereupt flag
			{
				_reg.flags[5] = 0;
				getnext();

			}
			break;
		case TOK_CLV:// clear overflow flag
			{
				_reg.flags[1] = 0;
				getnext();
			}
			break;
		case TOK_LDX:// Load Accumulator into Register LDX, from memory or constant
			{
				int op_type = 0, op1 = term(&op_type);
				if(op_type == TOK_NUMERIC || op_type == TOK_REGISTER) {
					_reg.ldx = op1;
				}
				else if(op_type == TOK_HEX) {
					_reg.ldx = _reg.memory_map[op1];
				}
			}
			break;
		case TOK_LDY:
			{
				int op_type = 0, op1 = term(&op_type);
				if(op_type == TOK_NUMERIC || op_type == TOK_REGISTER)
					_reg.ldy = op1;
				else
					_reg.ldy = _reg.memory_map[op1];
			}
			break;
		case TOK_LDA: // Load Accumulator from memory
			{
				int op_type = 0;
				int op1 = term(&op_type);
				if(op_type == TOK_HEX) {
					if(_reg.accum >= 0xFF) _reg.accum = 0xFF;
					_reg.accum = _reg.memory_map[op1];
				} else if(op_type == TOK_NUMERIC || op_type == TOK_REGISTER) {
					if(_reg.accum >= 0xFF) _reg.accum = 0xFF;
					_reg.accum = op1;
				}
			}
			break;
		case TOK_ADC: // Add Accumulator to Address/Constant with Carry Flag (Based off Decimal Flag) 
		case TOK_SBC: // Sub Accumulator to Address/Constant with Carry Flag (Based off Decimal Flag)
		case TOK_AND: // And Accumulator to Address/Constant with Carry Flag (Based off Decimal Flag)
		case TOK_EOR: // Exculsive Or Accumulator 
		case TOK_ORA: // Or Memory with Accumulator
		case TOK_ASL: // Shift Left One Bit
		case TOK_ROR: // Rotate Right One Bit
		case TOK_ROL: // Rotate Left one bit
		case TOK_LSR:
			{
				if(_reg.flags[4] == 0) { // if decmial mode flag is not set
					int op_type = 0, op1 = term(&op_type);
					if(op_type == TOK_HEX || op_type == TOK_REGISTER) {
						if(op_code == TOK_ADC || op_code == TOK_SBC) // Add/Subtract 
						_reg.accum += (op_code == TOK_SBC) ? -_reg.memory_map[op1] : _reg.memory_map[op1];
						else if(op_code == TOK_AND)  // And 
							_reg.accum = _reg.accum & _reg.memory_map[op1];
						else if(op_code == TOK_EOR)
							_reg.accum = _reg.accum ^ _reg.memory_map[op1];
						else if(op_code == TOK_ORA)
							_reg.accum = _reg.accum | _reg.memory_map[op1];
						else if(op_code == TOK_ASL)
							_reg.memory_map[op1] = do_asl(_reg.memory_map[op1]);
						else if(op_code == TOK_ROR)
							_reg.memory_map[op1] = do_ror(_reg.memory_map[op1]);
						else if(op_code == TOK_ROL)
							_reg.memory_map[op1] = do_rol(_reg.memory_map[op1]);
						else if(op_code == TOK_LSR)
							_reg.memory_map[op1] = _reg.memory_map[op1] >> 1;


						// other instructions
						if(_reg.accum > 0xFF) {
							_reg.accum = 0;
							_reg.flags[7] = 1;
						}

					}
					else if(op_type == TOK_NUMERIC) {

						if(op_code == TOK_SBC || op_code == TOK_ADC)
						_reg.accum += (op_code == TOK_SBC) ? -op1 : op1;
						else if(op_code == TOK_AND) 
							_reg.accum = _reg.accum & op1;
						else if(op_code == TOK_EOR)
							_reg.accum = _reg.accum ^ op1;
						else if(op_code == TOK_ORA)
							_reg.accum = _reg.accum | op1;
						else if(op_code == TOK_ASL)
							_reg.accum = do_asl(_reg.accum);
						else if(op_code == TOK_ROR)
							_reg.accum = do_ror(_reg.accum);
						else if(op_code == TOK_ROL)
							_reg.accum = do_rol(_reg.accum);
						else if(op_code == TOK_LSR)
							_reg.accum = _reg.accum >> 1;

						if(_reg.accum > 0xFF)
						{
							_reg.accum = 0x0;
							_reg.flags[7] = 1;
						}

					}
				}
				else if(_reg.flags[4] == 1) {
					int op_type = 0, op1 = term(&op_type);
					if(op_type == TOK_HEX || op_type == TOK_REGISTER) {
						if(op_code == TOK_ADC || op_code == TOK_SBC)
						_reg.accum += (op_code == TOK_SBC) ? -_reg.memory_map[op1] : _reg.memory_map[op1];
						else if(op_code == TOK_AND)
							_reg.accum = _reg.accum & _reg.memory_map[op1];
						else if(op_code == TOK_EOR)
							_reg.accum = _reg.accum ^ _reg.memory_map[op1];
						else if(op_code == TOK_ORA)
							_reg.accum = _reg.accum | _reg.memory_map[op1];
						else if(op_code == TOK_ASL)
							_reg.memory_map[op1] = do_asl(_reg.memory_map[op1]);
						else if(op_code == TOK_ROR)
							_reg.memory_map[op1] = do_ror(_reg.memory_map[op1]);
						else if(op_code == TOK_ROL)
							_reg.memory_map[op1] = do_rol(_reg.memory_map[op1]);
						else if(op_code == TOK_LSR)
							_reg.memory_map[op1] = _reg.memory_map[op1] >> 1;

						if(_reg.accum > 127) {
							_reg.accum = -128;
							_reg.flags[7] = 1;
							_reg.flags[0] = 1;
						}
						else if(_reg.accum < -127) {
							_reg.accum = 128;
							_reg.flags[7] = 1;
							_reg.flags[0] = 0;
						} 
						else if(_reg.accum > 0)
							_reg.flags[0] = 0;
						else if(_reg.accum < 0)
							_reg.flags[0] = 1;

					} else if(op_type == TOK_NUMERIC) {
						if(op_code == TOK_SBC || op_code == TOK_ADC)
						_reg.accum += (op_code == TOK_SBC) ? -op1:op1;
						else if(op_code == TOK_AND)
							_reg.accum = _reg.accum & op1;
						else if(op_code == TOK_EOR)
							_reg.accum = _reg.accum ^ op1;
						else if(op_code == TOK_ORA)
							_reg.accum = _reg.accum | op1;
						else if(op_code == TOK_ASL)
							_reg.accum = do_asl(_reg.accum);
						else if(op_code == TOK_ROR)
							_reg.accum = do_ror(_reg.accum);
						else if(op_code == TOK_ROL)
							_reg.accum = do_rol(_reg.accum);
						else if(op_code == TOK_LSR)
							_reg.accum = _reg.accum >> 1;

						if(_reg.accum > 127) {
							_reg.accum = -128;
							_reg.flags[7] = 1;
							_reg.flags[0] = 1;
						}
						else if(_reg.accum < -127) {
							_reg.accum = 128;
							_reg.flags[7] = 1;
							_reg.flags[0] = 0;
							
						} else if(_reg.accum > 0)
							_reg.flags[0] = 0;
						else if(_reg.accum < 0)
							_reg.flags[0] = 1;
					}
				}

			}
			break;
		case TOK_STA:// Store accumulator in memory
			{
				int op_type = 0;
				int op1 = term(&op_type);
				if(op_type == TOK_HEX || op_type == TOK_REGISTER) {
					if(_reg.accum >= 0xFF) _reg.accum = 0xFF;
					_reg.memory_map[op1] = _reg.accum;
				}
			}
			break;
		case TOK_STY:// Store Y register in memory
			{
				int op_type = 0;
				int op1 = term(&op_type);
				if(op_type == TOK_HEX || op_type == TOK_REGISTER || op_type == TOK_NUMERIC) {
					_reg.memory_map[op1] = _reg.ldy;
				}

			}
			break;
		case TOK_STX:// Store X register in memory
			{
				int op_type = 0;
				int op1 = term(&op_type);
				if(op_type == TOK_HEX || op_type == TOK_REGISTER || op_type == TOK_NUMERIC) {
					_reg.memory_map[op1] = _reg.ldx;
				}
			}
			break;
		case TOK_TAX:// transfer accumulator to register X
			{
				_reg.ldx = _reg.accum;
				getnext();
			}
			break;
		case TOK_TAY:// transfer accumulator to register Y
			{
				_reg.ldy = _reg.accum;
				getnext();
			}
			break;
		case TOK_INX:// Increment register X
			{
				_reg.ldx++;
				getnext();
			}
			break;
		case TOK_INY: // Increment register Y
			{
				_reg.ldy++;
				getnext();
			}
			break;
		case TOK_DEX: // Decrement register X
			{
				_reg.ldx--;
				getnext();
			}
			break;
		case TOK_DEY:
			{
				_reg.ldy--;
				getnext();
			}
			break;
		case TOK_CPX: // Compare value in register X 
		case TOK_CPY: // Compare value in register Y
			{
				int op_type = 0;
				int op1 = term(&op_type);
				if(op_type == TOK_HEX) {
					if(op_code == TOK_CPX) {
						if(_reg.memory_map[op1] == _reg.ldx)
							_reg.flags[6] = 0;
						else 
							_reg.flags[6] = 1;
					}
					else {
						if(_reg.ldy == _reg.memory_map[op1])
							_reg.flags[6] = 0;
						else
							_reg.flags[6] = 1;
					}


				} else if(op_type == TOK_NUMERIC || op_type == TOK_REGISTER) {
					if(op_code == TOK_CPX) {
						if(_reg.ldx == op1)
						{
							_reg.flags[6] = 0;
						}
						else _reg.flags[6] = 1;
					} else {
						if(_reg.ldy == op1) _reg.flags[6] = 0;
						else _reg.flags[6] = 1;
					}
				} 

			}
			break;
		case TOK_CLD: // Clear Decimal Mode
			{
				_reg.flags[4] = 0;
				getnext();
			}
			break;
		case TOK_SED:// Set Decimal Mode
			{
				_reg.flags[4] = 1;
				getnext();
			}
			break;
		case TOK_CMP:// Compare Accumulator with Address/Constant
			{
				int op_type = 0, op_code = term(&op_type);
				if(op_type == TOK_HEX || op_type == TOK_REGISTER) {
					int value1 = _reg.memory_map[op_code];
					_reg.flags[6] = (value1 == _reg.accum) ? 0 : 1;


				} else if(op_type == TOK_NUMERIC) {
					_reg.flags[6] = (op_code == _reg.accum) ? 0 : 1;
				}
			}
			break;
		case TOK_BNE: // branch if flags register (zero flag) is equal to 1
			{
				if(_reg.flags[6] == 1) {
					struct sym_list *lst_pointer = 0;
					getnext();
					// lst = pointer to position in parse chain
					lst_pointer = sym_list_look(&symbols, symbols.node_list, lst->node->text);
					if(lst_pointer)
						lst = lst_pointer;
					getnext();
				} else getnext();

			}
			break;
		case TOK_BEQ:// branch if flags register ( zero flag ) is equal to 0
			{
				if(_reg.flags[6] == 0) {
					struct sym_list *lst_pointer = 0;
					getnext();
					lst_pointer = sym_list_look(&symbols, symbols.node_list, lst->node->text);
					if(lst_pointer)
						lst = lst_pointer;
					getnext();
				}
				else getnext();
			}
			break;
		case TOK_BCS:// Branch if Carry set
			{
				if(_reg.flags[7] == 1) {
					struct sym_list *lst_pointer = 0;
					getnext();
					lst_pointer = sym_list_look(&symbols, symbols.node_list, lst->node->text);
					if(lst_pointer)
						lst = lst_pointer;
					getnext();
				} else getnext();
			}
			break;
		case TOK_BCC:
			{
				if(_reg.flags[7] == 0) {

					struct sym_list *lst_pointer = 0;
					getnext();
					lst_pointer = sym_list_look(&symbols, symbols.node_list, lst->node->text);
					if(lst_pointer)
						lst = lst_pointer;
					getnext();
				}
				else getnext();
			}
			break;
		case TOK_BVC: // Branch if Overflow flag is clear
			{
				if(_reg.flags[1] == 0) {
					struct sym_list *lst_pointer = 0;
					getnext();
					lst_pointer = sym_list_look(&symbols, symbols.node_list, lst->node->text);
					if(lst_pointer)
						lst = lst_pointer;
					getnext();
				}
				else getnext();
			}
			break;
		case TOK_BVS:// Branch if Overflow flag is set
			{
				if(_reg.flags[1] == 1) {
					struct sym_list *lst_pointer = 0;
					getnext();
					lst_pointer = sym_list_look(&symbols, symbols.node_list, lst->node->text);
					if(lst_pointer)
						lst = lst_pointer;
					getnext();
				}
				else getnext();
			}
			break;
		case TOK_JMP: // unconditional jump to code label
			{
				struct sym_list *lst_pointer = 0;
				getnext();
				lst_pointer = sym_list_look(&symbols, symbols.node_list, lst->node->text);
				if(lst_pointer)
					lst = lst_pointer;
				getnext();

			}
			break;
		case TOK_BMI:// branch if Negative Flag is equal to 1
			{
				if(_reg.flags[0] == 1) {
					struct sym_list *lst_pointer = 0;
					getnext();
					lst_pointer = sym_list_look(&symbols, symbols.node_list, lst->node->text);
					if(lst_pointer)
						lst = lst_pointer;
					getnext();
				}
				else getnext();
			}
			break;
		case TOK_BPL: // branch if Negative Flag is equal to 0
			{
				if(_reg.flags[0] == 0) {
					struct sym_list *lst_pointer = 0;
					getnext();
					lst_pointer = sym_list_look(&symbols, symbols.node_list, lst->node->text);
					if(lst_pointer)
						lst = lst_pointer;

					getnext();
				}
				else getnext();
				
			}
			break;
		case TOK_PHP:
			{
				int i;
				for(i = 0; i <= 8; i++)
				int_stack_push(&int_stack, _reg.flags[i]);
				getnext();
			}
			break;
		case TOK_PLP:
			{
				int i;
				for(i = 8; i <= 0; i++)
					_reg.flags[i] = int_stack_pop(&int_stack);
				getnext();
			}
			break;
		case TOK_PHA:
			{
				int_stack_push(&int_stack, _reg.accum);
				getnext();

			}
			break;
		case TOK_PLA:
			{
				_reg.accum = int_stack_pop(&int_stack);
				getnext();
			}
			break;
		case TOK_NOP:
			{
				if(debug_mode == 1 || debug_mode == 2)
				{
					dump_reg();
					system("pause");
				}
				getnext();
			}
			break;
		case TOK_LDM:
			{
				size_t i;
				getnext();
				for(i = 0;i < strlen(lst->node->text); i++) {
					_reg.memory_map[_reg.accum+i] = lst->node->text[i];
				}
				_reg.ldy = strlen(lst->node->text);
				getnext();
			}
			break;
		default:
			getnext();
		}

	}

}

void asn(struct sym_list *lst) {



}

int term(int *type) {

	int value = 0;
	do {
		getnext();
		if(lst)
			*type = lst->node->type;
	} while (lst && lst->node->type != TOK_HEX && lst->node->type != TOK_NUMERIC && lst->node->text[0] != 'A' && lst->node->text[0] != 'X' && lst->node->text[0] != 'Y');



	if(*type == TOK_HEX) {

		sscanf(lst->node->text, "%x", &value);
		getnext();
		return value;

	} 
	else if (*type == TOK_NUMERIC)
	{
		if(lst->node->text[0] == '$') {
			char *buf = lst->node->text+1;
			sscanf(buf, "%x", &value);
		}
		else value = atoi(lst->node->text);
		getnext();
		return value;
	}
	else if(*type == TOK_CHAR) {
		*type = TOK_REGISTER;
		if(lst->node->text[0] == 'A') {
			getnext();
			return _reg.accum;
		}
		if(lst->node->text[0] == 'X') {
			getnext();
			return _reg.ldx;
		}
		if(lst->node->text[0] == 'Y') {
			getnext();
			return _reg.ldy;
		}
	}

	return 0;
}

void factor(struct sym_list *lst) {

}

// just running down a dream - Tom petty
