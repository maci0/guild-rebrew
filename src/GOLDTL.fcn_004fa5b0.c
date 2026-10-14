/* ADDRESS: GOLDTL 0x00690478 */
extern char g_690478[];
/* ADDRESS: GOLD 0x00611748 */
extern char g_690478[];



typedef int (__cdecl* fcn_004fa5b0_fn)(char*, int);

int __cdecl fcn_004fa5b0(int a1, char* a2, int a3)
{
	if (a1 >= 0x3a) {
		return 0x40;
	}
	if (a2 == 0) {
		return 0x40;
	}
	if (*(unsigned char*) (a2 + 2) >= 0xa) {
		return 1;
	}
	return (*(fcn_004fa5b0_fn*) (g_690478 + a1 * 4))(a2, a3);
}
