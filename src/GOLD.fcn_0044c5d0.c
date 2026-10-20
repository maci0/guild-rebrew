int __cdecl strnicmp(const char *, const char *, unsigned int);

/* ADDRESS: GOLD 0x0044c5d0 */
char *__cdecl fcn_0044c5d0(const char *name)
{
	char *p;

	p = *(char **)0xfc2ffc;
	if (p == (char *)0xfc4a40) {
		return 0;
	}
	do {
		if (strnicmp(name, p, 0x3f) == 0) {
			return p;
		}
		p = *(char **)(p + 0x1fc);
	} while (p != (char *)0xfc4a40);
	return 0;
}
