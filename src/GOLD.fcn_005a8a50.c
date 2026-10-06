// FUNCTION: GOLD 0x005a8a50
// fcn_005a8a50 — if(e=fcn_005a8600(*(int*)(a+1))) e[0x44/4]=b.

int __cdecl fcn_005a8600(int);

void __cdecl fcn_005a8a50(char* a, int b)
{
	int* e;
	e = (int*) fcn_005a8600(*(int*) (a + 1));
	if (e != 0) {
		e[0x44 / 4] = b;
	}
}
