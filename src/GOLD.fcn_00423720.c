/* ADDRESS: GOLD 0x00423720 */
// fcn_00423720 — list search node with [n+8]==a.

int __cdecl fcn_00423720(int a)
{
	char* p;
	p = *(char**) 0x6323a4;
	while (p != 0) {
		if (*(int*) (p + 8) == a) {
			return (int) p;
		}
		p = *(char**) (p + 4);
	}
	return 0;
}
