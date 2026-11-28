

// SIZE 0x4
typedef struct Col {
	unsigned char a;
	unsigned char b;
	unsigned char c0 : 1;
	unsigned char c1 : 1;
	unsigned char c2 : 6;
	unsigned char d;
} Col;

// SIZE 0x70
typedef struct Tex {
	char name[0x40];
	int refs;
	int pad44;
	int id;
	int pad4c[3];
	Col col;
	char x5c;
	char kind;
	char pad5e[0x12];
} Tex;

extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;

/* ADDRESS: GOLDDE 0x00451ac0 */
Tex* __cdecl d3_FindTextureVariant(int idx, char kind)
{
	Tex* p;
	int id;

	if (kind == 0) {
		return &((Tex*)d3_TextureBank)[idx];
	}
	id = ((Tex*)d3_TextureBank)[idx].id;
	if (((Tex*)d3_TextureBank)[idx].col.a < 0xff || ((Tex*)d3_TextureBank)[idx].col.c0) {
		for (p = &((Tex*)d3_TextureBank)[d3_TextureBankCount - 1]; p >= ((Tex*)d3_TextureBank); p--) {
			if (p->refs > 0 && p->id == id && p->kind == kind) {
				return p;
			}
		}
		return 0;
	}
	for (p = ((Tex*)d3_TextureBank); p <= &((Tex*)d3_TextureBank)[d3_TextureBankCount - 1]; p++) {
		if (p->refs > 0 && p->id == id && p->kind == kind) {
			return p;
		}
	}
	return 0;
}
unsigned char _dpad_1038144[33624];
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_104049c[324];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_10404a4[28];
unsigned char _dpad_10405d0[16];
#endif
