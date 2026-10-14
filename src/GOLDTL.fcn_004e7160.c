/* ADDRESS: GOLDTL 0x009b0840 */
extern char g_9b0840[];
/* ADDRESS: GOLD 0x0092c500 */
extern char g_9b0840[];
/* ADDRESS: GOLD 0x004e5730 */
/* ADDRESS: GOLDTL 0x004e7160 */

void __cdecl fcn_004e7160(int idx, int a2, int a3, int a4, int a5, unsigned char a6)
{
	int o;

	o = idx * 20;
	*(int*) ((int) g_9b0840 + o) = a2;
	*(int*) ((int) g_9b0840 + 4 + o) = a3;
	*(int*) ((int) g_9b0840 + 8 + o) = a4;
	*(int*) ((int) g_9b0840 + 0x10 + o) = a5;
	*(unsigned char*) ((int) g_9b0840 + 0xc + o) = a6;
}
