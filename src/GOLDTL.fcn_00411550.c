/* ADDRESS: GOLDTL 0x006772b4 */
extern char g_6772b4[];


void __cdecl fcn_0064d41a(void*, void*, double);
void __cdecl fcn_00411520(int, int, void*);

void __cdecl fcn_00411550(int a1, int a2, float a3)
{
	char buf[0x80];

	fcn_0064d41a(buf, g_6772b4, (double) a3);
	fcn_00411520(a1, a2, buf);
}
