// FUNCTION: GOLD 0x0042fca0
// FUNCTION: GOLDTL 0x42f690

int __cdecl fcn_0042f120(int, int, int*);
void __cdecl fcn_0042f240(int, int, int, int);

int __cdecl fcn_0042f690(int a1, int a2, int a3, int a4)
{
	int r;

	r = fcn_0042f120(a1, a2, &a2);
	if (r != 0) {
		fcn_0042f240(r, a2, a3, a4);
		return a4;
	}
	return 0;
}
