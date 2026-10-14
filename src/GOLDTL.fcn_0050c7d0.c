extern unsigned char* g_868050;
/* ADDRESS: GOLD 0x005093d0 */
/* ADDRESS: GOLDTL 0x0050c7d0 */

int __cdecl fcn_0050c7d0(int idx, int type)
{
	unsigned char* e;
	int sum;
	int i;

	sum = 0;
	e = g_868050 + idx * 0x24d;
	for (i = 0; i < 0x40; i++) {
		if ((*(unsigned short*) (e + 0x23 + i * 2) & 0x7fff) != 0 && e[0x1a3 + i] == type) {
			sum += e[0x1e3 + i];
		}
	}
	return sum;
}
