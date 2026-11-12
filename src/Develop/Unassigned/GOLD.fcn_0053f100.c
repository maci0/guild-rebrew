/* ADDRESS: GOLD 0x0053f100 */
void __cdecl fcn_0053f100(void)
{
	int p;

	for (p = 0x74e1e4; p < 0x7585e4; p += 0xa4) {
		if (--*(unsigned char*) p == 0) {
			*(int*) (p - 4) = 0;
		}
	}
}
