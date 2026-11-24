/* Walks a packed string list: a1 entries (plus 4 more when a2 == 8) are
 * skipped, entry 4 or a nonempty entry 6 become the fallback returned for
 * a2 == 8. */
/* ADDRESS: GOLD 0x0042c3b0 */
char* __cdecl fcn_0042c3b0(char* a0, int a1, int a2)
{
	char* alt;
	char* p;
	int i;
	int len;
	char mode_c;

	mode_c = (char) a2;
	p = a0;
	i = 0;
	alt = (char*) a2;
	if (mode_c == 8) {
		a1 += 4;
		alt = a0;
	}
	while (i < a1 - 1) {
		len = 0;
		while (p[len++] != 0) {
		}
		p = p + len - 1;
		if (p == 0) {
			return a0;
		}
		p++;
		i++;
		if (i == 4 || (i == 6 && *p != 0)) {
			alt = p;
		}
	}
	if (*p == 0) {
		if (mode_c == 4) {
			return a0;
		}
		if (mode_c == 8) {
			p = alt;
		}
	}
	return p;
}
