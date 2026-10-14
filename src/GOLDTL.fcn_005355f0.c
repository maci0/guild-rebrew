/* ADDRESS: GOLDTL 0x006a2bf8 */
extern int g_6a2bf8;
/* ADDRESS: GOLDTL 0x006a2bfc */
extern int g_6a2bfc;
/* ADDRESS: GOLDTL 0x006a2c00 */
extern int g_6a2c00;



void __cdecl fcn_00471e30(int);

void __cdecl fcn_005355f0(void)
{
	if (g_6a2bf8 != -1) {
		fcn_00471e30(g_6a2bf8);
		g_6a2bf8 = -1;
		g_6a2bfc = -1;
		g_6a2c00 = -1;
	}
}
