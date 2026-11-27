int __cdecl d3_GetAnimSize(char* a);

/* ADDRESS: GOLDTL 0x00459cd0 */
int __cdecl d3_GetAnimMemorySize(char* a)
{
	int r;

	r = 0;
	if (a != 0 && a[0x16a] == 0) {
		r = d3_GetAnimSize(a);
		a[0x16a] = 1;
	}
	return r;
}
