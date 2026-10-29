#include <string.h>

typedef struct BAE0 {
	int id;
	unsigned short f4;
} BAE0;

int __cdecl fcn_0042e410(int a0);
unsigned char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_005c6270(void* p, int n);
int __cdecl fcn_004bac00(void* q, int* out, float f);
int __cdecl fcn_00503fe0(int a0, int a1, int a2);
void __cdecl fcn_0051af00(char* out, int fmt, ...);
void __cdecl fcn_00545e80(int a0, int a1, char* s, int flag, int a4,
                         int a5, int a6, int a7, int a8);

/* ADDRESS: GOLDTL 0x004bae40 */
int __cdecl fcn_004bae40(BAE0* a0)
{
	int n;
	float f0;
	int v;
	char buf[0x200];
	unsigned char* q;
	int h;
	unsigned int len;
	int flag;
	double d;

	n = fcn_0042e410(0xf) & 0xffff;
	d = (double) n + *(double*) 0x664e78;
	f0 = (float) (d * *(double*) 0x6640e8);
	q = fcn_00508e40(a0->id);
	if (q == 0) {
		return 1;
	}
	if (fcn_005c6270(q, 0x290) == 0) {
		if (fcn_004bac00(q, &v, f0) != 0) {
			h = fcn_00503fe0(1, 1, v);
			if (h != 0) {
				fcn_0051af00(buf, a0->f4 + 0x12e7, h,
				             (int) (f0 * *(float*) 0x662cf8));
				len = strlen(buf);
				fcn_00545e80(*(int*) ((char*) q + 4), *(int*) ((char*) q + 4),
				             buf, 0x100 < len, 0x603, *(int*) ((char*) h + 1), -1, 0, 0);
				return 0;
			}
		}
	}
	return 0x400;
}
