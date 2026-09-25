// FUNCTION: GOLDTL 0x004f56b0
// SIZE: 137
// FUNCTION: GOLD 0x004f3580
// SIZE: 144

typedef struct
{
	char b[0x2d];
} S2d;
// SIZE 0x2d

int __cdecl fcn_004f51d0(int a, S2d s, int c);
int __cdecl fcn_004f5300(int a, S2d s, int c);
int __cdecl fcn_004f53a0(int a, S2d s, int c);

int __cdecl fcn_004f56b0(int a, S2d s, int c)
{
	if ((unsigned char) s.b[0x1c] < 9) {
		return fcn_004f51d0(a, s, c);
	}
	if ((unsigned char) s.b[0x1c] < 0x11) {
		return fcn_004f5300(a, s, c);
	}
	if ((unsigned char) s.b[0x1c] < 0x1d) {
		return fcn_004f53a0(a, s, c);
	}
	return 0;
}
