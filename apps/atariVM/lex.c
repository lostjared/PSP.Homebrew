#include "lex.h"
#include "program.h"

char token_map[256];
struct token cur_token;
int cur_line = 0, cur_pos = 0;
struct sym_table symbols;

void init_map() {
	char i = 0;
	for(i = 0; i < 127; i++)
		token_map[i] = TOK_NULL;
	for(i = 'a'; i <= 'z'; i++)
		token_map[i] = TOK_CHAR;
	for(i = 'A'; i <= 'Z'; i++)
		token_map[i] = TOK_CHAR;
	for(i = '0'; i <= '9'; i++)
		token_map[i] = TOK_DIGIT;
	token_map['<'] = token_map['.'] = TOK_SYMBOL;
	token_map['{'] = TOK_OBRACE, token_map['}'] = TOK_CBRACE;
	token_map['\"'] = token_map['\''] = TOK_QUOTE;
	token_map[','] = TOK_COMMA, token_map[';'] = TOK_SEMI;
	token_map['('] = TOK_OPARAM, token_map[')'] = TOK_CPARAM;
	token_map['$'] = TOK_ADDRESS, token_map['#'] = TOK_NUMERIC;
	token_map['*'] = token_map['='] = TOK_ADMODE;
}

int mlex_init_file(struct file_buffer *buf, const char *src) {

	init_map();
#ifndef COMPILE_EBOOT
	buf->fptr = fopen(src,"r");
	if(!buf->fptr)
		return -1;
#else
	buf->fptr = 0;
#endif
	buf->cpos = 0;
	buf->cline = 0;
	return 1;
}
int mlex_close(struct file_buffer *buf) {
	if(buf->fptr != 0)
		fclose(buf->fptr);
	return 0;
}
#ifndef COMPILE_EBOOT
char mlex_getc(struct file_buffer *buf) {
	char c = fgetc(buf->fptr);
	if(c == '\n') 
	{
		cur_line++;
		cur_pos = 0;
	}
	else cur_pos++;
	return c;
}
#else
static int array_pos = 0;

char mlex_getc(struct file_buffer *buf) {
	char c = -1;
	if(array_pos <= array_length && array[array_pos] != 0) {
		 c = array[array_pos++];
		if(c == '\n')
		{
			cur_line++;
			cur_pos = 0;
		}
		else cur_pos++;

		return c;
	}
	array_pos++;
	return c;
}

#endif
char slash_sequence(char c) {
	switch(c) {
		case 'n':
			return '\n';
		case 't':
			return '\t';
		case '0':
			return '\0';
		case '\'':
			return '\'';
		case '\"':
			return '\"';
	}

	return 0;
}


int fpeek(FILE *ptr) {
	char c;
	c = fgetc(ptr);
	ungetc(c,ptr);
	return c;
}

void addchr(char c) {
	cur_token.tok[0] = c;
	cur_token.tok[1] = 0;
}



void mlex_gettoken(struct file_buffer *buf) {

	size_t pos = 0;
	static int scope = 0;

		char c = mlex_getc(buf);
		if(c == -1)
		{
			cur_token.type = TOK_NULL;
			return;
		}
		memset(&cur_token, 0, sizeof(cur_token));
		cur_token.i = cur_pos;
		cur_token.z = cur_line;
		switch(token_map[c]) {
			case TOK_SEMI:
				{
					while( (c = mlex_getc(buf) ) != '\n' );
					mlex_gettoken(buf);
					return;
				}
				break;
			case TOK_CHAR:
			case TOK_DIGIT:
			case TOK_SYMBOL:
			case TOK_OBRACE:
			case TOK_CBRACE:
			case TOK_COMMA:
			case TOK_OPARAM:
			case TOK_CPARAM:
			case TOK_NUMERIC:
			case TOK_ADMODE:
			case TOK_ADDRESS:
				{
					int hex_ok = 1;
					cur_token.type = token_map[c];
					if(cur_token.type == TOK_ADDRESS) {
						cur_token.type = TOK_HEX;
						while( (c = mlex_getc(buf)) && (token_map[c] == TOK_CHAR || token_map[c] == TOK_DIGIT)) {
							cur_token.tok[pos++] = c;
							cur_token.tok[pos] = 0;
						}
						mlex_addtoken();
						return;
					}
					else if(cur_token.type == TOK_NUMERIC) {

						while (( (c = mlex_getc(buf)) ) && (token_map[c] == TOK_CHAR || token_map[c] == TOK_DIGIT || token_map[c] == TOK_ADDRESS)) {
							cur_token.tok[pos++] = c;
							cur_token.tok[pos] = 0;
						}
						mlex_addtoken();
						return;
					}
					if(c == '{') scope++;
					if(c == '}') scope--;
					cur_token.scope = scope;

					do {
						cur_token.tok[pos++] = c;
						cur_token.tok[pos] = 0;

					} while ( (c = mlex_getc(buf)) &&  token_map[c] == cur_token.type);
					mlex_addtoken();
#ifndef COMPILE_EBOOT
					ungetc(c,buf->fptr);
#else
					array_pos--;
#endif

					return;
				}
			case TOK_QUOTE:
				{
					char pc = c;
					cur_token.type = token_map[c];
					
					while((c = mlex_getc(buf))) {
						if(token_map[c] == TOK_QUOTE) {
							
							if(pc == '\\' && compile == 0) {
								if(pos-1 > 0) 
									cur_token.tok[pos-1] = compile == 0 ? slash_sequence(c) : c;
								continue;
							}
							else
								break;
						}
						else if( c == '\\') {
							if(compile == 1) cur_token.tok[pos++] = c;
							c = mlex_getc(buf);
							cur_token.tok[pos++] = compile == 0 ? slash_sequence(c) : c;
							cur_token.tok[pos] = 0;
						}
						else {
							cur_token.tok[pos++] = c;
							cur_token.tok[pos] = 0;
						}

						pc = c;
					}	

					mlex_addtoken();
				}
				break;
			default:
				mlex_gettoken(buf);
		}
}

void mlex_addtoken() {
	if(cur_token.type != TOK_NULL) {
		sym_add(&symbols, cur_token.tok, cur_token.type, cur_token.i, cur_token.z, cur_token.scope);
	}
}

void mlex_anaylize(struct file_buffer *buf) {


	sym_init(&symbols);
	do {
	
		mlex_gettoken(buf);
	} while ( cur_token.type != TOK_NULL );

	mlex_close(buf);
	
	parse();
	//build_icode("program.atari");
	if(debug_mode == 1) {
		build_debug("debug.html");
		sym_print(&symbols);
	} else if ( debug_mode == 2 ) {
		build_debug("debug.html");
	}
	sym_free(&symbols);
}