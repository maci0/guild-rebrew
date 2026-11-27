

int __cdecl sbs_CountRootSamples(void);
int __cdecl sbs_CountSets(void);
int __cdecl sbs_CountSetEntries(int);

int __cdecl sbs_CalcCompiledSize(void)
{
	int r = 0;
	int a;
	int b;
	int c;

	if (*(int*) 0x6b7d68 != 0) {
		a = sbs_CountRootSamples();
		b = sbs_CountSets();
		c = sbs_CountSetEntries(0);
		r = (a + b) * 64 + (c + b + a + 0x1b) * 12 + *(int*) (*(char**) 0x6b7d68 + 0x34);
	}
	return r;
}
