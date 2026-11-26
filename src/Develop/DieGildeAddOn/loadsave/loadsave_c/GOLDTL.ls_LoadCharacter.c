#include <string.h>

#include "Develop/DieGildeAddOn/loadsave/loadsave.h"

extern char* g_6b5c20;
extern int d3_CurrentContextIndex;
extern int g_6b7fdc;
extern int ls_SaveVersion;
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

extern char* __cdecl ls_ReadCharacterRecord(void*);
extern char* __cdecl gm_LookupEntityRecordById(int);
extern unsigned short* __cdecl fcn_00502cd0(int, int, ...);
extern int __cdecl ch_GetQueueEntryByIndex(int);
extern int __cdecl gm_SelectEntityHeadSet(int);
extern int __cdecl vfs_ResolvePath(char*, void*, void*, char*);
extern int __cdecl ch_CreateMesh(void*, char*, void*);
extern void __cdecl ch_SetBodyAttachment(void*, int, void*);
extern void __cdecl ch_StartLoopingAnimation(void*, void*);
extern void __cdecl d3_SetObjectRotation(void*, void*);
extern void __cdecl ch_UpdateHeldObjectAttachment(void*);
extern void __cdecl d3_BindEntitySceneObject(void*, void*, int);
extern char* __cdecl fcn_00442910(int, void*, void*, char*);
extern char* __cdecl gm_ResolveEntityOwnerBuilding(void*);
extern char __cdecl SelectTextureSet(void*, void*, unsigned char, char);
extern int __cdecl ch_AttachTransport(void*, void*);
extern void __cdecl ch_SetVisible(void*, int);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
extern int __cdecl d3_SelectSceneContext(int, int);
extern unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
extern int __cdecl init_EnsureObjektSceneContext(char*);
extern int __cdecl init_AllocateGebaeudeSceneSlot(char*);


/* Laedt die gespeicherten Figurendatensaetze, wandelt gespeicherte
 * Aktions-/Lagerkennungen zurueck in Zeiger und baut die Meshes neu auf. */
/* ADDRESS: GOLDTL 0x005238c0 */
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
	unsigned short template_id;

	found = 0;
	alloc = 0;
	count = 0;
	total = d3_CurrentContextIndex;
	if (!ls_ReadVfsDataChecked(&count, 4, 1, (void*) stream)) {
		return 0;
	}
	i = 0;
	if (count > 0) {
		do {
			e = ls_ReadCharacterRecord((void*) stream);
			*(char**) (e + 0x12c) = gm_LookupEntityRecordById((int) *(char**) (e + 0x12c));
			i++;
		} while (i < count);
	}
	if (!ls_ReadVfsDataChecked(&count, 4, 1, (void*) stream)) {
		return 0;
	}
	i = 0;
	if (count > 0) {
		do {
			e = ls_ReadCharacterRecord((void*) stream);
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
			found = gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (rec + 0x2c));
			if (found != 0) {
				alloc = fcn_00502cd0((int) *(unsigned int*) ((char*) found + 0x5d),
						     2, 6, 1, *(unsigned int*) (rec + 0x30));
				if (alloc != 0 && *(short*) alloc != 0xfd) {
					v = init_EnsureObjektSceneContext((char*) alloc);
				} else {
					v = init_AllocateGebaeudeSceneSlot((char*) found);
				}
			} else {
				v = 0;
			}
			d3_SelectSceneContext(v, 1);
			sprintf(name, s_675504, rec + 0x170, rec + 0x130);
			if (strstr(name, s_6a24a8) != 0) {
				sprintf(name, s_6a2498, rec + 0x130);
			}
			sprintf(path, s_6a2490, name);
			_strupr(path);
			if (vfs_ResolvePath(path, (void*) g_6b7fdc, (void*) g_6b7fdc, text) == 0) {
				p = *(char**) (rec + 0x12c);
				template_id = *(unsigned short*) p;
				p[0x1f4] = 0;
				strcpy(rec + 0x170, (char*) (gm_SelectEntityHeadSet(template_id) + 4));
				p = strchr(rec + 0x170, '_');
				if (p != 0) {
					strcpy(rec + 0x130, p + 1);
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
					ch_SetBodyAttachment(rec, 2, rec + 0x1a8);
				}
				if (*(char*) (rec + 0x1e8) != 0) {
					p = strchr(rec + 0x1e8, '_');
					if (p != 0) {
						*p = 0;
					}
					ch_StartLoopingAnimation(rec, rec + 0x1e8);
				}
				u = *(unsigned int**) (rec + 0x12c);
				if (u != 0) {
					target = (char*) *(int*) (rec + 0x34);
					if ((unsigned int) u >= 0x7f4ca0 && (unsigned int) u < 0x85a0a0) {
						d3_SetObjectRotation(target, rec + 0x48);
						sprintf(target, s_68b0d8, u[1]);
						*(unsigned int*) (target + 0x204) = (unsigned int) u;
						*(unsigned int*) (target + 0x48) = (unsigned int) *(unsigned short*) u | 0x3000000;
						*(unsigned int*) ((char*) u + 0x184) = (unsigned int) rec;
						if (*(char**) ((char*) u + 0x17c) != 0) {
							*(char*) ((char*) u + 0x180) = **(char**) ((char*) u + 0x17c);
						}
						ch_UpdateHeldObjectAttachment(u);
					} else {
						d3_BindEntitySceneObject(target, u, 1);
						target = *(char**) (rec + 0x34);
						sprintf(target, s_68b0d8, *(unsigned int*) ((char*) u + 2));
						type = *(unsigned char*) u;
						*(unsigned int*) ((char*) u + 0x3b) = (unsigned int) rec;
						if (*(unsigned short*) u == 0x134) {
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
							e = gm_ResolveEntityOwnerBuilding(u);
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
							ch_AttachTransport(rec, found);
							*(unsigned int*) ((char*) found + 0x224) = 1;
							d3_BindEntitySceneObject(found, u, 1);
						}
					}
				}
			}
			if ((*(unsigned char*) (rec + 0x8c) & 0x20) != 0) {
				ch_SetVisible(rec, 0);
			}
		}
		list++;
	} while ((int) list < 0x14d0c20);
	d3_SelectSceneContext(total, 1);
	{
		*(unsigned int*) g_6b5c20 = 0;
		n = 0;
		if (ls_SaveVersion < 0x10044) {
			count = 0x300;
		} else if (ls_SaveVersion < 0x10058) {
			count = 0x500;
		} else {
			count = 0x7d0;
		}
		i = 0;
		do {
			u = (unsigned int*) (g_6b5c20 + i);
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
		v = ch_GetQueueEntryByIndex((int) u[9]);
		u[9] = v;
		u[10] = ch_GetQueueEntryByIndex((int) u[10]);
		u[3] = 0;
		*u = *(unsigned int*) ((char*) 0x14d0c40 + (unsigned int) type * 0x4c);
		if (v == 0) {
			if (u[5] != 0) {
				if (*(int*) ((char*) u[5] + 0x128) != 0) {
					ch_ClearActionQueue((void*) u[5]);
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
					v = init_EnsureObjektSceneContext((char*) alloc);
				} else {
					v = init_AllocateGebaeudeSceneSlot(e);
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
			sprintf(path, s_6a23e0, *(unsigned char*) (rec + 9));
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
	clear_record:
			memset(rec, 0, 0x194);
		}
		i += 0x194;
	} while (i < 0xc5440);
	return 1;
}
