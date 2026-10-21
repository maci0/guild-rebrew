int __cdecl fcn_0064f170(void*, char*, int);
int __cdecl fcn_0064d470(char*, char*);
void* __cdecl fcn_00422460(char*, int);
int __cdecl fcn_00418c80(void*, void*, int, float);
int __cdecl fcn_004192b0(int, int, int, int);

/* ADDRESS: GOLDTL 0x00515e10 */
int __cdecl fcn_00515e10(char* p)
{
	char buf[0x100];
	int bn, br, si, v, r;
	char* s;
	char* d;

	r = fcn_0064f170(p, (char*) 0x6a1f7c, 4);
	if (r != 0)
		return r;

	s = p + 4;
	d = buf;
	while (*s != 0) {
		*d = *s;
		d++;
		s++;
	}

	bn = fcn_0064d470(buf, (char*) 0x6a1f78);
	br = fcn_0064d470(buf + 8, (char*) 0x6a1f74);
	if (br != 0) {
		br = 0x7d0;
		bn = 0;
	} else {
		br = 0;
	}

	if (*(int*)0x774934 != 0) {
		si = (int) fcn_00422460(buf, 0);
		if (si != 0) {
			v = (int)(*(float*)(p + 0x68)) + 0x32;
			r = fcn_00418c80((void*) si, p, 0x7f, (float) v);
			if (r != 0)
				fcn_004192b0(r, 0, bn, br);
		}
	}

	*(int*)(p + 0x224) = 0;
	return r;
}
