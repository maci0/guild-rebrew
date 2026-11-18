


extern int g_6b7d7c;
char* __cdecl fcn_00422530(int, int);

int __cdecl fcn_004234a0(int a1, int a2)
{
	char* entry;

	if (g_6b7d7c == 0) {
		return 1;
	}
	entry = fcn_00422530(a1, a2);
	if (entry != 0 && entry[0x36] == 2) {
		return 1;
	}
	return 0;
}
