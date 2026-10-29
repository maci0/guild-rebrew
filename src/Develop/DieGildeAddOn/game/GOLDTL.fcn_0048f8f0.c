typedef struct Blk24 {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Blk24;
// SIZE 0x18

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

extern char g_7f4ca0[];
extern float g_664154;
extern unsigned short g_774970;

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_005463a0(int, int, int, int, int);
int* __cdecl fcn_0048f450(char* q);
int __cdecl fcn_004a5340(char* e, int a, int* p, int b, float r, unsigned short* out);
int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);

/* ADDRESS: GOLDTL 0x0048f8f0 */
int __cdecl fcn_0048f8f0(char* e, char* q, Blk24* b1, Blk24* b2)
{
	char* p;
	int* h;
	int t;
	int found;
	int v;
	unsigned short idx;

	b1->d = 2;
	b1->c = *(int*) (q + 1);
	if (fcn_00502cd0(*(int*) (q + 0x5d), 2, 0, 0x204, 6) == 0)
		return 0;
	h = fcn_0048f450(q);
	if (h == 0)
		return 0;
	if (fcn_005463a0(2, 0, 0x89, 3, *(int*) (q + 1)) != 0)
		return 0;
	t = 0xf00500;
	if (fcn_004a5340(e, 1, &t, 0, gm_RandomMod(0x20) + g_664154, &idx) == 0)
		return 0;
	p = g_7f4ca0 + idx * 0x21c;
	b2->c = *(int*) (p + 4);
	b2->a = h[1];
	b2->d = 4;
	v = *(int*) (p + 0x170);
	if (v != 0) {
		b2->b = *(int*) (v + 1);
		return 1;
	}
	v = *(int*) (p + 0x16c);
	if (v != 0) {
		b2->b = *(int*) (v + 1);
		return 1;
	}
	{
		F8 f;

		f.mask = 0x7b4c4a0;
		f.b = 0;
		found = -1;
		fcn_004a5e60(g_7f4ca0 + g_774970 * 0x21c, 0, f, 0, 100.0f, &found);
	}
	if (found == -1)
		return 0;
	b2->b = found;
	return 1;
}
