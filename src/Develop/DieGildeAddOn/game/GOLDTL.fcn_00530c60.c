#include <stdio.h>
#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "client_types.h"
extern char* g_7746cc;
#include "game_data.h"
typedef struct JobProto { unsigned char kind; unsigned char rest[0x24c]; } JobProto;
extern char g_7f4ca4[];
extern unsigned int g_6a2520;

extern int g_67a370;
extern float g_696540[];
extern float g_696550[];
extern int g_6b7fdc;

extern pos14_7f4c00 gm_GameTime;
extern s_7e2ac0 g_7e2ac0[48];

int __cdecl gm_GetSeason(int*);
int __cdecl he_FindActionMetaName(char*, int, char*);
int __cdecl cm_GetCommandStatus(unsigned int);
int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(void*);
char* __cdecl evt_LoadScript(char*);
int __cdecl vfs_LookupPath(char*, void*, void**);
int __cdecl fcn_00428340(char*, int, ...);
void __cdecl init_GetGebaeudeSceneName(int, char*);

/* ADDRESS: GOLDTL 0x00530c60 */
void __cdecl fcn_00530c60(unsigned char* building)
{
	int mode;
	int id;
	int stop;
	int hit;
	int j;
	int k;
	int i;
	int hour;
	int n;
	int r;
	int c;
	char* itemdef;
	BUILDING_PROTOTYPE* type_row;
	char* ent;
	char* info;
	char* info2;
	char* p;
	char* h;
	char* s;
	char* script;
	void* found;
	char job[0x60];
	char name[0x80];
	char path[0x80];
	char sp[0x80];
	int flags[8];

	itemdef = 0;
	if (g_7746cc != 0 && *(unsigned short*) g_7746cc != 0xfd) {
		itemdef = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) g_7746cc]);
	}
	type_row = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*building];
	if ((unsigned int)g_6b7fac > g_6a2520 + 500) {
		if (g_67a370 != 0) {
			info = *(char**) (g_67a370 + 0x3c8);
			if (info != 0 && *(int*) (info + 0x318) != 0) {
				((void (__cdecl*) (int, int, int, int)) *(int*) (info + 0x318)) (g_67a370, 6, (int) (info + 0x31c), 0);
			}
		}
		g_6a2520 = g_6b7fac;
	}
	hour = gm_GetSeason((int*) &gm_GameTime);
	i = 0;
	do {
		ent = ch_ContextCharacters[i];
		if (ent != 0 && (info = *(char**) (ent + 0x184)) != 0
		    && *(int*) (info + 0x2c) == *(int*) (building + 1)
		    && *(unsigned char*) (ent + 8) > 0
		    && *(int*) (info + 0x88) == g_67a370) {
			mode = 0;
			job[0] = 0;
			r = he_FindActionMetaName(ent, (int) building, job);
			if (r != 0) {
				if (type_row->category == 0x0d) {
					if (g_7746cc != 0) {
						if (*(unsigned short*) g_7746cc == 0x37
						    && *(int*) (*(char**) (ent + 0x184) + 0x30) == *(int*) (g_7746cc + 2)) {
							mode = 1;
						}
						else if (*(unsigned short*) g_7746cc == 0xfd
						         && *(int*) (*(char**) (ent + 0x184) + 0x30) == *(int*) (g_7746cc + 2)) {
							p = *(char**) (ent + 0x17c);
							mode = 1;
							if (p != 0 && *(int*) (p + 0xc8) != 0) {
								mode = 0;
							}
						}
					}
					else {
						p = *(char**) (ent + 0x17c);
						mode = 1;
						if (p != 0 && *(int*) (p + 0xc8) != 0) {
							mode = 0;
						}
					}
				}
				else {
					if (type_row->category == 8 && *(unsigned short*) g_7746cc == 0xdd
					    && *(char*) (ent + 0x180) == 0x15) {
						mode = 1;
					}
					else {
						p = *(char**) (ent + 0x17c);
						mode = 1;
						if (p != 0 && *p == 4 && *(int*) (p + 0xc8) != 0) {
							mode = 0;
						}
					}
				}
			}
			else {
				if (type_row->category == 0x16 && g_7746cc != 0 && *(unsigned short*) g_7746cc == 0x120
				    && *(int*) (*(char**) (ent + 0x184) + 0x30) == *(int*) (g_7746cc + 2)
				    && (*(unsigned int*) (ent + 0x1c8) & 0x1000) == 0) {
					strcpy(job, "besucher");
					mode = 1;
				}
				else if (type_row->category == 1 && *(char**) (ent + 0x170) == (char*) building
				         && (*(unsigned int*) (ent + 0x1c8) & 0x1000) == 0) {
					strcpy(job, "bewohner");
					mode = 1;
				}
				else if (*(char*) (ent + 0x180) == 0 && *(char**) (ent + 0x16c) == (char*) building
				         && *(int*) (*(char**) (ent + 0x184) + 0x28) == -1) {
					if (*(char*) (ent + 0x164)) {
						strcpy(job, "meister");
					}
					else if (*(char*) (ent + 0x165) == 0x1c
					         && (*(unsigned char*) (ent + 0x1b4) & 1)) {
						strcpy(job, "faulenzen");
					}
					else {
						strcpy(job, "pause");
					}
					mode = 1;
				}
			}
			if (*(char*) (ent + 0x165) == 0x1c && (*(unsigned char*) (ent + 0x1b4) & 1)
			    && *(int*) (*(char**) (ent + 0x184) + 0x28) == -1) {
				strcpy(job, "faulenzen");
				mode = 1;
			}
			if (mode && job[0] != 0) {
				info = *(char**) (ent + 0x184);
				if (*(int*) (info + 0x28) != -1 && evt_FindScriptById(*(int*) (info + 0x28)) != 0) {
					/* already running */
				}
				else if (*(int*) (info + 0x28) == -1) {
					k = 0;
					while (k < 8) {
						flags[k] = 1;
						k += 1;
					}
					for (j = 0; j < 32; j++) {
						info2 = ch_ContextCharacters[j];
						if (info2 != 0 && (info2 = *(char**) (info2 + 0x184)) != 0
						    && (id = *(int*) (info2 + 0x28)) != -1
						    && (h = evt_FindScriptById(id)) != 0
						    && (s = strstr(h, job)) != 0) {
							n = strlen(job);
							c = s[n] - '0';
							if (c < 0 || c > 9) {
								break;
							}
							flags[c] = 0;
						}
					}
					k = 0;
					while (k < 8) {
						if (flags[k]) {
							break;
						}
						k += 1;
					}
					if (*(char*) (ent + 0x180) == 0x16) {
						strcpy(name, "Training_Allgemein");
					} else {
						if (itemdef == 0) {
							init_GetGebaeudeSceneName((int) *building, name);
						} else {
							strcpy(name, itemdef + 1);
						}
					}
					sprintf(path, "%slocations\\%s\\%s%i_%s.esc", "x:\\engine\\gfx\\scripts\\",
					        name, job, k, name);
					if (!vfs_LookupPath(path, (void*) g_6b7fdc, &found)) {
						sprintf(path, "%slocations\\%s\\%s0_%s.esc", "x:\\engine\\gfx\\scripts\\",
						        name, job, name);
					}
					if (vfs_LookupPath(path, (void*) g_6b7fdc, &found)) {
						sprintf(sp, "sp_%i", *(int*) (ent + 4));
						script = evt_LoadScript(path);
						if (script != 0) {
							fcn_00428340(script, 1, sp);
							*(int*) (script + 0xc94) = (int) info;
							*(int*) (info + 0x28) = *(int*) (script + 0x100);
						}
					}
				}
			}
			else {
				stop = 0;
				if (*(char**) (ent + 0x16c) == (char*) building
				    && (info = *(char**) (ent + 0x184)) != 0
				    && (id = *(int*) (info + 0x28)) != -1) {
					if (*(char*) (ent + 0x180) == 0
					    || (float) (gm_GameTime.b & 0xffff) > g_696550[hour]) {
						stop = 1;
					}
					p = *(char**) (ent + 0x17c);
					if ((p != 0 && *p == 4 && *(int*) (p + 0xc8) != 0) || stop) {
						hit = 0;
						h = evt_FindScriptById(id);
						if (h != 0) {
							for (j = 0; j < 48; j++) {
								if (hit) {
									break;
								}
								if (g_7e2ac0[j].key != 0 && *(char*) g_7e2ac0[j].pad != 0
								    && strstr(h, (char*) g_7e2ac0[j].pad) != 0) {
									hit = 1;
								}
							}
							if (hit) {
								evt_RequestScriptExit(h);
							}
						}
					}
				}
			}
		}
		i += 1;
	} while (i < 0x20);
}
