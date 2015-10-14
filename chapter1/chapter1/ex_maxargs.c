#include "ex_maxargs.h"

int maxargs(A_stm stm)
{
	if (stm == NULL)
	{
		return 0;
	}
	switch (stm->kind)
	{
	case A_assignStm :
		return maxargs_exp(stm->u.assign.exp);
	case A_printStm:
		return 1 + maxargs_expList(stm->u.print.exps);
	case A_compoundStm:
		return maxargs(stm->u.compound.stm1) + maxargs(stm->u.compound.stm2);
	}

	return 0;
}

int maxargs_exp(A_exp exp)
{
	if (exp == NULL)
	{
		return 0;
	}
	switch (exp->kind)
	{
	case A_idExp:
	case A_numExp:
		return 0;
	case A_opExp:
		return maxargs_exp(exp->u.op.left) + maxargs_exp(exp->u.op.right);
	case A_eseqExp:
		return maxargs(exp->u.eseq.stm) + maxargs_exp(exp->u.eseq.exp);
	}
	return 0;
}

int maxargs_expList(A_expList expList)
{
	if (expList == NULL)
	{
		return 0;
	}
	switch (expList->kind)
	{
	case A_pairExpList:
		return maxargs_exp(expList->u.pair.head) + maxargs_expList(expList->u.pair.tail);
	case A_lastExpList:
		return maxargs_exp(expList->u.last);
	}
	return 0;
}