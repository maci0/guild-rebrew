unsigned short __cdecl fcn_0042e410(int n);
char* __cdecl fcn_00508e40(int id);
void __cdecl fcn_004c4510(char* p, int n);
void __cdecl fcn_004c4570(int a, int b, int off, int* v);
void __cdecl fcn_004c5360(void);

// FUNCTION: GOLD 0x00493e90
// SIZE: 369
// FUNCTION: GOLDTL 0x004934c0
// SIZE: 369
char* __cdecl fcn_004934c0(char* e)
{
	char* pick;
	char* list[5];
	char* t;
	int cnt;
	int n;
	int i;
	int k;

	pick = 0;
	n = 0;
	cnt = 0;
	for (i = 0; i < 5; i++) {
		t = fcn_00508e40(((int*) (e + 0x68))[i]);
		if (t != 0) {
			cnt++;
			if (*(unsigned char*) (t + 8) > 0 && *(unsigned short*) (t + 0xa) > 0xb) {
				list[n] = t;
				n++;
			}
		}
	}
	if (n != 0) {
		pick = list[fcn_0042e410(n)];
	}
	if (e[2] == 5) {
		if (pick != 0) {
			return pick;
		}
		if (cnt != 0) {
			int v;

			t = fcn_00508e40(*(int*) (e + 0x5c));
			v = -1;
			if (t != 0) {
				fcn_004c4510(t, *(int*) (t + 4));
				fcn_004c4570(4, 1, 0x5c, &v);
				fcn_004c5360();
			}
			for (i = 0; i < 5; i++) {
				t = fcn_00508e40(((int*) (e + 0x68))[i]);
				if (t != 0) {
					if (*(int*) (t + 0x60) == *(int*) (e + 4)) {
						k = 1;
					} else if (*(int*) (t + 0x64) == *(int*) (e + 4)) {
						k = 2;
					} else {
						continue;
					}
					fcn_004c4510(t, *(int*) (t + 4));
					fcn_004c4570(4, 1, k * 4 + 0x5c, &v);
					fcn_004c5360();
				}
			}
		}
		return 0;
	}
	t = fcn_00508e40(*(int*) (e + 0x5c));
	if (t != 0 && *(unsigned char*) (t + 8) > 0 && *(unsigned char*) (t + 2) > 1 && *(unsigned char*) (t + 2) < 10 && (*(int*) (t + 0x1c8) & 0x40000) == 0) {
		return t;
	}
	if (pick != 0 && *(unsigned char*) (pick + 2) > 1 && *(unsigned char*) (pick + 2) < 10) {
		return pick;
	}
	return 0;
}
