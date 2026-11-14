void __cdecl fcn_004437f0(char*);
char* __cdecl fcn_0043fc10(int, int, unsigned int, unsigned int, unsigned int, void*);
void __cdecl fcn_004614b0(char*);
void* __cdecl fcn_0041de30(void*, int);
void __cdecl fcn_0043eef0(void*, void*);
void __cdecl fcn_0041e740(void*);
void __cdecl fcn_004371d0(void*, int);
void __cdecl fcn_004360e0(void*);

/* ADDRESS: GOLD 0x00446180 */
int __cdecl fcn_00446180(char* object)
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
    fcn_004437f0(object);
    for (row = 0; row < 8; row++) {
        for (column = 0; column < 8; column++) {
            step = *(unsigned char*)(object + (column + row * 8) * 100 + 0x13e);
            if (step == 0) {
                step = (*(unsigned char*)(object + 0x1c70) & 0x1c) >> 2;
                if (step == 0) {
                    step = 1;
                }
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
                left_y = ny - 1;
                y = row * size;
                if (left_y != 0) {
                    do {
                        left_x = nx - 1;
                        x = column * size;
                        if (left_x != 0) {
                            do {
                                resource = fcn_0043fc10(scene, universe, x, y, step, object + 0x30);
                                if (resource != 0 && *resource == 0x2a) {
                                    description = *(char**)(resource + 0x4c);
                                    if (description[0x40] == 0) {
                                        *(int*)(resource + 0x58) = 0;
                                        if (*(void**)(resource + 0x60) == 0) {
                                            fcn_004614b0(resource);
                                        }
                                        buffer = fcn_0041de30(*(void**)(resource + 0x60), 0x20);
                                        if (buffer != 0) {
                                            fcn_0043eef0(buffer, description + 0x10);
                                            fcn_0041e740(*(void**)(resource + 0x60));
                                            if (*(unsigned char*)0x63373c != 0) {
                                                fcn_004371d0(*(void**)(resource + 0x60), 0);
                                            }
                                            description[0x40] = 1;
                                            created++;
                                        }
                                    }
                                    if (*(signed char*)(resource + 0x68) >= 0) {
                                        fcn_004360e0(*(void**)(resource + 0x64));
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
