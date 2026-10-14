/* ADDRESS: GOLD 0x0050ab50 */
/* ADDRESS: GOLDTL 0x0050dfd0 */

int __cdecl fcn_0050dfd0(char* a1)
{
	int n;

	if (*(unsigned short*) a1 == 0x1dd) {
		n = *(int*) (a1 + 0xe);
		return (n + 2) * 5;
	}
	n = *(int*) (a1 + 0xe);
	if (n == 3) {
		return 0x50;
	}
	return n * 20;
}
