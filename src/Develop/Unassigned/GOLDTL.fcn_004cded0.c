extern char g_9baae0[];
extern char g_9baae0[];

/* ADDRESS: GOLD 0x004cd350 */
/* ADDRESS: GOLDTL 0x004cded0 */
char* __cdecl fcn_004cded0(void)
{
	int i;
	int a;

	for (i = 0, a = (int) g_9baae0; a < (int) g_9baae0 + 0x2b8; a += 0x57, i++) {
		if (*(int*) a == 0) {
			return (char*) ((int) g_9baae0 + i * 87);
		}
	}
	return 0;
}
unsigned char _dpad_9ba1c0[2336];
unsigned char _dpad_9baae0[752];
