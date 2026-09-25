typedef struct Stat {
	int v[9];
} Stat;
// SIZE 0x24

int __cdecl fcn_00493be0(char* p);
void __cdecl fcn_004f4830(int a, Stat* st);
char* __cdecl fcn_00508e40(int id);
float __cdecl fcn_0050f980(int a, int b, int c);

// FUNCTION: GOLD 0x004946b0
// SIZE: 212
// FUNCTION: GOLDTL 0x493ce0
// SIZE: 212
int __cdecl fcn_00493ce0(unsigned short* home, char* p)
{
	Stat st;
	int r;
	float f;
	float d;
	char* q;

	r = fcn_00493be0(p);
	fcn_004f4830(0, &st);
	f = (5.0f - st.v[6]) * 0.1f + 0.7f;
	q = fcn_00508e40(*(int*) (p + 0x18));
	d = fcn_0050f980(*(unsigned short*) q, *home, 1);
	if (!(d > f * 66.666f)) {
		if (d > f * 33.333f) {
			r += 1;
		} else {
			r += 2;
		}
	}
	if (r == 5) {
		if (!q[0x166]) {
			r = 4;
		}
	} else if (r == 7) {
		if ((unsigned char) q[0xd] < 2) {
			r = 6;
		}
	}
	r = r > 0 ? r : 0;
	if (r >= 9) {
		r = 9;
	}
	return r;
}
