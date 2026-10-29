extern int g_67ac90;

char __cdecl fcn_00449db0(int a, int b, int mode, char* key, char* val);
int __cdecl fcn_00449b60(char* s);
int __cdecl fcn_0044c0e0(char* key, char* val);

/* ADDRESS: GOLDTL 0x0044c200 */
int __cdecl fcn_0044c200(int a, int b)
{
	int i;
	int r;
	char val[0x100];
	char key[0x100];

	fcn_00449db0(a, b, 0, key, val);
	r = fcn_00449b60(val);
	if (r != 0) {
		return r;
	}
	r = fcn_00449b60(key);
	if (r != 0) {
		return r;
	}
	r = fcn_0044c0e0(key, val);
	if (fcn_00449db0(a, b, -1, key, val)) {
		fcn_0044c0e0(key, val);
	}
	if ((g_67ac90 & 0x7f) == 1) {
		for (i = 1; i < 3; i++) {
			if (fcn_00449db0(a, b, i, key, val)) {
				fcn_0044c0e0(key, val);
			}
		}
		return r;
	}
	return r;
}
