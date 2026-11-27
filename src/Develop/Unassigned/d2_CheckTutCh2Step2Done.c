extern int *g_665f08;

#pragma auto_inline(off)
#pragma check_stack(off)

/* ADDRESS: GOLDTL 0x0057f090 */
int __cdecl d2_CheckTutCh2Step2Done(register int* p)
{
	register int v;

	if (*p == 0x17) {
		g_665f08[0] = 10;
		g_665f08[1] = 10;
		v = *(int*) 0x6b7fac;
		g_665f08[3] = v;
		return 1;
	} else if (*p == 0x18) {
		g_665f08[0] = 11;
		g_665f08[1] = 11;
		v = *(int*) 0x6b7fac;
		g_665f08[3] = v;
		return 1;
	}
	return 3;
}
