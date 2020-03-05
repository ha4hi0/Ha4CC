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
    user_input = argv[1];
    if(!strncmp(argv[1], "-test", 5)){
        runtest();
        return 0;
    }
    asts = new_vector();
    tokens = new_vector();
    tokenize();
    program(asts);
	asts = analyze(asts);
	start_gen(asts);
    return 0;
}

