#include <stdio.h>
#include <string.h>

int __cdecl fcn_00479010(void*);
int __cdecl fcn_004790d0(void*);
int __cdecl fcn_0047cb30(int, int, int, int);
void __cdecl fcn_0047c6e0(int, int, void*, int, unsigned char);
void __cdecl fcn_0047cda0(int, void*);
void __cdecl fcn_00476020(int);
int __cdecl fcn_004690a0(int);
int __cdecl fcn_0047c820(int, int, char*, char*, unsigned char, char, int);
void __cdecl fcn_0046f190(int, int, int, int, void*, char*, int);
void __cdecl fcn_00468ea0(int, int, int, int);

/* ADDRESS: GOLD 0x00476ca0 */
void __cdecl fcn_00476ca0(char* obj, int x, int y)
{
    int had_surface;
    int old_x;
    int old_y;
    int old_width;
    int old_height;
    int old_font;
    int selected;
    int index;
    int px;
    int py;
    int font;
    int* entry;
    char label[64];

    if (*(int*) 0x6ed9d4 != 0)
        return;
    had_surface = *(int*) (obj + 0x34);
    if (had_surface == 0 && fcn_00479010(obj) == 0)
        return;
    old_y = *(int*) 0x6f045c;
    old_x = *(int*) 0x6f0458;
    old_height = *(int*) 0x5fed60;
    old_width = *(int*) 0x5fed5c;
    fcn_0047cb30(0, 0, *(int*) (obj + 4), *(int*) (obj + 8));
    selected = *(int*) 0x5feba8;
    if (selected != -1) {
        *(short*) (0xf8a52d + selected * 17) = (short) x;
        *(short*) (0xf8a52f + selected * 17) = (short) y;
        fcn_0047cda0(selected, obj);
    } else {
        fcn_0047c6e0(x, y, obj, *(int*) 0x6ed9cc, *(unsigned char*) 0x6ed9d0);
    }
    old_font = *(int*) 0x5fe718;
    fcn_00476020(*(int*) 0x5fe73c + 1);
    index = 0;
    for (entry = (int*) 0xf8ab80; entry < (int*) 0xf8abc8; entry += 3) {
        if (*entry == -1)
            continue;
        px = x + *(short*) (*(int*) 0x6ed918 + *(int*) 0x5fe750 * 0x54 + 0x50) + index % 3 * 26;
        py = y + (*(int*) 0xf8f084 + 26) * (index / 3);
        font = fcn_004690a0(*entry);
        if (fcn_0047c820(px, py, obj, (char*) font, *(unsigned char*) 0x6ed98c, -2, 0)) {
            if (*entry >= 0xdf && *entry <= 0x3ba && entry[1] == -1)
                strcpy(label, *(char**) 0x143a51c);
            else
                sprintf(label, (char*) 0x5fe7d0, entry[1]);
            fcn_0046f190(px - 8, py + 24, 0x28, *(int*) 0xf8f084, obj, label, 8);
        }
        index++;
    }
    fcn_00468ea0(x, y, 128, 128);
    fcn_00476020(old_font);
    fcn_0047cb30(old_x, old_y, old_width, old_height);
    if (had_surface == 0)
        fcn_004790d0(obj);
}
