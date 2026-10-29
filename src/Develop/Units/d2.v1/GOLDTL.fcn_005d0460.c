int __cdecl fcn_0050e520(int k, int* out);
int __cdecl fcn_005cff10(char* s, int a2, int a3, int a4);
int __cdecl fcn_005cff20(char* s, int a2, int a3, int a4);

/* ADDRESS: GOLDTL 0x005d0460 */
int __cdecl fcn_005d0460(char* s, int a2, int a3, int a4)
{
	char* p;
	int r;

	if (s == 0) {
		return 0;
	}
	r = fcn_0050e520((unsigned char) *s, (int*) &p);
	if (r != 0) {
		return fcn_005cff10(p, a2, a3, a4);
	}
	return fcn_005cff20(s, a2, a3, a4);
}
