extern unsigned char g_773d75;

char* __cdecl gm_SearchTable67(int id);
float __cdecl fcn_0050bb50(int id, unsigned char k);
int __cdecl fcn_004c51f0(int a, int b, int c, int d, unsigned char k, int n);

/* ADDRESS: GOLDTL 0x00497670 */
int __cdecl fcn_00497670(int a1, char* it, char* x)
{
	char* t;

	t = gm_SearchTable67(*(int*) (x + 4));
	if (!t) {
		return 0;
	}
	if (it[0] != 2) {
		return 0;
	}
	fcn_004c51f0(*(int*) (t + 1), -1, *(int*) (it + 4), *(int*) (it + 8), g_773d75, (int) fcn_0050bb50(*(int*) (it + 4), g_773d75));
	return 0xe;
}
