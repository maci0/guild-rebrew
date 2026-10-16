int __cdecl strncmp(const char *, const char *, unsigned int);

/* ADDRESS: GOLD 0x004d2550 */
char __cdecl fcn_004d2550(char *s, int b)
{
	unsigned short w;
	int slot;
	char *rec;
	int inner;

	inner = *(int *)(b + 0x16c);
	if (strncmp(s, (const char *)0x60d128, 5) == 0) {
		rec = *(char **)(s + 0x200);
		w = *(unsigned short *)inner;
		if (*(int *)(rec + 0xa) != w) {
			slot = *(int *)0x6f0d60;
			((int *)0x930380)[slot] = (int)s;
			*(int *)0x6f0d60 = slot + 1;
		}
	}
	return 1;
}
