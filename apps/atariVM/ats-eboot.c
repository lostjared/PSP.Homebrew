#include<stdio.h>

void do_trans(char *source, char *out) {
	FILE *fptr = fopen(source, "r");
	FILE *optr = fopen(out,"w");
	size_t counter = 0;
	if(!fptr || !optr)
		return;

	fprintf(optr, "#ifndef COMPILE_EBOOT\n");
	fprintf(optr, "#define COMPILE_EBOOT\n");
	fprintf(optr, "static char array[] = {");

	while(!feof(fptr)) {

		char c = fgetc(fptr);
		if(c != -1)
		fprintf(optr, "0x%x, ", c);
		counter++;
	}
	
	fprintf(optr, " 0 }; \n");
	fprintf(optr, "int array_length = 0x%x;\n", counter-1);
	fprintf(optr, "#endif");
	fclose(fptr);
	fclose(optr);

}

int main(int argc, char **argv) {

	if(argc == 3)
		do_trans(argv[1],argv[2]);

	return 0;
}