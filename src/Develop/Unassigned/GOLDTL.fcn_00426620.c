
/* ADDRESS: GOLDTL 0x00426620 */
char* __cdecl fcn_00426620(char* s, int unused, char* end)
{
	int i;
	char* p;
	char c;

	i = 0;
	if (s[0] == '&' || s[1] == '&' || s[0] == '|' || s[1] == '|') {
		return 0;
	}
	if (s < end) {
		p = s;
		do {
			c = *p;
			if (c == ')' || c == ';' || c == '(' || c == '{') {
				return 0;
			}
			if (*p == '&' && p[1] == *p) {
				return s + i;
			}
			if (c == '|' && p[1] == '|') {
				return s + i;
			}
			i++;
			p++;
		} while (p < end);
	}
	return 0;
}
