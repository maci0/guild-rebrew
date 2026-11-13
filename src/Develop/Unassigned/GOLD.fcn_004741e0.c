#include <stdio.h>
#include <string.h>
#include "gold_gui.h"
extern GuiWin g_00f8f120[];
extern GuiEnt* g_00f8f080;
char* __cdecl fcn_00430470(char*, const char*, void*);
unsigned int __cdecl fcn_00430bd0(void*, unsigned int, unsigned int, char*);
int __cdecl fcn_00430fa0(char*, int, int);
void __cdecl fcn_00430aa0(char*);
int __cdecl fcn_00472380(short, short, short, short, unsigned int);
int __cdecl fcn_00472a90(short, short, short, short, unsigned int, int);
void __cdecl fcn_004721d0(char*, int);
int __cdecl fcn_00468880(char*);
void __cdecl d2_AddRefcount(int);
int __cdecl fcn_004731c0(short, short, int, int);
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
    char path[256] = "";
    char message[256];
    char header[5];
    char* file;
    int version;
    int count;
    int slot;
    char* dialog;
    int i;
    int j;
    char* record;
    char* window;
    char* parent;
    char* current;
    int parentID;
    int windowID;
    int resource;
    int element;
    char* imageName;
    unsigned char* aux;

    strcpy(path, name);
    if (!I32(0x6ed984)) {
        strcpy(path, "forms\\");
        strcat(path, name);
        strcat(path, ".form");
    }
    file = fcn_00430470(path, "rb", *(void**)0x6333fc);
    if (!file) {
        sprintf(message, "Konnte die Form\n %s\nnicht laden...", name);
        return -1;
    }
    fcn_00430bd0(header, 1, 4, file);
    version = header[3] - '0';
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
    for (slot = 1; slot < 0x30; slot++) {
        if (I32((char*)0xfb1020 + slot * 0x2ac + 0x184) == 0) {
            break;
        }
    }
    if (slot >= 0x30) {
        return -1;
    }
    dialog = (char*)0xfb1020 + slot * 0x2ac;
    I32(dialog + 0x194) = I32(0x6ed94c) - 1;
    for (i = 0; i < count; i++) {
        record = version == 2 ? (char*)0x68ce98 + i * 0x101c : (char*)0x633f18 + i * 0xed4;
        parentID = I32(record + (version == 2 ? 0xed0 : 0xe94));
        if (parentID) {
            parentID = I32(dialog + parentID * 4);
            parent = (char*)&g_00f8f120[parentID];
            windowID = fcn_00472a90((short)(S16(record) - S16(parent + 4)),
                (short)(S16(record + 2) - S16(parent + 6)), S16(record + 4), S16(record + 6),
                I32(record + 8), parentID);
        } else {
            windowID = fcn_00472380(S16(record), S16(record + 2), S16(record + 4), S16(record + 6), I32(record + 8));
        }
        I32(dialog + 4 + i * 4) = windowID;
        if (version == 2) {
            if (record[0xf4c]) {
                fcn_004721d0(record + 0xf4c, I32(0x6ed938));
            }
            current = (char*)&g_00f8f120[I32(0x6ed938)];
            if ((U8(current + 0xc) & 1) && F32(record + 0xf8c) == 0.0f) {
                F32(current + 0x394) = 0.65f;
            } else {
                I32(current + 0x394) = I32(record + 0xf8c);
            }
        }
        window = (char*)&g_00f8f120[windowID];
        if (version == 2) {
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
        g_00f8f080[I32(window + 0x26c)].f40 = (int)dialog;
        I32(dialog + 0x184)++;
        for (j = 0; j < S16(record + 0xcc); j++) {
            imageName = record + 0x190 + j * 0x40;
            aux = (unsigned char*)record + 0xd90 + j * 4;
            if (I32(record + 0xd0 + j * 4) <= 0x3f) {
                resource = fcn_00468880(imageName);
                if (resource != -1) {
                    element = fcn_004731c0(S16(record + 0xc + j * 2), S16(record + 0x6c + j * 2), resource, windowID);
                    if (I32(aux) == 0x12) {
                        g_00f8f080[element].dirty = 1;
                        g_00f8f080[element].f4c = 0;
                    }
                    if (I32(aux) == 8) {
                        g_00f8f080[element].dirty = 0;
                        g_00f8f080[element].f4c = 1;
                    }
                    g_00f8f080[element].f40 = (int)dialog;
                }
            }
            if (I32(record + 0xd0 + j * 4) == 'C') {
                if (strcmp(imageName, "") != 0) {
                    resource = fcn_0042e770(imageName);
                    if (resource != -1) {
                        element = d2_ShowTxt(S16(record + 0xc + j * 2), S16(record + 0x6c + j * 2), ((char**)0x143a1c0)[resource], windowID);
                        g_00f8f080[element].f08 = fcn_0042e770(imageName);
                        g_00f8f080[element].f40 = (int)dialog;
                    }
                }
            } else if (I32(record + 0xd0 + j * 4) == 'A') {
                element = fcn_0046a350(S16(record + 0xc + j * 2), S16(record + 0x6c + j * 2), aux[1], aux[2], aux[0], windowID);
                g_00f8f080[element].f40 = (int)dialog;
            } else if (I32(record + 0xd0 + j * 4) == 'E') {
                resource = fcn_00468880(imageName);
                element = fcn_0046a950(S16(record + 0xc + j * 2), S16(record + 0x6c + j * 2), U8(record + 0xf1c + j), 0, 100, resource, aux[0], windowID);
                g_00f8f080[element].f40 = (int)dialog;
            }
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
    }
    I32(dialog + 0x190) = 1;
    I32(dialog + 0x19c) = 1;
    I32(dialog + 0x1a0) = 1;
    I32(dialog) = slot;
    I32(0x6ed958) = slot;
    I32(0x6ed984) = 0;
    strcpy(dialog + 0x22c, name);
    window = (char*)&g_00f8f120[I32(dialog + 4)];
    if (x != 0 && y != 0) {
        fcn_0046cd90(x, y, I32(window + 0x26c));
    }
    if ((int)S16(0xfb9072) < (int)S16(window + 4) + S16(window + 8)) {
        fcn_0046cd90((short)(S16(0xfb9072) - S16(window + 8)), S16(window + 6), I32(window + 0x26c));
    }
    return slot;
}
