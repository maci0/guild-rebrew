

// SIZE 0x70
typedef struct Tex {
	char name[0x40];
	int refs;
	int parent;
	int id;
	int pad4c;
	int x50;
	unsigned char flags;
	char pad55[0xf];
	int x64;
	int x68;
	int pad6c;
} Tex;

extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;

void __cdecl d3_SyncClonedTextureHandles(Tex* t)
{
	Tex* list;
	int idx;
	unsigned int i;

	if ((t->flags & 2) == 0 && t->name[0] != '*') {
		idx = t - ((Tex*)d3_TextureBank);
		list = ((Tex*)d3_TextureBank);
		for (i = 0; i < d3_TextureBankCount; i++) {
			if (list[i].refs > 0 && (list[i].flags & 2) != 0 && list[i].parent == idx) {
				list[i].x50 = t->x50;
				list[i].x64 = t->x64;
				list[i].x68 = t->x68;
			}
		}
	}
}
