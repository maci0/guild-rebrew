extern int g_774934;
extern float g_681750;

int* __cdecl fcn_004c2de0(int, int, int, int);
int __cdecl fcn_00423890(int*, int);
void __cdecl fcn_004c0a80(int*, int);

/* ADDRESS: GOLD 0x004c27d0 */
/* ADDRESS: GOLDTL 0x004c30a0 */

int* __cdecl fcn_004c30a0(int a, int b, int c, int d, int e)
{
	int* p;

	if (g_774934 == 0)
		return 0;
	p = fcn_004c2de0(a, b, c, d);
	if (p != 0) {
		fcn_00423890(p, (int) (g_681750 * 127.0f));
		fcn_004c0a80(p, e);
	}
	return p;
}
