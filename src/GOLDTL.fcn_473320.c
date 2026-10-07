// FUNCTION: GOLDTL 0x473320

// fcn_00472a50 — table: if(n && *(int*)n&8) { fcn_00476850(n); *p=0; } else if(n) *(int*)n|=4.

int __cdecl fcn_00476850(int);

void __cdecl fcn_00472a50(void)
{
	int p;
	for (p = 0x1015ec0; p < 0x1015f40; p += 4) {
		int n;
		int f;
		n = *(int*) p;
		if (n != 0) {
			f = *(int*) n;
			if (f & 8) {
				fcn_00476850(n);
				*(int*) p = 0;
			} else {
				*(int*) n = f | 4;
			}
		}
	}
}
