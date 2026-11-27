#include <stdio.h>
#include <string.h>
#include "gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"
extern GOLD_GUI_WINDOW g_00f8f120[];
extern GuiEnt* g_00f8f080;
extern float g_6628a8;
extern int d2_CurrentWindowId;
extern char g_6b5c60[];
char* __cdecl fcn_00430470(char*, const char*, void*);
unsigned int __cdecl fcn_00430bd0(void*, unsigned int, unsigned int, char*);
int __cdecl fcn_00430fa0(char*, int, int);
void __cdecl fcn_00430aa0(char*);
int __cdecl fcn_00472380(short, short, short, short, unsigned int);
int __cdecl d2_CreateChildWindow(short, short, short, short, unsigned int, int);
void __cdecl fcn_004721d0(char*, int);
int __cdecl fcn_00468880(char*);
void __cdecl d2_AddRefcount(int);
int __cdecl d2_AddElementToWindow(short, short, int, int);
int __cdecl fcn_0042e770(char*);
int __cdecl d2_ShowTxt(short, short, char*, int);
int __cdecl fcn_0046a350(int, int, int, int, unsigned char, int);
int __cdecl fcn_0046a950(int, int, unsigned char, int, int, int, unsigned char, int);
void __cdecl fcn_0046cd90(short, short, int);
#define I32(p) (*(int*)(p))
#define S16(p) (*(short*)(p))
#define U8(p) (*(unsigned char*)(p))
#define F32(p) (*(float*)(p))

