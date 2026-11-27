
/* ADDRESS: GOLDTL 0x004246c0 */
int __cdecl sbs_CountRootSamples(void)
{
	char* p;
	int n;

	n = 0;
	p = *(char**) 0x6b7d68;
	p = *(char**) (p + 0x38);
	while (p != 0) {
		p = *(char**) (p + 0x104);
		n++;
	}
	return n;
}
