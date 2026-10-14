/* ADDRESS: GOLDTL 0x00665f08 */
extern int* g_665f08;
/* ADDRESS: GOLD 0x005eec60 */
extern int* g_665f08;
/* ADDRESS: GOLDTL 0x006b7fc0 */
extern int g_6b7fc0;
/* ADDRESS: GOLD 0x006333e0 */
extern int g_6b7fc0;
/* ADDRESS: GOLDTL 0x00774a14 */
extern int g_774a14;
/* ADDRESS: GOLD 0x006f265c */
extern int g_774a14;
/* ADDRESS: GOLD 0x00576680 */
/* ADDRESS: GOLDTL 0x0057ec20 */

int __cdecl fcn_0057ec20(int a1)
{
	int* p;

	if (*(int*) ((char*)&g_774a14) == 0) {
		return 1;
	}
	p = g_665f08;
	if (*(int*) ((char*) p + 0x3c) == 2 || *p == 5) {
		return 0;
	}
	p = (int*) p[6];
	if (p == 0) {
		return 1;
	}
	if (*(int*) ((char*)&g_6b7fc0) != 0) {
		return 0;
	}
	return (*(int*) ((char*) p + 0x68) & a1) != 0;
}
