extern int g_6b5cc4;

int __cdecl _strcmpi(char*, char*);

/* ADDRESS: GOLD 0x004118d0 */
unsigned char __cdecl fcn_004118d0(int u, int a)
{
	if (_strcmpi((char*) u, (char*) a) == 0) {
		g_6b5cc4 = u;
		return 0;
	}
	return 1;
}
