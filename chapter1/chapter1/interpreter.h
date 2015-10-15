#ifndef INTERPERTER_H_
#define INTERPERTER_H_

#include "A.h"

typedef struct Table_ *Table;
struct Table_
{
	string id;
	int value;
	Table tail;
};
Table table(string id, int value, Table tail);

typedef struct IntAndTable_ *IntAndTable;
struct IntAndTable_
{
	int value;
	Table t;
};
IntAndTable intAndTable(int value, Table t);

Table inter_stm(A_stm, Table);
IntAndTable inter_exp(A_exp, Table);
IntAndTable inter_print_exp(A_exp exp, Table t);

int lookup(string id, Table t);

#endif
