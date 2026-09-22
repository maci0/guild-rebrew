// FUNCTION: GOLD 0x0050d350
// SIZE: 35
// fcn_0050d350 — fcn_0053ee40(a); if([0x6f1c28]) fcn_00458770(a, [0x6f1c28]).

int __cdecl fcn_0053ee40(int);
int __cdecl fcn_00458770(int, int);

void __cdecl fcn_0050d350(int a)
{
	fcn_0053ee40(a);
	if (*(int*) 0x6f1c28 != 0) {
		fcn_00458770(a, *(int*) 0x6f1c28);
	}
}
