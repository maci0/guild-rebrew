#include <stdio.h>
#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;
extern char g_7f4ca4[];
extern char* g_entity_type_table;
extern char* g_item_def_table;
extern void* g_6b7fdc;
extern int g_6b8010;

void* __cdecl fcn_00503fe0(int, int, int);
char* __cdecl fcn_004bcc50(char*, int);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004c4450(unsigned int);
int __cdecl fcn_005155e0(unsigned char*);
void __cdecl fcn_00546190(void*);
void __cdecl fcn_00529160(char*, int, int, int);
char* __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(char*);
char* __cdecl evt_LoadScript(char*);
int __cdecl fcn_0042f120(char*, void*, void**);
int __cdecl fcn_00428340(char*, int, ...);
void __cdecl fcn_004c5aa0(int, char, char, short, char, int);
char* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_004c51f0(int, int, short, int, char, int);
void __cdecl fcn_004c5530(int);
void __cdecl fcn_00500bb0(void*, int, int, int);
char* __cdecl plt_FindPlantInfo(int);

/* ADDRESS: GOLDTL 0x00565ab0 */
void __cdecl fcn_00565ab0(char* ev)
{
	char* v4;
	char* v24;
	char* v5;
	char* v15;
	char* v8;
	char* v6;
	void* found;
	int v20;
	int v21;
	char spname[0x40];
	char pkt[0xf8];
	char path[0x80];
	char erm[0x80];

	v4 = (char*) fcn_00503fe0(1, 1, *(int*) (ev + 0xac));
	if (v4 != 0) {
		v24 = *(char**) (v4 + 0x71);
		v5 = fcn_004bcc50(v24, *(int*) (ev + 0xb8));
		v15 = fcn_00508e40(*(int*) (ev + 0xb0));
		if (v5 != 0) {
			if (v15 == 0) {
				fcn_00546190(ev);
				return;
			}
			if (*(int*) (v5 + 0x10) == -1 || *(int*) (v5 + 0x10) == *(int*) (ev + 4)) {
				v8 = *(char**) (v15 + 0x184);
				v6 = plt_FindPlantInfo(*(unsigned short*) (v5 + 0xa));
				switch (*(int*) (ev + 0x70)) {
				case -2:
				case -1:
					fcn_004c5aa0(*(int*) (ev + 0xac), *(char*) (v5 + 8), *(char*) (v5 + 9),
					             *(unsigned short*) (v5 + 0xa), 0, *(int*) (ev + 4));
					fcn_00546190(ev);
					return;
				case 0:
					v20 = *(int*) (ev + 0xc0);
					if (!fcn_004c4450(v20)) {
						return;
					}
					if (g_6b8010 != fcn_005155e0((unsigned char*) v4)) {
						*(int*) (ev + 0xc0) = -1;
					}
					else {
						sprintf(erm, "Ernten_start_%s", v6 + 2);
						sprintf(path, "%slocations/%s/%s_%s.esc", "x:\\engine\\gfx\\scripts\\",
						        g_entity_type_table + (unsigned char) *v4 * 0x24d + 1, erm,
						        g_entity_type_table + (unsigned char) *v4 * 0x24d + 1);
						if (fcn_0042f120(path, g_6b7fdc, &found)) {
							char* script = evt_LoadScript(path);

							if (script != 0) {
								sprintf(spname, "sp_%i", *(int*) (ev + 0xb0));
								fcn_00428340(script, 3, spname, *(int*) (v5 + 0x14),
								             (int) *(char*) (v5 + 0xd) / (int) *(unsigned char*) (v6 + 0x43));
								*(int*) (script + 0xc94) = (int) v8;
								*(int*) (v8 + 0x28) = *(int*) (script + 0x100);
								*(int*) (ev + 0xb4) = *(int*) (script + 0x100);
							}
						}
					}
					v20 = 0;
					v21 = 1;
					break;
				case 1:
					*(int*) (ev + 0xc0) = -1;
					*(int*) (ev + 0x52) = *(int*) &g_7f4c00;
					*(int*) (ev + 0x56) = g_7f4c04;
					*(int*) (ev + 0x5a) = g_7f4c08;
					*(unsigned short*) (ev + 0x5e) = g_7f4c0c;
					{
						unsigned short type = *(unsigned short*) (v5 + 0xa);
						char* def = g_item_def_table + type * 0x41;

						fcn_00500bb0(ev + 0x52, 0, 0,
						             (int) ((double) (*(char*) (v5 + 0xd) * *(int*) (def + 0x22)) * 0.25));
					}
					*(int*) (ev + 0x70) = *(int*) (ev + 0x70) + 1;
					return;
				case 2:
					if (*(int*) (ev + 0xb4) != -1) {
						fcn_00428720(fcn_00426cc0(*(int*) (ev + 0xb4)));
					}
					if (g_6b8010 == fcn_005155e0((unsigned char*) v4)) {
						sprintf(erm, "Ernten_end_%s", v6 + 2);
						sprintf(path, "%slocations/%s/%s_%s.esc", "x:\\engine\\gfx\\scripts\\",
						        g_entity_type_table + (unsigned char) *v4 * 0x24d + 1, erm,
						        g_entity_type_table + (unsigned char) *v4 * 0x24d + 1);
						if (fcn_0042f120(path, g_6b7fdc, &found)) {
							char* script = evt_LoadScript(path);

							if (script != 0) {
								sprintf(spname, "sp_%i", *(int*) (ev + 0xb0));
								fcn_00428340(script, 3, spname, *(int*) (v5 + 0x14),
								             (int) *(char*) (v5 + 0xd) / (int) *(unsigned char*) (v6 + 0x43));
								*(int*) (script + 0xc94) = (int) v8;
								*(int*) (v8 + 0x28) = *(int*) (script + 0x100);
								*(int*) (ev + 0xb4) = *(int*) (script + 0x100);
							}
						}
					}
					v20 = 10;
					v21 = 0;
					break;
				case 3:
					{
						char* rec;
						char* p;
						int k;
						int c;

						fcn_004c5aa0(*(int*) (ev + 0xac), *(char*) (v5 + 8), *(char*) (v5 + 9), 0, 0, -1);
						rec = fcn_00502cd0(*(int*) (v4 + 0x5d), 2, 0, 0x2a, 6);
						if (rec != 0) {
							fcn_004c51f0(*(int*) (rec + 2), -1, *(unsigned short*) (v5 + 0xa),
							             1 << ((*(unsigned char*) (v5 + 0xd) - 1) & 0x1f), g_773d75, 0);
						}
						k = 0;
						p = v24 + 0xd;
						for (;;) {
							if (p[0] != (char) 0xff && *(int*) (p - 0xd) != *(int*) (ev + 0xb8)
							    && *(char*) (v5 + 0xd) <= p[0]
							    && *(short*) (v5 + 0xa) == *(short*) (p - 3)) {
								c = *(unsigned char*) (v6 + 0x42);
								if (*(unsigned char*) (v5 + 8) < (unsigned char) p[-5] + 2 + c
								    && (int) ((unsigned char) p[-5] - c - 2) < (int) *(unsigned char*) (v5 + 8)
								    && *(unsigned char*) (v5 + 9) < (unsigned char) p[-4] + 2 + c
								    && (int) ((unsigned char) p[-4] - c - 2) < (int) *(unsigned char*) (v5 + 9)) {
									char* rec2 = v24 + k * 0x18;

									if (rec2 != 0) {
										memset(pkt, 0, 0xf8);
										pkt[4] = 0x28;
										*(int*) (pkt + 0x8) = *(int*) (g_7f4ca4 + *(unsigned short*) (ev + 8) * 0x21c);
										*(int*) (pkt + 0xc) = *(int*) (v4 + 1);
										*(int*) (pkt + 0x10) = 1;
										*(int*) (pkt + 0x14) = 0;
										*(int*) (pkt + 0x28) = *(int*) &g_7f4c00;
										*(int*) (pkt + 0x2c) = g_7f4c04;
										*(int*) (pkt + 0x30) = g_7f4c08;
										*(unsigned short*) (pkt + 0x34) = g_7f4c0c;
										pkt[0x36] = 1;
										*(int*) (pkt + 0x58) = *(int*) (v4 + 1);
										*(int*) (pkt + 0x60) = *(int*) (ev + 0xb0);
										*(int*) (pkt + 0x64) = *(int*) rec2;
										fcn_004c5530((int) pkt);
									}
									fcn_00529160(v4, 0, *(unsigned short*) v15, 0);
									fcn_00546190(ev);
									return;
								}
							}
							p += 0x18;
							k += 1;
							if (k >= 0x40) {
								break;
							}
						}
						fcn_00529160(v4, 0, *(unsigned short*) v15, 0);
						fcn_00546190(ev);
						return;
					}
				default:
					return;
				}
				*(int*) (ev + 0x52) = *(int*) &g_7f4c00;
				*(int*) (ev + 0x56) = g_7f4c04;
				*(int*) (ev + 0x5a) = g_7f4c08;
				*(unsigned short*) (ev + 0x5e) = g_7f4c0c;
				fcn_00500bb0(ev + 0x52, 0, v20, v21);
				*(int*) (ev + 0x70) = *(int*) (ev + 0x70) + 1;
				return;
			}
		}
		if (v15 != 0) {
			fcn_00529160(v4, 0, *(unsigned short*) v15, 0);
		}
	}
	fcn_00546190(ev);
}
