extern char g_677864[];


int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDDE 0x00418f90 */
char* __cdecl d3_FormatDisplayMode(int* mode, char* buf)
{
	char* result;

	result = 0;
	if (mode != 0 && buf != 0) {
		fcn_0064d41a(buf, (char*) &g_677864, mode[0], mode[1], mode[3], mode[2]);
		result = buf;
	}
	return result;
}
