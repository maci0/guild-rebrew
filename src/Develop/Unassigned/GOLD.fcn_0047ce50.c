/* ADDRESS: GOLD 0x0047ce50 */
void __cdecl fcn_0047ce50(int arg0, int arg1, int arg2, int arg3, char* arg4)
{
	void __cdecl sub_47d950(int, int, int);
	extern int g_005fed64;
	int start = arg1;
	

	if (start < *(int*) 0x6f045c) {
		start -= *(int*) 0x6f045c;
		arg3 += start;
		start = 0;
	}
	if (start + arg3 > *(int*) 0x5fed60) {
		arg3 = *(int*) 0x5fed60 - start - 1;
	}
	{
		int save = g_005fed64;
		g_005fed64 = *(int*) (arg4 + 0x10);
		sub_47d950(*(int*) (arg4 + 0x1c) + 2 * (*(int*) (arg4 + 0x10) * start + arg0), arg2, arg3);
		g_005fed64 = save;
	}
}
