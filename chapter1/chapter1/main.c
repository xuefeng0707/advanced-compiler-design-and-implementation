#include <stdio.h>

#include "program1.h"
#include "ex_maxargs.h"
#include "interpreter.h"

int main()
{
	A_stm stm = program1();

	int count = maxargs(stm);
	printf("print count of program1: %d\n", count);

	Table t = inter_stm(stm, NULL);
	return 0;
}