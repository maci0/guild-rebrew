// FUNCTION: GOLD 0x005e0578
// fcn_005e0578 — if(--a[4]<0) return fcn_005e1c1d(a, byte); *a[0]=byte; a[0]++; return byte.

int __cdecl fcn_005e1c1d(void*, int);

int __cdecl fcn_005e0578(unsigned char byte, char* a)
{
	if (--*(int*) (a + 4) < 0) {
		return fcn_005e1c1d(a, byte);
	}
	*(char*) *(char**) a = (char) byte;
	(*(char**) a)++;
	return byte;
}
