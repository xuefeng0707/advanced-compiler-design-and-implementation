#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "interpreter.h"

Table inter_stm(A_stm stm, Table t)
{
	Table t1 = NULL;
	IntAndTable iat = NULL;
	A_expList el = NULL;
	if (stm == NULL)
	{
		return t;
	}
	switch (stm->kind)
	{
	case A_compoundStm:
		t1 = inter_stm(stm->u.compound.stm1, t);
		return inter_stm(stm->u.compound.stm2, t1);
	case A_assignStm:
		iat = inter_exp(stm->u.assign.exp, t);
		return table(stm->u.assign.id, iat->value, iat->t);
	case A_printStm:
		switch (stm->u.print.exps->kind)
		{
		case A_pairExpList:
			iat = inter_print_exp(stm->u.print.exps->u.pair.head, t);
			el = stm->u.print.exps->u.pair.tail;
			while (el != NULL)
			{
				if (el->kind == A_pairExpList)
				{
					iat = inter_print_exp(el->u.pair.head, iat->t);
					el = el->u.pair.tail;
				}
				else if (el->kind == A_lastExpList)
				{
					iat = inter_print_exp(el->u.last, iat->t);
					break;
				}
			}
			break;
		case A_lastExpList:
			iat = inter_print_exp(stm->u.print.exps->u.last, t);
		default:
			break;
		}
		printf("\n");
		return iat->t;
	default:
		break;
	}
	return NULL;
}

Table table(string id, int value, Table tail)
{
	Table t = checked_malloc(sizeof *t);
	t->id = id;
	t->value = value;
	t->tail = tail;
	return t;
}

IntAndTable intAndTable(int value, Table t)
{
	IntAndTable iat = checked_malloc(sizeof *iat);
	iat->value = value;
	iat->t = t;
	return iat;
}

IntAndTable inter_exp(A_exp exp, Table t)
{
	Table t1 = NULL;
	IntAndTable iat1 = NULL;
	IntAndTable iat2 = NULL;
	int num = 0;
	switch (exp->kind)
	{
	case A_idExp:
		return intAndTable(lookup(exp->u.id, t), t);
	case A_numExp:
		return intAndTable(exp->u.num, t);
	case A_opExp:
		iat1 = inter_exp(exp->u.op.left, t);
		iat2 = inter_exp(exp->u.op.right, iat1->t);
		switch (exp->u.op.oper)
		{
		case Plus:
			num = iat1->value + iat2->value;
			break;
		case Minus:
			num = iat1->value - iat2->value;
			break;
		case Times:
			num = iat1->value * iat2->value;
			break;
		case Div:
			num = iat1->value / iat2->value;
			break;
		default:
			break;
		}
		return intAndTable(num, iat2->t);
	case A_eseqExp:
		t1 = inter_stm(exp->u.eseq.stm, t);

		return inter_exp(exp->u.eseq.exp, t1);
	default:
		break;
	}
	return NULL;
}

int lookup(string id, Table t)
{
	Table tmp = t;
	while (tmp != NULL)
	{
		if (strcmp(id, tmp->id) == 0)
		{
			return tmp->value;
		}
	}

	// default value : 0
	return 0;
}

IntAndTable inter_print_exp(A_exp exp, Table t)
{
	IntAndTable iat = NULL;
	iat = inter_exp(exp, t);
	printf("%d ", iat->value);

	return iat;
}