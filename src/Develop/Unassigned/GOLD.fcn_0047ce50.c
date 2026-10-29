/* ADDRESS: GOLD 0x0047ce50 */
void __cdecl fcn_0047ce50(int arg0, int arg1, int arg2, int arg3, char* arg4)
{
	void __cdecl sub_47d950(int, int, int);
	int start = arg1;
	int len = arg3;

	if (start < *(int*) 0x6f045c) {
		start -= *(int*) 0x6f045c;
		len += start;
		start = 0;
	}
	if (start + len > *(int*) 0x5fed60) {
		len = *(int*) 0x5fed60 - start - 1;
	}
	{
		int save = *(int*) 0x5fed64;
		*(int*) 0x5fed64 = *(int*) (arg4 + 0x10);
		sub_47d950(*(int*) (arg4 + 0x1c) + 2 * (*(int*) (arg4 + 0x10) * start + arg0), arg2, len);
		*(int*) 0x5fed64 = save;
	}
}
