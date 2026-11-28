

// SIZE 0x70
typedef struct Tex {
	char name[0x40];
	int refs;
	int pad44;
	int id;
	char pad[0x24];
} Tex;

extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;

/* ADDRESS: GOLDDE 0x004512c0 */
void __cdecl d3_AddRefTexture(Tex* t, char all)
{
	unsigned int i;
	Tex* list;

	if (t == 0) {
		return;
	}
	if (all != 0 && *(int*) ((char*) t + 0x5c) > 0 && ((char*) t)[0x5d] == 0 && t->id != -1) {
		list = ((Tex*)d3_TextureBank);
		for (i = 0; i < d3_TextureBankCount; i++) {
			if (list[i].refs > 0 && list[i].id == t->id) {
				list[i].refs++;
			}
		}
		return;
	}
	t->refs++;
}
