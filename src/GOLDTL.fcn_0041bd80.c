/* ADDRESS: GOLDTL 0x006b6008 */
extern unsigned char g_6b6008[3][0x100];
/* ADDRESS: GOLD 0x00631428 */
extern unsigned char g_6b6008[3][0x100];
/* ADDRESS: GOLDTL 0x006b6108 */
extern char g_6b6108[];
/* ADDRESS: GOLD 0x00631528 */
extern char g_6b6108[];
/* ADDRESS: GOLDTL 0x006b6208 */
extern char g_6b6208[];
/* ADDRESS: GOLD 0x00631628 */
extern char g_6b6208[];
/* ADDRESS: GOLD 0x00420780 */
/* ADDRESS: GOLDTL 0x0041bd80 */

void __cdecl fcn_0041bd80(char* p)
{
	int i;

	for (i = 0; i < 0x100; i++) {
		p[i] = *(char*) ((char*) g_6b6008 + i);
		p[i + 0x100] = *(char*) (g_6b6108 + i);
		p[i + 0x200] = *(char*) (g_6b6208 + i);
	}
}
