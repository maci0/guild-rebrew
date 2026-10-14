

extern char g_6b5c60[];

char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_004dc230(char* a, char* p, char* q, int* out);
int __cdecl fcn_004e9180(char* a, int v);
int __cdecl fcn_004dc3a0(char c, char* a, int* args, int* out);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);

void __cdecl fcn_004dc5f0(char* o, int* m)
{
	char* a;
	char* p;
	char* q;
	int r;
	int out;

	*(int*) (o + 0x94) = -1;
	*(int*) (o + 0x98) = -1;
	if (*(int*) (o + 0x9c) != 0) {
		return;
	}
	a = fcn_00508e40(*(int*) (o + 0x10));
	if (a == 0 || a[0x166] == 0 || *(unsigned char*) (a + 0x1b1) > 0) {
		return;
	}
	if (m[0] == 1) {
		p = fcn_00508e40(m[3]);
		q = fcn_00508e40(m[4]);
		if (p == 0 || q == 0) {
			return;
		}
		r = fcn_004dc230(a, p, q, &out);
		*(int*) (o + 0x98) = out;
		*(int*) (o + 0x94) = r;
		fcn_0064d41a(o + 0x14, &(*(char*)g_6b5c60));
	} else if (m[0] == 2) {
		if (fcn_004e9180(a, m[2]) == 0) {
			return;
		}
		r = fcn_004dc3a0(*(char*) (m + 1), a, m + 3, &out);
		*(int*) (o + 0x98) = out;
		*(int*) (o + 0x94) = r;
		fcn_0064d41a(o + 0x14, &(*(char*)g_6b5c60));
	}
}
