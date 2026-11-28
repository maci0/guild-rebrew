

extern char str_empty[];

int __cdecl d3_LoadFloorTexture(char*, int, int);
void __cdecl d3_InvalidateFloorChunks(char*);

int __cdecl d3_ReloadFloorTextureSlot(char* floor, int name, int idx)
{
	int r;

	floor[idx * 64 + 0x7e24] = (*(char*)str_empty);
	r = d3_LoadFloorTexture(floor, name, idx);
	if (r >= 0) {
		d3_InvalidateFloorChunks(floor);
	}
	return r;
}
