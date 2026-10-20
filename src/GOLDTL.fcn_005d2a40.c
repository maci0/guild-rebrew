#include <string.h>

char* __cdecl fcn_00508e40(int);
float __cdecl fcn_00505e30(int);
int __cdecl gm_WalkEntityChain(unsigned short);
float __cdecl fcn_0050f980(unsigned int, unsigned int, unsigned int);
int __cdecl fcn_004fa5b0(int, char*, int);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* ADDRESS: GOLDTL 0x005d2a40 */
int __cdecl fcn_005d2a40(int a0, int a1)
{
	char* p;
	char* q;
	char* t;
	int buf[0x88];
	float f8;
	float fc;
	float f10;
	float v;
	int i;
	int n;

	f8 = 0.0f;
	fc = 0.0f;
	f10 = 0.0f;
	memset(buf, 0, sizeof buf);
	buf[0] = 1;
	p = fcn_00508e40(a0);
	q = fcn_00508e40(a1);
	if (p == 0 || q == 0) {
		return 0;
	}
	t = fcn_00508e40(*(int*) (q + 0x60));
	if (t != 0) {
		f10 = (float) (gm_WalkEntityChain(*(unsigned short*) t) / 2);
	}
	t = fcn_00508e40(*(int*) (q + 0x64));
	if (t != 0) {
		f8 = (float) (gm_WalkEntityChain(*(unsigned short*) t) / 2);
	}
	if ((float) gm_WalkEntityChain(*(unsigned short*) q) > 0.0f) {
		fc = (float) gm_WalkEntityChain(*(unsigned short*) q);
	}
	else {
		fc = 0.0f;
	}
	fc = MAX(fc, MAX(f10, f8));
	f8 = (float) gm_WalkEntityChain(*(unsigned short*) p);
	if (f8 > fc) {
		f8 = 1.0f;
	}
	else {
		f8 = (fc - f8) / fc * 5.0f + 1.0f;
	}
	f10 = (100.0f - fcn_0050f980(*(unsigned short*) p, *(unsigned short*) q, 1)) * 0.05f + 1.0f;
	f8 = (1.0f - MIN(MAX(fcn_00505e30(*(unsigned short*) q), 15.0f), 30.0f) * (1.0f / 15.0f)) * 4.0f
		+ 1.0f + f10 + f8;
	for (i = 0; i < 5; i++) {
		f8 = f8 + (float) (unsigned char) q[0x80 + i] * (1.0f / 252.0f);
	}
	if (fcn_004fa5b0(0x10, p, (int) buf) & 2) {
		f8 = f8 * 0.5f;
	}
	return (int) MIN(MAX(f8, 2.0f), 15.0f);
}
