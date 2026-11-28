#include <stdio.h>
#include <string.h>
#pragma intrinsic(memset)
#include "Develop/Units/d2.v1/gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/d2_gui.h"

extern GOLD_GUI_WINDOW g_00f8f120[];
extern float flt_0_0;
extern char str_empty[];
extern int g_772560;
extern int g_1038580;
extern int g_772528;
extern int g_67d3a0;
extern int vfs_RootDir;
extern int g_1040494;
extern char s_67d268[];
extern char s_67d774[];
extern char s_67d474[];
extern char s_67d798[];
extern char* txt_TextEntries[];

void* __cdecl vfs_Tfopen(const char* name, const char* mode, void* root);
unsigned int __cdecl vfs_ReadData(void* buf, unsigned int size, unsigned int count, void* stream);
int __cdecl vfs_fseek(void* f, int off, int whence);
void __cdecl CloseVfsStream(void* f);
int __cdecl d2_CreateGuiWindow(short, short, short, short, unsigned int);
int __cdecl d2_CreateWindow(int a, int b, int c, int d, int e);
int __cdecl d2_CreateChildWindow(short, short, short, short, unsigned int, int);
void __cdecl d2_LoadBackgroundTexture(char*, int);
void __cdecl d2_SetBackgroundTexture(const char* name, int win);
int __cdecl fcn_00468880(char*);
int __cdecl d2_FindResourceByName(const char* name);
void __cdecl d2_AddRefcount(int);
int __cdecl d2_AddElementToWindow(short, short, int, int);
int __cdecl txt_FindEntryIndex(const char*);
int __cdecl d2_ShowTxt(short, short, char*, int);
int __cdecl d2_EqualizeWindowButtonWidths(int a, int b, int c, int d);
int __cdecl d2_AttachWindowInputIcon(int, int, int, int, unsigned char, int);
int __cdecl d2_AddWindowInputIcon(int a, int b, int c, int d, int e, int f);
int __cdecl d2_AddWindowSlider(int, int, unsigned char, int, int, int, unsigned char, int);
int __cdecl d2_AddWindowValueGauge(int a, int b, int c, int d, int e, int f, int g, int h);
void __cdecl d2_MoveElement(short, short, int);
void __cdecl d2_PositionControl(int x, int y, int slot);

