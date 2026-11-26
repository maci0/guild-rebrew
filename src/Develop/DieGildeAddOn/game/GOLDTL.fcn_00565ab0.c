#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include <stdio.h>
#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;
extern char g_7f4ca4[];
extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;
extern void* g_6b7fdc;
extern int d3_CurrentContextIndex;
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_004bcc50(char*, int);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl cm_GetCommandStatus(unsigned int);
int __cdecl init_AllocateGebaeudeSceneSlot(unsigned char*);
void __cdecl he_FreeAction(void*);
void __cdecl he_AssignActionSlot(char*, int, int, int);
char* __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(char*);
char* __cdecl evt_LoadScript(char*);
int __cdecl vfs_LookupPath(char*, void*, void**);
int __cdecl fcn_00428340(char*, int, ...);
void __cdecl fcn_004c5aa0(int, char, char, short, char, int);
char* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl cm_SendSellObjekt(int, int, unsigned int, int, char, int);
void __cdecl cm_SendCopyEntityData(int);
void __cdecl gm_AddTime(void*, int, int, int);
char* __cdecl plt_FindPlantInfo(int);

/* ADDRESS: GOLDTL 0x00565ab0 */
void __cdecl he_UpdateErnten(char* ev)
{
	char* v8;
	char* plantInfo;
	char* v4;
	char* v15;
	char* v24;
	char spname[0x40];
	char pkt[0xf8];
	char path[0x80];
	char erm[0x80];
	char* v5;

	v4 = (char*) gm_StartFilteredEntitySearch(1, 1, *(int*) (ev + 0xac));
	if (v4 != 0) {
		v24 = *(char**) (v4 + 0x71);
		v5 = fcn_004bcc50(v24, *(int*) (ev + 0xb8));
		v15 = gm_LookupEntityRecordById(*(int*) (ev + 0xb0));
		if (v5 != 0) {
			if (v15 != 0) {
				if (*(int*) (v5 + 0x10) == -1 || *(int*) (v5 + 0x10) == *(int*) (ev + 4)) {
					v8 = *(char**) (v15 + 0x184);
					plantInfo = plt_FindPlantInfo(*(unsigned short*) (v5 + 0xa));
					switch (*(int*) (ev + 0x70)) {
					case 0:
						if (!cm_GetCommandStatus(*(int*) (ev + 0xc0))) {
							return;
						}
						if (d3_CurrentContextIndex == init_AllocateGebaeudeSceneSlot((unsigned char*) v4)) {
							void* found;
							char* ent = (char *)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned char)*v4];

							sprintf(erm, "Ernten_start_%s", plantInfo + 2);
							sprintf(path, "%slocations/%s/%s_%s.esc", "x:\\engine\\gfx\\scripts\\",
							        ent + 1, erm, ent + 1);
							if (vfs_LookupPath(path, g_6b7fdc, &found)) {
								char* script = evt_LoadScript(path);

								if (script != 0) {
									sprintf(spname, "sp_%i", *(int*) (ev + 0xb0));
									fcn_00428340(script, 3, spname, *(int*) (v5 + 0x14),
									             (int) *(char*) (v5 + 0xd) / (int) *(unsigned char*) (plantInfo + 0x43));
									*(int*) (script + 0xc94) = (int) v8;
									*(int*) (v8 + 0x28) = *(int*) (script + 0x100);
									*(int*) (ev + 0xb4) = *(int*) (script + 0x100);
								}
							}
						}
						else {
							*(int*) (ev + 0xc0) = -1;
						}
						*(pos14_7f4c00*) (ev + 0x52) = gm_GameTime;
						gm_AddTime(ev + 0x52, 0, 0, 1);
						*(int*) (ev + 0x70) = *(int*) (ev + 0x70) + 1;
						return;
					case 1:
						*(int*) (ev + 0xc0) = -1;
						{
							unsigned short type = *(unsigned short*) (v5 + 0xa);
							char* def = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[type]);

							*(pos14_7f4c00*) (ev + 0x52) = gm_GameTime;
							gm_AddTime(ev + 0x52, 0,
							             (int) ((double) (*(char*) (v5 + 0xd) * ((OBJECT_PROTOTYPE *)def)->value_022) * 0.25), 0);
						}
						*(int*) (ev + 0x70) = *(int*) (ev + 0x70) + 1;
						return;
					case 2:
						if (*(int*) (ev + 0xb4) != -1) {
							evt_RequestScriptExit(evt_FindScriptById(*(int*) (ev + 0xb4)));
						}
						if (d3_CurrentContextIndex == init_AllocateGebaeudeSceneSlot((unsigned char*) v4)) {
							void* found;
							char* ent = (char *)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned char)*v4];

							sprintf(erm, "Ernten_end_%s", plantInfo + 2);
							sprintf(path, "%slocations/%s/%s_%s.esc", "x:\\engine\\gfx\\scripts\\",
							        ent + 1, erm, ent + 1);
							if (vfs_LookupPath(path, g_6b7fdc, &found)) {
								char* script = evt_LoadScript(path);

								if (script != 0) {
									sprintf(spname, "sp_%i", *(int*) (ev + 0xb0));
									fcn_00428340(script, 3, spname, *(int*) (v5 + 0x14),
									             (int) *(char*) (v5 + 0xd) / (int) *(unsigned char*) (plantInfo + 0x43));
									*(int*) (script + 0xc94) = (int) v8;
									*(int*) (v8 + 0x28) = *(int*) (script + 0x100);
									*(int*) (ev + 0xb4) = *(int*) (script + 0x100);
								}
							}
						}
						*(pos14_7f4c00*) (ev + 0x52) = gm_GameTime;
						gm_AddTime(ev + 0x52, 0, 10, 0);
						*(int*) (ev + 0x70) = *(int*) (ev + 0x70) + 1;
						return;
					case 3:
						{
							char* rec;
							char* p;
							char* rec2;
							int k;
							int c;

							fcn_004c5aa0(*(int*) (ev + 0xac), *(char*) (v5 + 8), *(char*) (v5 + 9), 0, 0, -1);
							rec = fcn_00502cd0(*(int*) (v4 + 0x5d), 2, 0, 0x2a, 6);
							if (rec != 0) {
								cm_SendSellObjekt(*(int*) (rec + 2), -1, *(unsigned short*) (v5 + 0xa),
								             1 << (*(unsigned char*) (v5 + 0xd) - 1), g_773d75, 0);
							}
							k = 0;
							p = v24 + 0xd;
							for (;;) {
								if (*(char*) p != -1 && *(int*) (p - 0xd) != *(int*) (ev + 0xb8)
								    && *(char*) p >= *(char*) (v5 + 0xd)
								    && *(short*) (v5 + 0xa) == *(short*) (p - 3)) {
									if (*(unsigned char*) (v5 + 8) < (unsigned char) p[-5] + 2 + *(unsigned char*) (plantInfo + 0x42)
									    && (int) *(unsigned char*) (v5 + 8) > (int) ((unsigned char) p[-5] - *(unsigned char*) (plantInfo + 0x42) - 2)
									    && *(unsigned char*) (v5 + 9) < (unsigned char) p[-4] + 2 + *(unsigned char*) (plantInfo + 0x42)
									    && (int) *(unsigned char*) (v5 + 9) > (int) ((unsigned char) p[-4] - *(unsigned char*) (plantInfo + 0x42) - 2)) {
										rec2 = v24 + k * 0x18;
										if (rec2 != 0) {
											int id;
											int first = *(int*) rec2;

											memset(pkt, 0, 0xf8);
											pkt[4] = 0x28;
											*(int*) (pkt + 8) = *(int*) (g_7f4ca4 + *(unsigned short*) (ev + 8) * (int)sizeof(ENTITY_RECORD));
											id = *(int*) (v4 + 1);
											*(int*) (pkt + 0x0c) = id;
											*(int*) (pkt + 0x10) = 1;
											*(int*) (pkt + 0x14) = 0;
											*(int*) (pkt + 0x28) = gm_GameTime.a;
											*(int*) (pkt + 0x2c) = gm_GameTime.b;
											*(int*) (pkt + 0x30) = gm_GameTime.c;
											*(short*) (pkt + 0x34) = gm_GameTime.d;
											pkt[0x36] = 1;
											*(int*) (pkt + 0x58) = id;
											*(int*) (pkt + 0x5c) = *(int*) (ev + 0xb0);
											*(int*) (pkt + 0x64) = first;
											cm_SendCopyEntityData((int) pkt);
										}
										break;
									}
								}
								p += 0x18;
								k += 1;
								if (k >= 0x40) {
									break;
								}
							}
							he_AssignActionSlot(v4, 0, *(unsigned short*) v15, 0);
							he_FreeAction(ev);
							return;
						}
					case -1:
					case -2:
						fcn_004c5aa0(*(int*) (ev + 0xac), *(char*) (v5 + 8), *(char*) (v5 + 9),
						             *(unsigned short*) (v5 + 0xa), 0, *(int*) (ev + 4));
						he_FreeAction(ev);
						return;
					default:
						return;
					}
				}
			}
		}
		if (v15 != 0) {
			he_AssignActionSlot(v4, 0, *(unsigned short*) v15, 0);
		}
	}
	he_FreeAction(ev);
}
