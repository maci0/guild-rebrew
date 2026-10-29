extern unsigned char g_773d75;

float __cdecl fcn_0050bb50(int, char);
int __cdecl fcn_004c51f0(int, int, int, int, char, int);


/* ADDRESS: GOLDTL 0x0049c2b0 */
int __cdecl fcn_0049c2b0(int* a, char* e, int* b)
{
	int n;

	if (*e != 2)
		return 0;
	n = (int) fcn_0050bb50(*(int*) (e + 4), (*(char*)&g_773d75));
	fcn_004c51f0(a[1], b[1], *(int*) (e + 4), *(int*) (e + 8), (*(char*)&g_773d75), n);
	return 0xc;
}
