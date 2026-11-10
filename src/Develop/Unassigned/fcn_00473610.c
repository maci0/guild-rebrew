extern int g_77250c;
extern unsigned long g_14ce728;

/* ADDRESS: GOLDTL 0x00473610 */
short __cdecl fcn_00473610(void)
{
	int obj;
	int r;

	obj = *(int*) (g_77250c + 0x24);
	r = ((int (__stdcall*) (int)) *(int*) (*(int*) obj + 8))(obj);
	g_14ce728 = r;
	*(int*) (g_77250c + 0x24) = 0;
	return (short) r;
}
