extern int g_772ea8;
extern int g_772ea8;
extern int g_772eac;
extern int g_772eac;

/* ADDRESS: GOLD 0x004d6930 */
/* ADDRESS: GOLDTL 0x004d7d30 */
void __cdecl fcn_004d7d30(char* p)
{
	if (g_772ea8 != 0) {
		*(int*) (p + 0x354) = 0;
		*(int*) (p + 0x358) = g_772eac;
		return;
	}
	*(int*) (p + 0x354) = 1;
}
