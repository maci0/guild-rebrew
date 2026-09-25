extern int g_67ac90;

char __cdecl fcn_00449db0(int a, int b, int mode, char* key, char* val);
int __cdecl fcn_00449b60(char* s);
char* __cdecl fcn_0044c0e0(char* key, char* val);

// FUNCTION: GOLDTL 0x44c310
// SIZE: 297
char* __cdecl fcn_0044c310(int a, int b)
{
	int i;
	char* r;
	char* t;
	char val[0x100];
	char key[0x100];

	fcn_00449db0(a, b, 0, key, val);
	r = (char*) fcn_00449b60(val);
	if (r != 0) {
		return r;
	}
	r = (char*) fcn_00449b60(key);
	if (r != 0) {
		return r;
	}
	r = fcn_0044c0e0(key, val);
	if (r != 0) {
		(*(int*) (r + 0x1e0))++;
	}
	if (fcn_00449db0(a, b, -1, key, val)) {
		t = fcn_0044c0e0(key, val);
		if (t != 0) {
			(*(int*) (t + 0x1e0))++;
		}
	}
	if ((g_67ac90 & 0x7f) == 1) {
		for (i = 1; i < 3; i++) {
			if (fcn_00449db0(a, b, i, key, val)) {
				t = fcn_0044c0e0(key, val);
				if (t != 0) {
					(*(int*) (t + 0x1e0))++;
				}
			}
		}
		return r;
	}
	return r;
}
