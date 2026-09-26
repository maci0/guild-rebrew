// FUNCTION: GOLD 0x5049e0
// SIZE: 160
// FUNCTION: GOLDTL 0x00507a10
// SIZE: 157

extern unsigned short g_774970;
extern char g_7f4ca0[];

int __cdecl fcn_00504bd0(int k);
char* __cdecl fcn_0050e4a0(int k);
void* __cdecl fcn_00502cd0(int list, int a, int b, int c, int d);

void* __cdecl fcn_00507a10(unsigned char* e)
{
	void* r;
	int t;
	unsigned char c;
	char* o;

	r = 0;
	t = fcn_00504bd0(e[0]);
	if (t == 5) {
		c = ((unsigned char*)g_7f4ca0)[g_774970 * 0x21c + 0x169];
		if (c == 0x1e) {
			o = fcn_0050e4a0(2);
		} else if (c == 0x1f) {
			o = fcn_0050e4a0(3);
		} else if (c == 0x20) {
			o = fcn_0050e4a0(4);
		} else if (c == 0x21) {
			o = fcn_0050e4a0(5);
		} else {
			o = 0;
		}
		if (o != 0) {
			r = fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x142);
		}
	} else if (t == 3) {
		o = fcn_0050e4a0(1);
		r = fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x115);
	}
	return r;
}
