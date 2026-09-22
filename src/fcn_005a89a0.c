// FUNCTION: GOLD 0x005a89a0
// SIZE: 31
// fcn_005a89a0 — if(e=fcn_005a8600(*(int*)(a+1))) fcn_005a8500(a, e).

int __cdecl fcn_005a8600(int);
int __cdecl fcn_005a8500(void*, int);

void __cdecl fcn_005a89a0(char* a)
{
	int e;
	e = fcn_005a8600(*(int*) (a + 1));
	if (e != 0) {
		fcn_005a8500(a, e);
	}
}
