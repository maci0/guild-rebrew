typedef struct
{
	char pad00[0x40];
	int f40;
	char pad44[0x5c - 0x44];
	unsigned char frames;
	unsigned char f5d;
	unsigned char f5e;
	char pad5f[0x70 - 0x5f];
} fcn_0045cbe0_Anim;
// SIZE 0x70

extern char* g_104049c;
extern unsigned int g_662ea8[];

unsigned int __cdecl fcn_00401000(void* buf, unsigned int n);
int __cdecl fcn_0045cb10(int idx, int frame);

/* ADDRESS: GOLDTL 0x0045cbe0 */
char __cdecl fcn_0045cbe0(char* o, unsigned int t)
{
	char* m;
	fcn_0045cbe0_Anim** arr;
	fcn_0045cbe0_Anim* e;
	unsigned int h;
	int i;
	int n;

	m = *(char**) (o + 0x1cc);
	if (m != 0 && *(int*) (m + 0x318) != 0 && *(int*) (m + 0x310) > 0) {
		arr = *(fcn_0045cbe0_Anim***) (m + 0x31c);
		h = fcn_00401000(&o, 4);
		n = *(int*) (*(char**) (*(char**) (o + 0x1cc) + 0x318) + 0x1e4);
		for (i = 0; i < n; i++) {
			e = arr[i];
			if (e != 0 && e->frames > 0 && e->f5d == 0 && (e->f5e & 0xf) > 0 && e->f40 > 0) {
				arr[n + i] = (fcn_0045cbe0_Anim*) fcn_0045cb10(e - ((fcn_0045cbe0_Anim*)g_104049c), (t / g_662ea8[e->f5e & 0xf] + h) % e->frames);
			}
		}
	}
	return 1;
}
