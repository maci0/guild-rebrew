#include <string.h>

#include "Develop/DieGildeAddOn/loadsave/loadsave.h"

extern char g_6b5c20;
extern int g_6b8010;
extern int g_6b7fdc;
extern int g_6a23ac;
extern char s_675504[];
extern char s_6a24a8[];
extern char s_6a2498[];
extern char s_6a2490[];
extern char s_68b0d8[];
extern char s_6a2430[];
extern char s_6a23e0[];
extern char s_699760[];
extern char s_699770[];
extern char s_699784[];

extern char* __cdecl fcn_00523710(void*);
extern char* __cdecl fcn_00508e40(int);
extern unsigned short* __cdecl fcn_00502cd0(int, int, ...);
extern int __cdecl fcn_0051ad90(int);
extern int __cdecl fcn_004fda30(int);
extern int __cdecl fcn_0042f690(char*, void*, void*, char*);
extern void __cdecl fcn_0066080a(char*);
extern int __cdecl ch_CreateMesh(void*, char*, void*);
extern void __cdecl fcn_00407800(void*, int, void*);
extern void __cdecl fcn_0040c360(void*, void*);
extern void __cdecl fcn_00438cb0(void*, void*);
extern void __cdecl fcn_004ce9e0(void*);
extern void __cdecl fcn_00510820(void*, void*, int);
extern char* __cdecl fcn_00442910(int, void*, void*, char*);
extern char* __cdecl fcn_0050d430(void*);
extern char __cdecl SelectTextureSet(void*, void*, unsigned char, char);
extern int __cdecl fcn_00403ce0(void*, void*);
extern void __cdecl fcn_00402a00(void*, int);
extern void __cdecl fcn_00405130(void*);
extern int __cdecl fcn_004432d0(int, int);
extern unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
extern int __cdecl fcn_00515540(char*);
extern int __cdecl fcn_005155e0(char*);

/* ADDRESS: GOLDTL 0x005238c0 */

/* Laedt die gespeicherten Figurendatensaetze, wandelt gespeicherte
 * Aktions-/Lagerkennungen zurueck in Zeiger und baut die Meshes neu auf. */
