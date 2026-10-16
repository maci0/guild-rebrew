int __cdecl fcn_00425bf0(int, int, int);
char *__cdecl strstr(const char *, const char *);

/* ADDRESS: GOLD 0x0040d220 */
int __cdecl fcn_0040d220(int *a, int *b)
{
	int e;

	e = *a;
	if (e == 0) {
		fcn_00425bf0(*(int *)0x6332b8, *(int *)(*(int *)0x6332b8 + 0x118), 0x5f2304);
		return 0;
	}
	return strstr((char *)(e + 8), (char *)*b) != 0;
}
