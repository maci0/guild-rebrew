/* ADDRESS: GOLDTL 0x00402b80 */
int __cdecl fcn_00402b80(void)
{
	char* base;
	char* value;
	int count;
	int i;

	value = 0;
	base = *(char**) 0x6b5c20;
	count = 0;
	i = 0x7d0;
	do {
		value = *(char**) base;
		base += 0x194;
		if (value != 0) {
			count++;
		}
	} while (--i != 0);
	return count;
}
