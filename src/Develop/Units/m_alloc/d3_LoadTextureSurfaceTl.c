/* SIZE 0x70 */
typedef struct Tex {
	char name[0x40];
	int refs;
	int parent;
	int id;
	int pad4c;
	int x50;
	unsigned char flags;
	char pad55[0x5c - 0x55];
	unsigned char x5c;
	unsigned char x5d;
	char pad5e[2];
	int x60;
	int x64;
	int x68;
	int pad6c;
} Tex;

extern unsigned char g_6b7ff8;
extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;
extern int g_67bd2c;

int __cdecl d3_ResolveTexturePath(char* name);
void __cdecl d3_LoadTextureFromFile(int a1, int a2, void* a3, int a4, int a5, int a6);
void __cdecl d3_SyncClonedTextureHandles(Tex* a0);

/* ADDRESS: GOLDTL 0x0045ce90 */
/* ADDRESS: GOLDDE 0x00451e40 */
void __cdecl d3_LoadTextureSurfaceTl(Tex* texture)
{
	Tex* p;
	int obj;
	unsigned int i;
	unsigned char saved;

	if (texture != 0 && texture->refs > 0) {
		if (texture->flags & 2) {
			texture = (Tex*) d3_TextureBank + texture->parent;
		}
		saved = g_6b7ff8;
		if (texture->x50 == 0 && texture->parent != 0 && texture->name[0] != '*') {
			obj = d3_ResolveTexturePath(texture->name);
			if (obj != 0) {
				int val = g_67bd2c;
				g_6b7ff8 = (texture->flags & 0x20) ? 0 : saved;
				d3_LoadTextureFromFile(obj, texture->x60, &texture->x50, val, texture->x68, texture->x68);
				texture->x64 = (unsigned int) texture->x68 >> g_6b7ff8;
			}
		}
		d3_SyncClonedTextureHandles(texture);
		g_6b7ff8 = saved;
		if (texture->x5c > 1 && texture->x5d == 0) {
			p = (Tex*) d3_TextureBank;
			for (i = 0; i < d3_TextureBankCount; i++, p++) {
				if (p->refs > 0 && p->id == texture->id && p->x5d > 0) {
					d3_LoadTextureSurfaceTl(p);
				}
			}
		}
	}
}
