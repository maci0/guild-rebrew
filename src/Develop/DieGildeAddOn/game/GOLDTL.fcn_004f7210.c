extern unsigned short g_774970;

char* __cdecl fcn_00508e40(int a1);
int __cdecl fcn_005d3120(int a1, int* a2);
char* __cdecl fcn_005463a0(int a1, int a2, int a3);
char* __cdecl he_fn_Handlung(void);
void __cdecl fcn_0051af00(char* buf, int fmt, int arg);

/* ADDRESS: GOLDTL 0x004f7210 */
int __cdecl fcn_004f7210(int a0, int* a1)
{
	char* e;
	char* s;
	char* p;
	int r;

	if ((*a1 == 3 || *a1 == 1)
	    && (*(int*) (a0 + 0x5c) == -1
	        || ((s = fcn_00508e40(*(int*) (a0 + 0x5c))) != 0
	            && (*(char*) (s + 8) == 0 || *(char*) (s + 2) == 0x0f)))) {
		r = 2;
		if (*a1 == 3) {
			r = fcn_005d3120(a0, a1) | 2;
		} else if (*a1 == 1 && *(char*) (a0 + 2) == 6) {
			for (e = fcn_005463a0(1, 0, 0x41); e != 0; e = he_fn_Handlung()) {
				if (*(int*) (e + 0xac) == *(int*) (g_774970 * 0x21c + 0x7f4ca4)) {
					p = fcn_00508e40(*(int*) (e + 0xb0));
					fcn_0051af00((char*) a1 + 0x14, 0x1ce2, *(unsigned short*) p);
					return r;
				}
			}
			fcn_0051af00((char*) a1 + 0x14, 0x679060, 0x1ce1);
		}
		return r;
	}
	return 1;
}
