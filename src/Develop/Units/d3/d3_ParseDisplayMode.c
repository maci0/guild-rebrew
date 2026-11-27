

int __cdecl fcn_0064dc43(char*, char*, ...);

char __cdecl d3_ParseDisplayMode(char* str, int* mode)
{
	char ok;

	ok = 0;
	if (str != 0 && *str != 0 && mode != 0) {
		mode[2] = 0;
		ok = fcn_0064dc43(str, (char*) 0x677864, mode, mode + 1, mode + 3, mode + 2) == 4;
	}
	return ok;
}
