typedef struct
{
	char pad00[0x40];
	int f40;
	char pad44[0x5c - 0x44];
	unsigned char frames;
	unsigned char f5d;
	unsigned char f5e;
	char pad5f[0x70 - 0x5f];
} D3_TEX_ANIM_SLOT;
// SIZE 0x70

extern char* g_104049c;
extern unsigned int g_662ea8[];

unsigned int __cdecl vfs_CalcCrc32(void* buf, unsigned int n);
int __cdecl d3_FindTextureVariant(int idx, int frame);

/* ADDRESS: GOLDTL 0x0045cbe0 */
char __cdecl d3_UpdateAnimatedTextures(char* o, unsigned int t)
{
	char* m;
	D3_TEX_ANIM_SLOT** arr;
	D3_TEX_ANIM_SLOT* e;
	unsigned int h;
	int i;
	int n;

	m = *(char**) (o + 0x1cc);
	if (m != 0 && *(int*) (m + 0x318) != 0 && *(int*) (m + 0x310) > 0) {
		arr = *(D3_TEX_ANIM_SLOT***) (m + 0x31c);
		h = vfs_CalcCrc32(&o, 4);
		n = *(int*) (*(char**) (*(char**) (o + 0x1cc) + 0x318) + 0x1e4);
		for (i = 0; i < n; i++) {
			e = arr[i];
			if (e != 0 && e->frames > 0 && e->f5d == 0 && (e->f5e & 0xf) > 0 && e->f40 > 0) {
				arr[n + i] = (D3_TEX_ANIM_SLOT*) d3_FindTextureVariant(e - ((D3_TEX_ANIM_SLOT*)g_104049c), (t / g_662ea8[e->f5e & 0xf] + h) % e->frames);
			}
		}
	}
	return 1;
}
