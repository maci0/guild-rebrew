void __cdecl d3_UpdateFloorChunkLods(char*);
char* __cdecl d3_AcquireFloorTileTexture(int, int, unsigned int, unsigned int, unsigned int, void*);
void __cdecl d3_EnsureTextureSurface(char*);
void* __cdecl d3_LockSurface(void*, int);
void __cdecl d3_BlitFloorTileCells(void*, void*);
void __cdecl d3_UnlockSurface(void*);
void __cdecl d3_BuildTextureMipMaps(void*, int);
void __cdecl d3_PrecacheTexture(void*);

/* ADDRESS: GOLD 0x00446180 */
int __cdecl d3_BuildFloorTileTextures(char* object)
{
    int created;
    unsigned int size;
    int universe;
    int scene;
    unsigned int row;
    unsigned int column;
    unsigned int step;
    unsigned int nx;
    unsigned int ny;
    unsigned int left_x;
    unsigned int left_y;
    unsigned int x;
    unsigned int y;
    unsigned int base_x;
    unsigned int base_y;
    char* resource;
    char* description;
    void* buffer;

    created = 0;
    if (*(unsigned char*)0x633450 == 0 || *(int*)0xfc2dec == 0) {
        return 0;
    }
    size = *(unsigned int*)(object + 4);
    universe = *(int*)object;
    scene = *(int*)(object + 0x14);
    d3_UpdateFloorChunkLods(object);
    for (row = 0; row < 8; row++) {
        base_y = row * size;
        for (column = 0; column < 8; column++) {
            base_x = column * size;
            resource = object + (column + row * 8) * 100 + 0xe0;
            if (*(unsigned char*)(resource + 0x5e) == 0) {
                if (*(unsigned char*)(object + 0x1c70) & 0x1c) {
                    step = (*(unsigned char*)(object + 0x1c70) >> 2) & 7;
                } else {
                    step = 1;
                }
            } else {
                step = *(unsigned char*)(resource + 0x5e);
            }
            if (step != 0) {
                nx = size / step + 1;
                ny = nx;
                if (column == 7) {
                    nx -= 4 / step;
                }
                if (row == 7) {
                    ny -= 4 / step;
                }
                if (ny - 1 > 0) {
                    nx--;
                    y = base_y;
                    left_y = ny - 1;
                    do {
                        if (nx > 0) {
                            x = base_x;
                            left_x = nx;
                            do {
                                resource = d3_AcquireFloorTileTexture(scene, universe, x, y, step, object + 0x30);
                                if (resource != 0 && *resource == 0x2a) {
                                    description = *(char**)(resource + 0x4c);
                                    if (description[0x40] == 0) {
                                        *(int*)(resource + 0x58) = 0;
                                        if (*(void**)(resource + 0x60) == 0) {
                                            d3_EnsureTextureSurface(resource);
                                        }
                                        buffer = d3_LockSurface(*(void**)(resource + 0x60), 0x20);
                                        if (buffer != 0) {
                                            d3_BlitFloorTileCells(buffer, description + 0x10);
                                            d3_UnlockSurface(*(void**)(resource + 0x60));
                                            if (*(unsigned char*)0x63373c != 0) {
                                                d3_BuildTextureMipMaps(*(void**)(resource + 0x60), 0);
                                            }
                                            description[0x40] = 1;
                                            created++;
                                        }
                                    }
                                    if ((*(unsigned char*)(resource + 0x68) & 0x80) == 0) {
                                        d3_PrecacheTexture(*(void**)(resource + 0x64));
                                        *(unsigned char*)(resource + 0x68) |= 0x80;
                                    }
                                }
                                x += step;
                            } while (--left_x);
                        }
                        y += step;
                    } while (--left_y);
                }
            }
        }
    }
    return created;
}