/* ADDRESS: GOLD 0x004741e0 */
int __cdecl fcn_004741e0(short x, short y, char* name)
{
    char message[256];
    char path[256] = "";
    char header[5];
    char* file;
    int version;
    int count;
    int slot;
    int dialogOff;
    int dialogWords;
    int* winSlot;
    int p;
    int* q;
    int i;
    int j;
    char* record;
    char* v1;
    char* v2;
    char* window;
    char* parent;
    char* current;
    int parentID;
    int windowID;
    int resource;
    int element;
    char* coords;
    char* imageName;
    int* typePtr;
    unsigned char* aux;
    unsigned char aux0;

    strcpy(path, name);
    if (!I32(0x6ed984)) {
        strcpy(path, (char*)0x5fe608);
        strcat(path, name);
        strcat(path, ".form");
    }
    file = fcn_00430470(path, "rb", *(void**)0x6333fc);
    if (!file) {
        sprintf(message, "Konnte die Form\n %s\nnicht laden...", name);
        return -1;
    }
    fcn_00430bd0(header, 1, 4, file);
    version = (signed char)header[3] - '0';
    header[4] = 0;
    if (version == 2) {
        fcn_00430bd0(&count, 4, 1, file);
        fcn_00430bd0((void*)0x68ce98, 0x101c, count, file);
    } else {
        version = 0;
        fcn_00430fa0(file, 0, 0);
        fcn_00430bd0(&count, 4, 1, file);
        fcn_00430bd0((void*)0x633f18, 0xed4, count, file);
    }
    fcn_00430aa0(file);
    slot = 1;
    if (I32(0xfb1450)) {
        p = 0xfb1450;
        do {
            if (p >= 0xfb91e4) {
                return -1;
            }
            q = (int*)(p + 0x2ac);
            p += 0x2ac;
            slot++;
        } while (*q);
        if (slot >= 0x30) {
            return -1;
        }
    }
    dialogOff = slot * 0x2ac;
    I32(dialogOff + 0xfb11b4) = I32(0x6ed94c) - 1;
    if (count > 0) {
        v1 = (char*)0x633f18;
        v2 = (char*)0x68dd68;
        dialogWords = slot * 0xab;
        winSlot = (int*)(dialogWords * 4 + 0xfb1024);
        i = 0;
        do {
            int ver = version;
            record = v2 - 0xed0;
            if (ver == 0) {
                record = v1;
                parentID = I32(v1 + 0xe94);
                if (parentID) {
                    int pWin = I32((dialogWords + parentID) * 4 + 0xfb1020);
                    parent = (char*)&g_00f8f120[pWin];
                    parentID = pWin;
                }
                if (I32(v1 + 0xe94)) {
                    *winSlot = d2_CreateChildWindow((short)(S16(v1) - S16(parent + 4)),
                        (short)(S16(v1 + 2) - S16(parent + 6)), S16(v1 + 4), S16(v1 + 6),
                        I32(v1 + 8), parentID);
                } else {
                    *winSlot = fcn_00472380(S16(v1), S16(v1 + 2), S16(v1 + 4), S16(v1 + 6), I32(v1 + 8));
                }
            } else if (ver == 2) {
                if (I32(v2)) {
                    parentID = I32((dialogWords + I32(v2)) * 4 + 0xfb1020);
                    parent = (char*)&g_00f8f120[parentID];
                    windowID = d2_CreateChildWindow((short)(S16(record) - S16(parent + 4)),
                        (short)(S16(v2 - 0xece) - S16(parent + 6)), S16(v2 - 0xecc), S16(v2 - 0xeca),
                        I32(v2 - 0xec8), parentID);
                } else {
                    windowID = fcn_00472380(S16(record), S16(v2 - 0xece), S16(v2 - 0xecc), S16(v2 - 0xeca), I32(v2 - 0xec8));
                }
                *winSlot = windowID;
                if (v2[0x7c]) {
                    fcn_004721d0(v2 + 0x7c, d2_CurrentWindowId);
                }
                current = (char*)&g_00f8f120[d2_CurrentWindowId];
                if ((U8(current + 0xc) & 1) && F32(v2 + 0xbc) == g_6628a8) {
                    I32(current + 0x394) = 0x3f266666;
                } else {
                    I32(current + 0x394) = I32(v2 + 0xbc);
                }
            }
            window = (char*)&g_00f8f120[*winSlot];
            if (ver == 2) {
                S16(window + 0x27c) = (short)fcn_00468880(record[0xe90] ? record + 0xe90 : "_FONT");
                if (record[0xed4]) {
                    resource = fcn_00468880(record + 0xed4);
                    I32(window + 0x388) = resource;
                    d2_AddRefcount(resource);
                }
                S16(window + 0x10) = S16(record + 0xf14);
                S16(window + 0x12) = S16(record + 0xf16);
                S16(window + 0x14) = S16(record + 0xf18);
                S16(window + 0x16) = S16(record + 0xf1a);
                if (U8(window + 0xc) & 4) {
                    resource = fcn_00468880(record + 0xf90);
                    I32(window + 0x278) = resource;
                    if (resource == -1) {
                        I32(window + 0x278) = I32(0x5fe744);
                    }
                }
            }
            g_00f8f080[I32(window + 0x26c)].f40 = dialogOff + 0xfb1020;
            windowID = *winSlot;
            I32(dialogOff + 0xfb11a4)++;
            j = 0;
            if (S16(record + 0xcc) > 0) {
                coords = record + 0xc;
                imageName = record + 0x190;
                typePtr = (int*)(record + 0xd90);
                do {
                    if (typePtr[-0x330] < 0x40) {
                        resource = fcn_00468880(imageName);
                        if (resource != -1) {
                            element = d2_AddElementToWindow(S16(coords), S16(coords + 0x60), resource, windowID);
                            if (*typePtr == 0x12) {
                                g_00f8f080[element].dirty = 1;
                                g_00f8f080[element].f4c = 0;
                            }
                            if (*typePtr == 8) {
                                g_00f8f080[element].dirty = 0;
                                g_00f8f080[element].f4c = 1;
                            }
                            g_00f8f080[element].f40 = dialogOff + 0xfb1020;
                        }
                    }
                    if (typePtr[-0x330] == 'C' && strcmp(imageName, g_6b5c60) != 0) {
                        resource = fcn_0042e770(imageName);
                        if (resource != -1) {
                            element = d2_ShowTxt(S16(coords), S16(coords + 0x60), ((char**)0x143a1c0)[resource], windowID);
                            g_00f8f080[element].f08 = fcn_0042e770(imageName);
                            g_00f8f080[element].f40 = dialogOff + 0xfb1020;
                        }
                    } else if (typePtr[-0x330] == 'A') {
                        aux = (unsigned char*)typePtr;
                        aux0 = aux[0];
                        element = fcn_0046a350(S16(coords), S16(coords + 0x60), aux[1], aux[2], aux0, windowID);
                        g_00f8f080[element].f40 = dialogOff + 0xfb1020;
                    } else if (typePtr[-0x330] == 'E') {
                        aux = (unsigned char*)typePtr;
                        aux0 = aux[0];
                        resource = fcn_00468880(imageName);
                        element = fcn_0046a950(S16(coords), S16(coords + 0x60), U8(record + 0xf1c + j), 0, 100, resource, aux0, windowID);
                        g_00f8f080[element].f40 = dialogOff + 0xfb1020;
                    }
                    j++;
                    coords += 2;
                    imageName += 0x40;
                    typePtr++;
                } while (j < S16(record + 0xcc));
            }
            if (record[0xe50]) {
                resource = fcn_0042e770(record + 0xe50);
                if (resource != -1) {
                    strcpy(*(char**)(window + 0x2c), ((char**)0x143a1c0)[resource]);
                }
                I32(window + 0x240) = resource;
            } else {
                I32(window + 0x240) = -1;
            }
            if (version == 0) {
                S16(window + 0x12) = S16(record + 0xe9e);
                S16(window + 0x10) = S16(record + 0xe9c);
                S16(window + 0x14) = S16(record + 0xea0);
                S16(window + 0x16) = S16(record + 0xea2);
                resource = S16(record + 0xe90);
                if (resource == 0) {
                    resource = fcn_00468880("_FONT");
                }
                S16(window + 0x27c) = (short)resource;
                if (I32(record + 0xe98) >= 1) {
                    I32(window + 0x388) = I32(record + 0xe98);
                }
            }
            i++;
            winSlot++;
            v2 += 0x101c;
            v1 += 0xed4;
        } while (i < count);
    }
    I32(dialogOff + 0xfb11b0) = 1;
    I32(dialogOff + 0xfb11bc) = 1;
    I32(dialogOff + 0xfb11c0) = 1;
    I32(dialogOff + 0xfb1020) = slot;
    I32(0x6ed958) = slot;
    I32(0x6ed984) = 0;
    strcpy((char*)(dialogOff + 0xfb124c), name);
    window = (char*)&g_00f8f120[I32(dialogOff + 0xfb1024)];
    if (x != 0 && y != 0) {
        fcn_0046cd90(x, y, I32(window + 0x26c));
    }
    if ((int)S16(window + 4) + S16(window + 8) > (int)S16(0xfb9072)) {
        fcn_0046cd90((short)(S16(0xfb9072) - S16(window + 8)), S16(window + 6), I32(window + 0x26c));
    }
    return slot;
}
