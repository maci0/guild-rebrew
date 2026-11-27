typedef struct
{
	char pad0000[0x30];
	int anims[8];
	char pad0050[0x7e24 - 0x50];
	char names[8][0x40];
} D3_FLOOR_TEXTURES;
// SIZE 0x8024

void __cdecl d3_InvalidateFloorChunks(char*);
int __cdecl d3_LoadFloorTexture(D3_FLOOR_TEXTURES*, char* name, int slot);

/* ADDRESS: GOLDTL 0x0043f9d0 */
void __cdecl fcn_0043f9d0(D3_FLOOR_TEXTURES* o)
{
	int i;

	if (o == 0) {
		return;
	}
	d3_InvalidateFloorChunks((char*) o);
	for (i = 0; i < 8; i++) {
		d3_LoadFloorTexture(o, o->names[i], i);
	}
}
