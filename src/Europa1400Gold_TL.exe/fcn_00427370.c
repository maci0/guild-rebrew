// FUNCTION: GOLDTL 0x4238d0
// SIZE: 24

// fcn_00427370 — if(*0x6b7d7c) fcn_0042b780(*0x6b7d7c, arg).

int __cdecl fcn_0042b780(int, int);

void __cdecl fcn_00427370(int a)
{
	int h;
	h = *(int*) 0x6b7d7c;
	if (h != 0) {
		fcn_0042b780(h, a);
	}
}
