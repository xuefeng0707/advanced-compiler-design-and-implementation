#include "program1.h"

A_stm program1(void) {
	return A_CompoundStm(
		A_AssignStm(
			"a",
			A_OpExp(
				A_NumExp(5),
				Plus,
				A_NumExp(3)
			)
		),
		A_CompoundStm(
			A_AssignStm(
				"b",
				A_EseqExp(
					A_PrintStm(
						A_PairExpList(
							A_IdExp("a"),
							A_LastExpList(
								A_OpExp(
									A_IdExp("a"),
									Minus,
									A_NumExp(1)
								)
							)
						)
					),
					A_OpExp(
						A_NumExp(10),
						Times,
						A_IdExp("a")
					)
				)
			),
			A_PrintStm(
				A_LastExpList(
					A_IdExp("b")
				)
			)
		)
	);
}