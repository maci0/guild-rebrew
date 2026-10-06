// FUNCTION: GOLD 0x004cced0
// FUNCTION: GOLDTL 0x4cda50

// fcn_004cced0 — set b header; r=fcn_004f0ed0(a+0x10); if(b&&!r) b[0]=1.

int __cdecl fcn_004f0ed0(void*);

void __cdecl fcn_004cced0(char* a, char* b)
{
	int r;
	if (b != 0) {
		b[0] = 2;
		b[1] = 0;
		*(int*) (b + 6) = 0;
	}
	r = fcn_004f0ed0(a + 0x10);
	if (b != 0 && r == 0) {
		b[0] = 1;
	}
}

