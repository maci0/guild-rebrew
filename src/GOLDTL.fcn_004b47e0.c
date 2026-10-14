/* ADDRESS: GOLD 0x004b4670 */
/* ADDRESS: GOLDTL 0x004b47e0 */

int __cdecl fcn_004b47e0(unsigned char* stats, char* thr)
{
	int i;
	int n;

	for (i = 0, n = 0; i < 5; i++) {
		if (stats[i + 0x80] * 0.023809524f >= *(int*) (thr + 0x18))
			n++;
	}
	return n >= *(int*) (thr + 0x14);
}
