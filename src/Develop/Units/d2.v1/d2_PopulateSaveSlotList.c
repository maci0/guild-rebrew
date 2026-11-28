#include <string.h>
#include <stdio.h>

extern int vfs_RootDir;
extern int d2_CurrentWindowId;
extern char *d2_Controls, *d2_CurrentWindow;
int __cdecl vfs_ListFilesByExtension(char *, char *, void *);
int __cdecl vfs_Tfopen(char *, char *, int);
int __cdecl ls_LoadSavegameHeader(int, char *);
int __cdecl CloseVfsStream(int);
int __cdecl ls_AssignSavegameSlot(int, void *, int, void *);
int __cdecl d2_SetForm(int, int);
int __cdecl d2_CreateChildWindow(int, int, int, int, int, int);
int __cdecl d2_ShowTxt(int, int, char *, int);
int __cdecl d2_SetElementFont(int, int);
int __cdecl d2_AddWindowBitmapElement(int, int, int, int, void *, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl io_AppendText(int, ...);

/* ADDRESS: GOLDTL 0x005e0140 */
void __cdecl d2_PopulateSaveSlotList(int a, int b, void *items, void *records, char *path, int mode)
{
    int i, count, file, index, element, x, y;
    char header[0xfc], empty[0x210], text[64];
    char *row, *rec;
    unsigned short *pixels;

    memset(items, 0, 0x2100);
    for (i = 0; i < 16; i++) {
        row = (char *)items + i * 0x220;
        *(int *)(row + 4) = -1;
        *(int *)(row + 8) = -1;
    }
    count = vfs_ListFilesByExtension(path, (char *)0x6acfac, records);
    if (count > 16) count = 16;
    rec = (char *)records;
    for (i = 0; i < count; i++, rec += 0x210) {
        file = vfs_Tfopen(rec + 0x109, (char *)0x6750e8, vfs_RootDir);
        if (!file) continue;
        if (!ls_LoadSavegameHeader(file, header) || (header[4] & 2)) {
            CloseVfsStream(file);
            continue;
        }
        CloseVfsStream(file);
        index = ls_AssignSavegameSlot(16, items, (unsigned char)header[0x6d], rec);
        if (index == -1) continue;
        d2_SetForm(a, b);
        row = (char *)items + index * 0x220;
        y = *(short *)((int)d2_CurrentWindow + 0xc);
        element = d2_CreateChildWindow(0, (short)(index * 130), (short)(y - 16), 0x82, 16, d2_CurrentWindowId);
        *(int *)(row + 8) = element;
        *(int *)(element * 0x3cc + 0x10161cc) = 0x54;
        element = d2_ShowTxt(0xa8, -2, header + 0x9c, d2_CurrentWindowId);
        *(int *)(row + 4) = element;
        d2_SetElementFont(element, 0x53);
        strcpy(row + 0x99, header + 0x9c);
        row[0xc] = 1;
        if (*(int *)0x6a23ac >= 0x10028) {
            pixels = (unsigned short *)0x7ea3c0;
            for (x = 0; x < 120; x++) {
                pixels[x * 160] = 0;
                pixels[x * 160 + 159] = 0;
            }
            for (x = 0; x < 160; x++) {
                pixels[x] = 0;
                pixels[119 * 160 + x] = 0;
            }
            d2_AddWindowBitmapElement(0, 0, 160, 120, pixels, d2_CurrentWindowId);
        }
        *(int *)(d2_Controls + *(int *)(row + 4) * 0x2f4 + 0x5c) = 1;
        *(int *)(d2_Controls + *(int *)(row + 4) * 0x2f4 + 0x18) = *(int *)((int)d2_CurrentWindow + 0xc) - 0xa0;
        *(int *)(d2_Controls + *(int *)(row + 4) * 0x2f4 + 0x1d0) = 3;
        d2_CreateChildWindow(0xa4, 0x12, (short)(*(short *)((int)d2_CurrentWindow + 0xc) - 0xb0), 0x6e, 16, d2_CurrentWindowId);
        *(int *)(d2_CurrentWindowId * 0x3cc + 0x10161cc) = 0x54;
        *(int *)(d2_CurrentWindowId * 0x3cc + 0x1015f60) = 0;
        sprintf(text, (char *)0x699a68, *(int *)(header + 0x68), 0x11);
        io_AppendText(0x1cc5, header + 5, *(int *)(header + 0x32) + 0x578,
                      *(unsigned short *)(header + 0x36), *(int *)(header + 0x38) % 60);
        io_AppendText(0x1cc6, (header[0x6c] ? 10 : 0) + 0x114 + (unsigned char)header[0x62], header + 0x40,
                      (header[0x6c] ? 0x5f : 0) + 0x130 + (unsigned char)header[0x60],
                      (header[0x6c] ? 0x28 : 0) + 0x253 + (unsigned char)header[0x61], text,
                      *(int *)(0x14ac550 + *(int *)(header + 0x98) * 4));
    }
    memset((void *)0x7ea3c0, 0, 0x9600);
    for (i = 0; i < 16; i++) {
        row = (char *)items + i * 0x220;
        if (*(int *)(row + 8) != -1) continue;
        memset(empty, 0, sizeof(empty));
        sprintf(empty + 9, *(char **)0x14ac640, i);
        index = ls_AssignSavegameSlot(16, items, i, empty);
        if (index == -1) continue;
        d2_SetForm(a, b);
        row = (char *)items + index * 0x220;
        row[0xc] = 0;
        y = *(short *)((int)d2_CurrentWindow + 0xc);
        element = d2_CreateChildWindow(0, (short)(index * 130), (short)(y - 16), 0x78, 16, d2_CurrentWindowId);
        *(int *)(row + 8) = element;
        *(int *)(element * 0x3cc + 0x10161cc) = 0x54;
        element = d2_ShowTxt(0xa8, 0, row + 0x19, d2_CurrentWindowId);
        *(int *)(row + 4) = element;
        d2_SetElementFont(element, 0x53);
        d2_AddWindowBitmapElement(0, 0, 160, 120, (void *)0x7ea3c0, d2_CurrentWindowId);
        d2_AddElementToWindow(0x3c, 0x20, 0x4fb, d2_CurrentWindowId);
        *(int *)(d2_Controls + *(int *)(row + 4) * 0x2f4 + 0x5c) = 1;
        *(int *)(d2_Controls + *(int *)(row + 4) * 0x2f4 + 0x18) = *(int *)((int)d2_CurrentWindow + 0xc) - 0xa0;
        *(int *)(d2_Controls + *(int *)(row + 4) * 0x2f4 + 0x1d0) = 3;
        d2_CreateChildWindow(0xa4, 0x18, (short)(*(short *)((int)d2_CurrentWindow + 0xc) - 0xb0), 0x60, 16, d2_CurrentWindowId);
        *(int *)(d2_CurrentWindowId * 0x3cc + 0x10161cc) = 0x54;
        io_AppendText(0x1cc7);
    }
}
