#include <string.h>

typedef struct {
	char pad_000[0x4];
	int f4;
} H_4b82f0;

char *__cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(char *, int);
int __cdecl fcn_004a55c0(char *, int, int *, int, float, int *);
int __cdecl gm_RandomMod(unsigned short);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_0051af00(char *, int, ...);
void __cdecl fcn_00545d40(int, int, char *, int, int, int);

/* ADDRESS: GOLDTL 0x004b82f0 */
int __cdecl fcn_004b82f0(int *obj)
{
	int a;
	int b;
	char buf[0x400];
	H_4b82f0 *h;
	char *t;
	char *s;
	int type;
	int r;
	int neg;
	int clamp;

	h = (H_4b82f0 *) fcn_00508e40(obj[0]);
	if (h == 0) {
		return 1;
	}
	if (fcn_005c6270((char *) h, 0x290) != 0) {
		return 0x400;
	}
	b = 0x600c00;
	if (fcn_004a55c0((char *) h, 1, &b, 0, 100.0f, &a) == 0) {
		return 0x400;
	}
	type = a & 0xffff;
	t = (char *) (0x7f4ca0 + type * 0x21c);
	r = gm_RandomMod(5) & 0xffff;
	neg = r * 2 + 6;
	fcn_004c54c0(h->f4, *(int *) (t + 4), -neg, 1);
	s = buf;
	fcn_0051af00(s, *(unsigned short *) ((char *) obj + 4) + 0x12e7,
		*(unsigned short *) t, *(unsigned short *) t, *(unsigned short *) t);
	clamp = strlen(s) > 0x100;
	fcn_00545d40(h->f4, h->f4, s, clamp, 0x603, 0);
	return 0;
}
