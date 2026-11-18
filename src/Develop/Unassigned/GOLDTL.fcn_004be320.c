
/* ADDRESS: GOLDTL 0x004be320 */
void __cdecl fcn_004be320(char* p, int count)
{
	int i;

	i = 0;
	while (p != 0 && count != i) {
		p = *(char**) (p + 0x3c);
		i++;
	}
}
