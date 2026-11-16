/* Walks a packed string list: a1 entries (plus 4 more when a2 == 8) are
 * skipped, entry 4 or a nonempty entry 6 become the fallback returned for
 * a2 == 8. */
/* ADDRESS: GOLD 0x0042c3b0 */
char* __cdecl fcn_0042c3b0(char* a0, int a1, int a2)
{
	char* alt;
	char* p;
	int n;
	int i;
	int len;
	char c;

	i = 0;
	p = a0;
	if ((char) a2 == 8) {
		a1 = a1 + 4;
		alt = a0;
	} else {
		alt = (char*) a2;
	}
	n = a1 - 1;
	if (n > 0) {
		do {
			len = 0;
			do {
				c = p[len];
				len++;
			} while (c != 0);
			p = p + len - 1;
			if (p == 0) {
				return a0;
			}
			p++;
			i++;
			if (i == 4 || (i == 6 && *p != 0)) {
				alt = p;
			}
		} while (i < n);
	}
	if (*p == 0) {
		if ((char) a2 == 4) {
			return a0;
		}
		if ((char) a2 == 8) {
			p = alt;
		}
	}
	return p;
}
