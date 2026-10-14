/* ADDRESS: GOLDTL 0x0068a9d0 */
extern char g_68a9d0[];
/* ADDRESS: GOLD 0x0060bd68 */
extern char g_68a9d0[];
/* ADDRESS: GOLDTL 0x0068a9d4 */
extern char g_68a9d4[];
/* ADDRESS: GOLD 0x0060bd6c */
extern char g_68a9d4[];
/* ADDRESS: GOLDTL 0x0068a9d8 */
extern char g_68a9d8[];
/* ADDRESS: GOLD 0x0060bd70 */
extern char g_68a9d8[];
/* ADDRESS: GOLD 0x004c4450 */
/* ADDRESS: GOLDTL 0x004c4dc0 */

int __cdecl fcn_004c4dc0(int a1, int a2)
{
	if (a2 == -2) {
		return *(int*) g_68a9d0;
	}
	if (a2 == -3) {
		return *(int*) g_68a9d4;
	}
	if (a2 == -4) {
		return *(int*) g_68a9d8;
	}
	return a2;
}