#define I32(p) (*(int*)(p))
#define S16(p) (*(short*)(p))
#define U8(p) (*(unsigned char*)(p))
#define F32(p) (*(float*)(p))

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004741e0 */
int __cdecl d2_LoadForm(short x, short y, char* name)
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
    file = (char*)vfs_Tfopen(path, "rb", *(void**)0x6333fc);
    if (!file) {
        sprintf(message, "Konnte die Form\n %s\nnicht laden...", name);
        return -1;
    }
    vfs_ReadData(header, 1, 4, file);
    version = (signed char)header[3] - '0';
    header[4] = 0;
    if (version == 2) {
        vfs_ReadData(&count, 4, 1, file);
        vfs_ReadData((void*)0x68ce98, 0x101c, count, file);
    } else {
        version = 0;
        vfs_fseek(file, 0, 0);
        vfs_ReadData(&count, 4, 1, file);
        vfs_ReadData((void*)0x633f18, 0xed4, count, file);
    }
    CloseVfsStream(file);
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
                    *winSlot = d2_CreateGuiWindow(S16(v1), S16(v1 + 2), S16(v1 + 4), S16(v1 + 6), I32(v1 + 8));
                }
            } else if (ver == 2) {
                if (I32(v2)) {
                    parentID = I32((dialogWords + I32(v2)) * 4 + 0xfb1020);
                    parent = (char*)&g_00f8f120[parentID];
                    windowID = d2_CreateChildWindow((short)(S16(record) - S16(parent + 4)),
                        (short)(S16(v2 - 0xece) - S16(parent + 6)), S16(v2 - 0xecc), S16(v2 - 0xeca),
                        I32(v2 - 0xec8), parentID);
                } else {
                    windowID = d2_CreateGuiWindow(S16(record), S16(v2 - 0xece), S16(v2 - 0xecc), S16(v2 - 0xeca), I32(v2 - 0xec8));
                }
                *winSlot = windowID;
                if (v2[0x7c]) {
                    d2_LoadBackgroundTexture(v2 + 0x7c, d2_CurrentWindowId);
                }
                current = (char*)&g_00f8f120[d2_CurrentWindowId];
                if ((U8(current + 0xc) & 1) && F32(v2 + 0xbc) == flt_0_0) {
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
                    if (typePtr[-0x330] == 'C' && strcmp(imageName, str_empty) != 0) {
                        resource = txt_FindEntryIndex(imageName);
                        if (resource != -1) {
                            element = d2_ShowTxt(S16(coords), S16(coords + 0x60), ((char**)0x143a1c0)[resource], windowID);
                            g_00f8f080[element].f08 = txt_FindEntryIndex(imageName);
                            g_00f8f080[element].f40 = dialogOff + 0xfb1020;
                        }
                    } else if (typePtr[-0x330] == 'A') {
                        aux = (unsigned char*)typePtr;
                        aux0 = aux[0];
                        element = d2_AttachWindowInputIcon(S16(coords), S16(coords + 0x60), aux[1], aux[2], aux0, windowID);
                        g_00f8f080[element].f40 = dialogOff + 0xfb1020;
                    } else if (typePtr[-0x330] == 'E') {
                        aux = (unsigned char*)typePtr;
                        aux0 = aux[0];
                        resource = fcn_00468880(imageName);
                        element = d2_AddWindowSlider(S16(coords), S16(coords + 0x60), U8(record + 0xf1c + j), 0, 100, resource, aux0, windowID);
                        g_00f8f080[element].f40 = dialogOff + 0xfb1020;
                    }
                    j++;
                    coords += 2;
                    imageName += 0x40;
                    typePtr++;
                } while (j < S16(record + 0xcc));
            }
            if (record[0xe50]) {
                resource = txt_FindEntryIndex(record + 0xe50);
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
        d2_MoveElement(x, y, I32(window + 0x26c));
    }
    if ((int)S16(window + 4) + S16(window + 8) > (int)S16(0xfb9072)) {
        d2_MoveElement((short)(S16(0xfb9072) - S16(window + 8)), S16(window + 6), I32(window + 0x26c));
    }
    return slot;
}
#else
/* ADDRESS: GOLDTL 0x00470820 */
int __cdecl d2_LoadForm(int posX, int posY, char* formName)
{
	char v22[256];
	char formPath[256];
	char v23[8];
	int v40;
	int formCount;
	int v25;
	int* v26;
	int v27;
	int v28;
	int v29;
	int v30;
	int v31;
	int* v32;
	int* v33;
	int v34;
	int v35;
	int* v36;
	int v37;
	int v38;
	int* v39;
	int v41;
	int v42;
	int v43;
	int v44;
	int v45;
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	int v13;
	int v15;
	int* v10;
	int v11;
	int v12;
	int v17;
	int v16;
	int v18;
	int v19;
	int v20;
	int v3;
	int i;
	int* p;
	int* q;
	int* r;
	int* s;
	int* t;
	char* d;
	char* c;
	char ch;

	formPath[0] = str_empty[0];
	memset(formPath + 1, 0, 255);

	strcpy(formPath, formName);
	if (!g_772560) {
		strcpy(formPath, s_67d268);
		strcat(formPath, formName);
		strcat(formPath, ".form");
	}
	v15 = (int) vfs_Tfopen(formPath, (char*) 0x6750e8, (void*) vfs_RootDir);
	if (!v15) {
		sprintf(v22, s_67d774, formName);
		return -1;
	}
	vfs_ReadData(v23, 1, 4, (void*) v15);
	v40 = (signed char) v23[3] - 0x30;
	v23[4] = 0;
	if (v40 == 2) {
		vfs_ReadData((char*) &formCount, 4, 1, (void*) v15);
		vfs_ReadData((char*) 0x711a80, 0x101c, formCount, (void*) v15);
	} else {
		v40 = 0;
		vfs_fseek((void*) v15, 0, 0);
		vfs_ReadData((char*) &formCount, 4, 1, (void*) v15);
		vfs_ReadData((char*) 0x6b8b00, 0xed4, formCount, (void*) v15);
	}
	CloseVfsStream((void*) v15);
	v35 = 1;
	if (g_1038580) {
		v15 = 0x1038580;
		do {
			if (v15 >= 0x1040604)
				return -1;
			v26 = (int*) (v15 + 700);
			v15 += 700;
			v35++;
		} while (*(int*) v26);
		if (v35 >= 0x30)
			return -1;
	}
	v44 = 0;
	v15 = v35 * 700;
	*(int*) (v15 + 0x10382d4) = g_772528 - 1;
	if (formCount > 0) {
		v39 = (int*) 0x6b8b00;
		v36 = (int*) 0x712950;
		v43 = v35 * 0xaf;
		v32 = (int*) (v35 * 700 + 0x1038144);
		v44 = 0;
		do {
			v13 = v40;
			v10 = v39;
			v26 = (int*) ((char*) v36 - 0xed0);
			if (v40) {
				v33 = v26;
				if (v40 == 2) {
					if (*(int*) v36) {
						v45 = *(int*) ((*(int*) v36 + v43) * 4 + 0x1038140);
						v42 = v45 * 0x3cc + 0x1015f40;
						v11 = d2_CreateChildWindow(
							(short) ((short) *v26
							- *(short*) (v42 + 4)),
							(short) (*((short*) v36 - 0x767)
							- *(short*) (v42 + 8)),
							(short) v36[-0x3b3],
							(short) *((short*) v36 - 0x765),
							v36[-0x3b2], v45);
					} else {
						v11 = d2_CreateWindow(
							(short) *v26,
							(short) *((short*) v36 - 0x767),
							(short) v36[-0x3b3],
							(short) *((short*) v36 - 0x765),
							v36[-0x3b2]);
					}
					v8 = 0;
					*v32 = v11;
					if ((char) v36[0x1f])
						d2_SetBackgroundTexture((char*) &v36[0x1f],
							d2_CurrentWindowId);
					v11 = d2_CurrentWindowId * 0x3cc;
					if ((*(unsigned char*) (v11 + 0x1015f54) & 1)
						&& *(float*) ((char*) v36 + 0xbc)
						== flt_0_0)
						*(unsigned int*) (v11 + 0x10162e4) =
							0x3f266666;
					else
						*(int*) (v11 + 0x10162e4) =
							*(int*) ((char*) v36 + 0xbc);
				}
			} else {
				v33 = v39;
				v26 = v10;
				if (v39[0x3a5]) {
					v45 = *(int*) ((v39[0x3a5]
						+ v43) * 4 + 0x1038140);
					v42 = v45 * 0x3cc + 0x1015f40;
					v11 = d2_CreateChildWindow(
						(short) ((short) *v39
						- *(short*) (v42 + 4)),
						(short) (*((short*) v39 + 1)
						- *(short*) (v42 + 8)),
						(short) v39[1],
						(short) *((short*) v39 + 3),
						v39[2], v45);
					*v32 = v11;
				} else {
					v11 = v39[2];
					v5 = *((short*) v39 + 3);
					v8 = v39[1];
					v6 = *((short*) v39 + 1);
					v7 = *v39;
					*v32 = d2_CreateWindow(
						(short) v7, (short) v6,
						(short) v8, (short) v5, v11);
				}
			}
			v41 = *v32 * 0x3cc + 0x1015f40;
			if (v13 == 2) {
				if (*(char*) ((char*) v26 + 0xe90))
					p = (int*) ((char*) v26 + 0xe90);
				else
					p = (int*) s_67d474;
				v12 = d2_FindResourceByName((char*) p);
				*(unsigned int*) (v41 + 0x28c) = v12;
				if (*(char*) ((char*) v26 + 0xed4)) {
					v12 = d2_FindResourceByName(
						(char*) v26 + 0xed4);
					*(unsigned int*) (v41 + 0x398) =
						v12;
					d2_AddRefcount(v12);
				}
				v13 = v26[0x3c6];
				v5 = *(short*) ((char*) v26 + 0xf16);
				*(int*) (v41 + 0x18) =
					(short) v26[0x3c5];
				*(int*) (v41 + 0x20) = (short) v13;
				v6 = *(short*) ((char*) v26 + 0xf1a);
				*(int*) (v41 + 0x1c) = (int) v5;
				*(int*) (v41 + 0x24) = (int) v6;
				if (*(unsigned char*) (v41 + 0x14) & 4) {
					v13 = d2_FindResourceByName(
						(char*) v26 + 0xf90);
					*(int*) (v41 + 0x288) = v13;
					if (v13 == -1)
						*(unsigned int*) (v41 + 0x288)
							= g_67d3a0;
				}
			}
			v38 = 0;
			*(int*) (&((D2_CONTROL_TL*)d2_Controls)[*(int*) (*(int*) v32 * 0x3cc + 0x10161bc)].value_050)
				= v15 + 0x1038140;
			v34 = *v32;
			v13 = v33[0x33];
			*(int*) (v15 + 0x10382c4) =
				*(int*) (v15 + 0x10382c4) + 1;
			if ((short) v13 >= 1) {
				q = (int*) ((char*) v33 + 0xc);
				v19 = (int*) ((char*) v33 + 0x190);
				t = (int*) ((char*) v33 + 0xd90);
				do {
					if (t[-0x330] <= 0x3f) {
						v12 = d2_FindResourceByName((char*) v19);
						v13 = d2_AddElementToWindow((short) *q,
							(short) q[0x18], v12, v34);
						if (*t == 0x12) {
							*(unsigned int*) (&((D2_CONTROL_TL*)d2_Controls)[v13].value_058) = 1;
							*(unsigned int*) (&((D2_CONTROL_TL*)d2_Controls)[v13].value_05c) = 0;
						}
						if (*t == 8) {
							*(unsigned int*) (&((D2_CONTROL_TL*)d2_Controls)[v13].value_058) = 0;
							*(unsigned int*) (&((D2_CONTROL_TL*)d2_Controls)[v13].value_05c) = 1;
						}
						*(int*) (&((D2_CONTROL_TL*)d2_Controls)[v13].value_050) =
							v15 + 0x1038140;
					}
					if (t[-0x330] == 0x43) {
						if (strcmp((char*) v19,
							str_empty) != 0) {
							v13 = txt_FindEntryIndex(
								(char*) v19);
							if (v13 != -1) {
								v12 = d2_EqualizeWindowButtonWidths(
									(short) *q,
									(short) q[0x18],
									*(int*) (v13 * 4
										+ 0x14a5320),
									v34);
								v13 = v12 * 0x2f4;
								*(unsigned int*) (&((D2_CONTROL_TL*)(d2_Controls + v13))->value_008) =
									txt_FindEntryIndex(
									(char*) v19);
								*(int*) (&((D2_CONTROL_TL*)(d2_Controls + v13))->value_050) =
									v15 + 0x1038140;
							}
						}
					} else if (t[-0x330] == 0x41) {
						v37 = *t & 0xff;
						v13 = d2_AddWindowInputIcon(
							(short) *q,
							(short) q[0x18],
							*(unsigned char*) ((char*) t + 1),
							*(unsigned char*) ((char*) t + 2),
							v37, v34);
						*(int*) (&((D2_CONTROL_TL*)d2_Controls)[v13].value_050) =
							v15 + 0x1038140;
					} else if (t[-0x330] == 0x45) {
						v37 = *t & 0xff;
						v12 = d2_FindResourceByName(
							(char*) v19);
						v13 = d2_AddWindowValueGauge(
							(short) *q,
							(short) q[0x18],
							*(unsigned char*) ((char*) v33
								+ v38 + 0xf1c),
							0, 100, v12,
							v37, v34);
						*(int*) (&((D2_CONTROL_TL*)d2_Controls)[v13].value_050) =
							v15 + 0x1038140;
					}
					t++;
					v38++;
					q = (int*) ((char*) q + 2);
					v19 = (int*) ((char*) v19 + 0x40);
				} while (v38 < (short) v33[0x33]);
			}
			if (*(char*) ((char*) v33 + 0xe50)) {
				v13 = txt_FindEntryIndex(
					(char*) v33 + 0xe50);
				if (v13 != -1) {
					p = (int*) *(char**) (v13 * 4
						+ 0x14a5320);
					d = *(char**) (v41 + 0x3c);
					do {
						ch = *(char*) p;
						p = (int*) ((char*) p + 1);
						*d = ch;
						d++;
					} while (ch);
				}
				*(int*) (v41 + 0x250) = v13;
			} else {
				*(unsigned int*) (v41 + 0x250) = 0xffffffff;
			}
			if (!v40) {
				v5 = *(short*) ((char*) v33 + 0xe9e);
				v11 = v33[0x3a8];
				*(int*) (v41 + 0x18) = (short) v33[0x3a7];
				*(int*) (v41 + 0x1c) = (int) v5;
				v5 = *(short*) ((char*) v33 + 0xea2);
				*(int*) (v41 + 0x20) = (short) v11;
				*(int*) (v41 + 0x24) = (int) v5;
				if (*(short*) ((char*) v33 + 0xe90))
					v11 = *(short*) ((char*) v33 + 0xe90);
				else
					v11 = d2_FindResourceByName(s_67d474);
				v8 = v33[0x3a6];
				*(int*) (v41 + 0x28c) = v11;
				if (v8 > 0)
					*(int*) (v41 + 0x398) = v8;
			}
			v44++;
			v32++;
			v36 += 0x407;
			v39 += 0x3b5;
		} while (v44 < formCount);
	}
	v13 = v35;
	*(unsigned int*) (v15 + 0x10382d0) = 1;
	*(unsigned int*) (v15 + 0x10382dc) = 1;
	*(unsigned int*) (v15 + 0x10382e0) = 1;
	*(int*) (v15 + 0x1038140) = v35;
	g_772534 = v35;
	g_772560 = 0;
	strcpy((char*) (v15 + 0x1038374), formName);
	v41 = *(int*) (v15 + 0x1038144) * 0x3cc + 0x1015f40;
	if (posX || posY)
		d2_PositionControl(posX, posY,
			*(int*) (v41 + 0x27c));
	if (*(int*) (v41 + 4) + *(int*) (v41 + 0xc)
		> g_1040494)
		d2_PositionControl(g_1040494 - *(int*) (v41 + 0xc),
			*(int*) (v41 + 8),
			*(int*) (v41 + 0x27c));
	return v13;
}
#endif
