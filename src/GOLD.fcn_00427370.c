// FUNCTION: GOLD 0x00427370
// fcn_00427370 — if(*0x63319c) fcn_0042b780(*0x63319c, arg).

int __cdecl fcn_0042b780(int, int);

void __cdecl fcn_00427370(int a)
{
	int h;
	h = *(int*) 0x63319c;
	if (h != 0) {
		fcn_0042b780(h, a);
	}
}
