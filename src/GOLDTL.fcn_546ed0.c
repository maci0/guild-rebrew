// FUNCTION: GOLDTL 0x546ed0

// fcn_0053f100 — for each 0xa4-strided byte: if(--*p==0) *(p-4)=0.

void __cdecl fcn_0053f100(void)
{
	int p;
	for (p = 0x7d2024; p < 0x7dc424; p += 0xa4) {
		if (--*(char*) p == 0) {
			*(int*) (p - 4) = 0;
		}
	}
}
