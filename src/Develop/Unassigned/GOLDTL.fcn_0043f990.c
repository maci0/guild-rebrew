

extern char g_6b5c60[];

int __cdecl d3_LoadFloorTexture(char*, int, int);
void __cdecl d3_InvalidateFloorChunks(char*);

int __cdecl d3_ReloadFloorTextureSlot(char* o, int a2, int idx)
{
	int r;

	o[idx * 64 + 0x7e24] = (*(char*)g_6b5c60);
	r = d3_LoadFloorTexture(o, a2, idx);
	if (r >= 0) {
		d3_InvalidateFloorChunks(o);
	}
	return r;
}
