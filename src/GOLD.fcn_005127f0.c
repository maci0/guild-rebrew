int __cdecl strncmp(const char *a, const char *b, unsigned int n);
void __cdecl fcn_004179d0(int a);

/* ADDRESS: GOLD 0x005127f0 */
void __cdecl fcn_005127f0(char *s)
{
	int p;

	if (strncmp(s, (const char *)0x623240, 4) == 0) {
		p = *(int *)(s + 0x20c);
		if (p != 0)
			fcn_004179d0(p);
	}
}
