__declspec(dllimport) unsigned long __stdcall GetUserDefaultLCID(void);

extern unsigned short g_776270;
extern int g_776274;
extern int g_776258;

/* ADDRESS: GOLDTL 0x0065be6a */

/* CRT locale bootstrap: flags the locale table, then records the user's
 * default LCID into the two CRT locale slots. */
void __cdecl fcn_0065be6a(void)
{
	int lcid;

	g_776270 |= 0x104;
	lcid = (int) GetUserDefaultLCID();
	g_776274 = lcid;
	g_776258 = lcid;
}
