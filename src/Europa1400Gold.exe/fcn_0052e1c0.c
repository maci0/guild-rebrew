// FUNCTION: GOLD 0x0052e1c0
// SIZE: 34
// fcn_0052e1c0 — for p stride 0xc8: if(*p) *(*p + 0x224)=0; *p=0;.

void __cdecl fcn_0052e1c0(void)
{
	int p;
	for (p = 0x760640; p < 0x761f40; p += 0xc8) {
		if (*(int*) p != 0) {
			*(int*) (*(int*) p + 0x224) = 0;
		}
		*(int*) p = 0;
	}
}
