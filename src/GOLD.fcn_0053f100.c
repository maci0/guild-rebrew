// FUNCTION: GOLD 0x0053f100
// fcn_0053f100 — for each 0xa4-strided byte: if(--*p==0) *(p-4)=0.

void __cdecl fcn_0053f100(void)
{
	int p;
	for (p = 0x74e1e4; p < 0x7585e4; p += 0xa4) {
		if (--*(char*) p == 0) {
			*(int*) (p - 4) = 0;
		}
	}
}
