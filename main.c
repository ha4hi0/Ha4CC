#include "Ha4CC.h"

void DOKO(int i)
{
	fprintf(stderr, "DOKO%d\n", i);
}

int main(int argc, char **argv){
	if(argc != 2){
		fprintf(stderr, "Invalid argument");
			return 1;
	}
	if(!strncmp(argv[1], "-test", 5)){
		runtest();
		return 0;
	}
	user_input = read_file(argv[1]);
    tokens = tokenize();
	Vector *asts = program(tokens);
	Scope *top=new_scope(NULL);
	asts = analyze(asts, top);
	start_gen(asts, top);
    return 0;
}

