#pragma auto_inline(off)
#pragma check_stack(off)

/* ADDRESS: GOLDTL 0x0057f090 */
int __cdecl fcn_0057f090(register int* p)
{
	register int v;

	if (*p == 0x17) {
		(*(int**) 0x665f08)[0] = 10;
		(*(int**) 0x665f08)[1] = 10;
		v = *(int*) 0x6b7fac;
		*(volatile int*) (0xc + (char*) *(int*) 0x665f08) = v;
		return 1;
	} else if (*p == 0x18) {
		(*(volatile int**) 0x665f08)[0] = 11;
		(*(int**) 0x665f08)[1] = 11;
		v = *(int*) 0x6b7fac;
		*(volatile int*) ((char*) *(int*) 0x665f08 + 0xc) = v;
		return 1;
	}
	return 3;
}
