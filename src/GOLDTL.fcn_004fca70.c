// FUNCTION: GOLD 0x004fa3d0
// FUNCTION: GOLDTL 0x004fca70

extern char g_7f4ca0[];
extern float g_662910;
extern float g_6628a8;
extern int g_773d48;
extern int g_99f7f0;

int __cdecl fcn_004f4830(int k, int* info);
void __cdecl fcn_004c51a0(int a, int b, int c, int d);

int __cdecl fcn_004fca70(unsigned short id, unsigned char* s, unsigned char flags)
{
	int info[9];
	int i;
	int n;
	int amt;
	float v;

	fcn_004f4830(0xb, info);
	for (i = 0; i < 6; i++) {
		if (s[i] == 0) {
			break;
		}
	}
	if (i >= 6) {
		return 0;
	}
	n = *(int*) (g_7f4ca0 + 0x19c + id * 0x21c);
	v = n * (info[6] * 0.01f);
	if (!(v > g_6628a8)) {
		v = g_6628a8;
	}
	amt = (int) v;
	if (n > 0) {
		s[i] = 5;
		*(int*) (s + 8 + i * 4) = amt;
		*(int*) (s + 0x20 + i * 4) = info[6];
		if (flags & 1) {
			fcn_004c51a0(-1, *(int*) (g_7f4ca0 + 4 + id * 0x21c), 0, amt);
			g_773d48++;
		}
		if (flags & 2) {
			g_99f7f0 += amt;
		}
	}
	return 1;
}
