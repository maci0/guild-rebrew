/* Walks a packed string list: index entries (plus 4 more when mode == 8) are
 * skipped, entry 4 or a nonempty entry 6 become the fallback returned for
 * mode == 8. */
/* ADDRESS: GOLD 0x0042c3b0 */
char* __cdecl txt_GetPackedStringEntry(char* entries, int index, int mode)
{
	char* alt;
	char* p;
	int i;
	int len;
	char mode_c;

	mode_c = (char) mode;
	p = entries;
	i = 0;
	alt = (char*) mode;
	if (mode_c == 8) {
		index += 4;
		alt = entries;
	}
	while (i < index - 1) {
		len = 0;
		while (p[len++] != 0) {
		}
		p = p + len - 1;
		if (p == 0) {
			return entries;
		}
		p++;
		i++;
		if (i == 4 || (i == 6 && *p != 0)) {
			alt = p;
		}
	}
	if (*p == 0) {
		if (mode_c == 4) {
			return entries;
		}
		if (mode_c == 8) {
			p = alt;
		}
	}
	return p;
}
