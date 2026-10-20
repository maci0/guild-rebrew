extern char g_6b5c60[];
int __cdecl sprintf(char* buf, const char* fmt, ...);

char* __cdecl fcn_00508e40(int a1);
int __cdecl fcn_004e9180(char* a1, int a2);
int __cdecl fcn_004aacb0(unsigned short* a1, unsigned short* a2, unsigned short* a3, int* a4);
int __cdecl fcn_004aae50(char a1, unsigned short* a2, int* a3, int* a4);

/* ADDRESS: GOLDTL 0x004dc6e0 */
void __cdecl fcn_004dc6e0(char* obj, int* a1)
{
	char* v3;
	char* v4;
	char* v5;
	int tmp;
	int r;

	*(int*) (obj + 0x94) = -1;
	*(int*) (obj + 0x98) = -1;
	if (*(int*) (obj + 0x9c) != 0) {
		return;
	}
	v3 = fcn_00508e40(*(int*) (obj + 0x10));
	if (v3 == 0) {
		return;
	}
	if (*(char*) (v3 + 0x166) == 0) {
		return;
	}
	if (*(unsigned char*) (v3 + 0x1b1) > 0) {
		return;
	}
	if (a1[0] == 1) {
		v4 = fcn_00508e40(a1[3]);
		v5 = fcn_00508e40(a1[4]);
		if (v4 == 0 || v5 == 0) {
			return;
		}
		r = fcn_004aacb0((unsigned short*) v3, (unsigned short*) v4, (unsigned short*) v5, &tmp);
		*(int*) (obj + 0x98) = tmp;
	} else if (a1[0] == 2) {
		r = fcn_004e9180(v3, a1[2]);
		if (r == 0) {
			return;
		}
		r = fcn_004aae50(*(char*) (a1 + 1), (unsigned short*) v3, a1 + 3, &tmp);
		*(int*) (obj + 0x98) = tmp;
	} else {
		return;
	}
	*(int*) (obj + 0x94) = r;
	sprintf(obj + 0x14, g_6b5c60);
}
