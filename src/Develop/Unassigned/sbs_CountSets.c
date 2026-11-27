
/* ADDRESS: GOLDTL 0x004246e0 */
int __cdecl sbs_CountSets(void)
{
	char* p;
	int n;

	n = 0;
	p = *(char**) 0x6b7d68;
	p = *(char**) (p + 0x3c);
	while (p != 0) {
		p = *(char**) (p + 0x3c);
		n++;
	}
	return n;
}
