// FUNCTION: GOLD 0x005deaf3
// fcn_005deaf3 — for(p=a; p<b; p++) if(*p) ((void(*)())*p)();

void __cdecl fcn_005deaf3(int* a, int* b)
{
	int* p;
	for (p = a; p < b; p++) {
		if (*p != 0) {
			((void (__cdecl*)()) *p)();
		}
	}
}
