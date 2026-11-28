
/* ADDRESS: GOLDTL 0x0042b2c0 */
/* ADDRESS: GOLDDE 0x00425670 */
int __cdecl msx_CountActiveWaveDrivers(void)
{
	int a;
	int n;

	n = 0;
	for (a = 0x6b7ed0; a < 0x6b7f10; a += 4) {
		if (*(int*) a != 0) {
			n++;
		}
	}
	return n;
}
