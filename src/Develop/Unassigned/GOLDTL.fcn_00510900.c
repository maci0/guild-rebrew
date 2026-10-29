extern char g_7f3b40[];
extern char g_7f3b40[];
extern signed char g_7f3b00[];
extern signed char g_7f3b00[];

/* ADDRESS: GOLD 0x0050d460 */
/* ADDRESS: GOLDTL 0x00510900 */
char __cdecl fcn_00510900(void)
{
	int i;

	for (i = 0; i < 0xb7; i++) {
		((int*) g_7f3b40)[i] = -1;
	}
	for (i = 0; i < 17; i++) {
		((short*) g_7f3b00)[i] = -1;
	}
	return 0;
}
