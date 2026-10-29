/* ADDRESS: GOLDTL 0x0042e4de */
int __cdecl fcn_0042e4de(const unsigned char* s1, const unsigned char* s2)
{
	while (*s1 == *s2 && *s1 != 0) {
		s1++;
		s2++;
	}
	if (*s1 == *s2) {
		return 0;
	}
	return (*s1 < *s2) ? -1 : 1;
}