unsigned int __cdecl ls_LoadCharacter(unsigned int stream)
{
	char name[128];
	char path[260];
	char text[260];
	char* e;
	char* rec;
	char* target;
	char* base;
	char* p;
	unsigned short* found;
	unsigned short* alloc;
	unsigned int** list;
	unsigned int* u;
	int count;
	int total;
	int i;
	int n;
	int v;
	int tex;
	unsigned char type;
	unsigned char t;

	found = 0;
	alloc = 0;
	count = 0;
	total = g_6b8010;
	if (!ls_ReadVfsDataChecked(&count, 4, 1, (void*) stream)) {
		return 0;
	}
	i = 0;
	if (count >= 1) {
		do {
			e = fcn_00523710((void*) stream);
			*(char**) (e + 0x12c) = fcn_00508e40((int) *(char**) (e + 0x12c));
			i++;
		} while (i < count);
	}
	if (!ls_ReadVfsDataChecked(&count, 4, 1, (void*) stream)) {
		return 0;
	}
	i = 0;
	if (count >= 1) {
		do {
			e = fcn_00523710((void*) stream);
			*(unsigned short**) (e + 0x12c) =
				fcn_00502cd0(0, 2, 7, 1, *(unsigned int*) (e + 0x12c));
			i++;
		} while (i < count);
	}
	list = (unsigned int**) 0x14d0020;
	do {
		rec = (char*) *list;
		if (rec != 0) {
			alloc = 0;
			found = gm_StartFilteredEntitySearch(1, (int) *(unsigned int*) (rec + 0x2c));
			if (found != 0) {
				alloc = fcn_00502cd0((int) *(unsigned int*) ((char*) found + 0x5d),
						     2, 6, 1, *(unsigned int*) (rec + 0x30));
				if (alloc != 0 && *(short*) alloc != 0xfd) {
					v = fcn_00515540((char*) alloc);
				} else {
					v = fcn_005155e0((char*) found);
				}
			} else {
				v = 0;
			}
			fcn_004432d0(v, 1);
			sprintf(name, s_675504, rec + 0x170, rec + 0x130);
			if (strstr(name, s_6a24a8) != 0) {
				sprintf(name, s_6a2498, rec + 0x130);
			}
			sprintf(path, s_6a2490, name);
			fcn_0066080a(path);
			if (fcn_0042f690(path, &g_6b7fdc, &g_6b7fdc, text) == 0) {
				p = *(char**) (rec + 0x12c);
				t = *(unsigned short*) p;
				p[0x1f4] = 0;
				strcpy(rec + 0x170, (char*) (fcn_004fda30(t) + 4));
				p = strchr(rec + 0x170, '_');
				if (p != 0) {
					strcpy(p + 1, rec + 0x130);
					*p = 0;
				}
				sprintf(name, s_675504, rec + 0x170, rec + 0x130);
			}
			ch_CreateMesh(rec, name, rec + 0x38);
			if (found != 0) {
				*(unsigned int*) (rec + 0x2c) = *(unsigned int*) ((char*) found + 1);
			}
			if (alloc != 0) {
				*(unsigned int*) (rec + 0x30) = *(unsigned int*) ((char*) alloc + 2);
			}
			if (*(int*) (rec + 0x34) != 0) {
				if (*(char*) (rec + 0x1a8) != 0) {
					fcn_00407800(rec, 2, rec + 0x1a8);
				}
				if (*(char*) (rec + 0x1e8) != 0) {
					p = strchr(rec + 0x1e8, '_');
					if (p != 0) {
						*p = 0;
					}
					fcn_0040c360(rec, rec + 0x1e8);
				}
				u = *(unsigned int**) (rec + 0x12c);
				if (u != 0) {
					target = (char*) *(int*) (rec + 0x34);
					if ((unsigned int) u >= 0x7f4ca0 && (unsigned int) u < 0x85a0a0) {
						fcn_00438cb0(target, rec + 0x48);
						sprintf(target, s_68b0d8, u[1]);
						*(unsigned int*) (target + 0x204) = (unsigned int) u;
						*(unsigned int*) (target + 0x48) = *u | 0x3000000;
						*(unsigned int*) ((char*) u + 0x184) = (unsigned int) rec;
						if (*(char**) ((char*) u + 0x17c) != 0) {
							*(char*) ((char*) u + 0x180) = **(char**) ((char*) u + 0x17c);
						}
						fcn_004ce9e0(u);
					} else {
						fcn_00510820(target, u, 1);
						sprintf(target, s_68b0d8, u[2]);
						type = *(unsigned char*) u;
						*(unsigned int*) ((char*) u + 0x3b) = (unsigned int) rec;
						if (type == 0x34 && *(unsigned short*) u == 0x134) {
							found = (unsigned short*) fcn_00442910(0, rec + 0x38,
											      rec + 0x48, s_699784);
						} else if (*(unsigned short*) u == 0x135) {
							found = (unsigned short*) fcn_00442910(0, rec + 0x38,
											      rec + 0x48, s_699770);
						} else if (*(unsigned short*) u == 0x136) {
							found = (unsigned short*) fcn_00442910(0, rec + 0x38,
											      rec + 0x48, s_699760);
						} else {
							found = 0;
						}
						if (found != 0) {
							e = fcn_0050d430(u);
							if (e != 0 && *(int*) (e + 0x54) != 0
							    && (*(unsigned char*) (e + 2) == 5
								|| *(unsigned char*) (e + 2) == 6
								|| *(unsigned char*) (e + 2) == 7)) {
								*(unsigned char*) &tex = *(unsigned char*) (e + 0x54) + 0x67;
							} else {
								*(unsigned char*) &tex = 0;
							}
							SelectTextureSet(found, *(void**) ((char*) found + 0x1cc),
									 (unsigned char) tex, 1);
							fcn_00403ce0(rec, found);
							*(unsigned int*) ((char*) found + 0x224) = 1;
							fcn_00510820(found, u, 1);
						}
					}
				}
			}
			if ((*(unsigned char*) (rec + 0x8c) & 0x20) != 0) {
				fcn_00402a00(rec, 0);
			}
		}
		list++;
	} while ((int) list < 0x14d0c20);
	fcn_004432d0(total, 1);
	{
		unsigned int* buf;

		buf = (unsigned int*) g_6b5c20;
		*buf = 0;
		n = 0;
		if (g_6a23ac < 0x10044) {
			count = 0x300;
		} else if (g_6a23ac >= 0x10058) {
			count = 0x7d0;
		} else {
			count = 0x500;
		}
		i = 0;
		do {
			u = (unsigned int*) ((char*) buf + i);
			memset(u, 0, 0x194);
			if (!ls_ReadVfsDataChecked(&t, 1, 1, (void*) stream)) {
				return 0;
			}
			*(char*) ((char*) u + 9) = t;
			if (!ls_ReadVfsDataChecked((char*) u + 0xc, 4, 1, (void*) stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked((char*) u + 0x14, 4, 1, (void*) stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked((char*) u + 0x30, 0x20, 1, (void*) stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked((char*) u + 0x50, 0x20, 1, (void*) stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked((char*) u + 0xf0, 0xa0, 1, (void*) stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked((char*) u + 0x190, 1, 1, (void*) stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked((char*) u + 0x24, 4, 1, (void*) stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked((char*) u + 0x28, 4, 1, (void*) stream)) {
				return 0;
			}
			n++;
			i += 0x194;
		} while (n < count);
	}
	i = 0;
	do {
		rec = (char*) ((char*) g_6b5c20 + i);
		u = (unsigned int*) rec;
		type = *(unsigned char*) (rec + 9);
		if (type == 0) {
			goto check_actions;
		}
		v = (int) *(unsigned int*) ((char*) 0x14d0020 + u[5] * 4);
		u[5] = v;
		if (v == 0) {
			goto clear_record;
		}
		v = fcn_0051ad90((int) u[9]);
		u[9] = v;
		u[10] = fcn_0051ad90((int) u[10]);
		u[3] = 0;
		*u = *(unsigned int*) ((char*) 0x14d0c40 + (unsigned int) type * 0x4c);
		if (v == 0) {
			if (u[5] != 0) {
				if (*(int*) ((char*) u[5] + 0x128) != 0) {
					fcn_00405130(u[5]);
				}
				*(unsigned int*) ((char*) u[5] + 0x128) = (unsigned int) u;
			} else {
				sprintf(path, s_6a2430, type);
				*(char*) (rec + 9) = 0;
			}
		}
		if (*(char*) (rec + 9) == 0x33) {
			e = (char*) gm_StartFilteredEntitySearch(1, 1, u[0xd]);
			if (e != 0) {
				alloc = fcn_00502cd0((int) *(unsigned int*) (e + 0x5d),
						     2, 6, 1, u[0xe]);
				if (alloc != 0 && *(short*) alloc != 0xfd) {
					v = fcn_00515540((char*) alloc);
				} else {
					v = fcn_005155e0(e);
				}
				u[0xc] = v;
				u[0x5c] = v;
			} else {
				u[0xc] = 0;
				u[0x5c] = 0;
			}
		} else if (*(char*) (rec + 9) == 0x2d) {
			u[0x55] = 0xffffffff;
			u[0x3d] = 0;
		}
	check_actions:
		if (u[9] == 0xffffffff || u[10] == 0xffffffff) {
			sprintf(path, s_6a23e0, *(char*) (rec + 9));
			u[9] = 0;
			u[10] = 0;
			n = 0;
			do {
				if (*(unsigned int*) (g_6b5c20 + n + 0x28) == (unsigned int) u) {
					*(unsigned int*) (g_6b5c20 + n + 0x28) = 0;
				}
				if (*(unsigned int*) (g_6b5c20 + n + 0x24) == (unsigned int) u) {
					*(unsigned int*) (g_6b5c20 + n + 0x24) = 0;
				}
				n += 0x194;
			} while (n < 0xc5440);
		}
	clear_record:
		memset(rec, 0, 0x194);
		i += 0x194;
	} while (i < 0xc5440);
	return 1;
}
