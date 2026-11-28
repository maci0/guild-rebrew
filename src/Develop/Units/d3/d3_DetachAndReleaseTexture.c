

// SIZE 0x70
typedef struct Tex {
	char name[0x40];
	int refs;
	int parent;
	int id;
	void* handle;
	int x50;
	unsigned char flags;
	char pad55[7];
	unsigned char x5c;
	char pad5d[0x13];
} Tex;

extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;

void __cdecl d3_ReleaseTexture(Tex*);

/* ADDRESS: GOLDDE 0x004522d0 */
void* __cdecl d3_DetachAndReleaseTexture(Tex* t, char all)
{
	void* r;
	unsigned int i;

	if (t == 0) {
		return 0;
	}
	if (t->handle == 0) {
		r = t;
	} else {
		r = t->handle;
		t->handle = 0;
		if (t->id != -1 && t->x5c > 0 && all != 0) {
			for (i = 0; i < d3_TextureBankCount; i++) {
				if (((Tex*)d3_TextureBank)[i].refs > 0 && ((Tex*)d3_TextureBank)[i].id == t->id) {
					d3_DetachAndReleaseTexture(&((Tex*)d3_TextureBank)[i], 0);
				}
			}
		}
		d3_ReleaseTexture(t);
	}
	return r;
}
