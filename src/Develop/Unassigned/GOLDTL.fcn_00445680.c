int __cdecl _strcmpi(const char*, const char*);


/* ADDRESS: GOLDTL 0x00445680 */
int __cdecl fcn_00445680(char* s, char** st)
{
	char* p;

	if (st[0] != 0) {
		p = s[0] == '!' ? s + 1 : s;
		if (st[1] != 0) {
			if (_strcmpi(p, st[0]) == 0 && st[1] == s) {
				st[2] = s;
			}
		} else if (_strcmpi(p, st[0]) == 0) {
			st[2] = s;
		}
	} else if (st[1] == s) {
		st[2] = s;
	}
	return st[2] != s;
}
