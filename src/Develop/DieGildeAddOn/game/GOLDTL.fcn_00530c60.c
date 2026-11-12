#include <stdio.h>
#include <string.h>

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

extern pos14_7f4c00 g_7f4c00;

int __cdecl fcn_00500e20(int*);
int __cdecl fcn_00530b20(char*, int, char*);
int __cdecl fcn_004c4450(unsigned int);
int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(void*);
char* __cdecl evt_LoadScript(char*);
int __cdecl vfs_LookupPath(char*, void*, void**);
int __cdecl fcn_00428340(char*, int, ...);
void __cdecl fcn_00511040(int, char*);

/* ADDRESS: GOLDTL 0x00530c60 */
void __cdecl fcn_00530c60(unsigned char* a0)
{
	char* itemdef;
	JobProto* type_row;
	char* ent;
	char* info;
	char* info2;
	char* p;
	char* h;
	char* q;
	char* s;
	char* script;
	void* found;
	char job[0x60];
	char name[0x80];
	char path[0x80];
	char sp[0x80];
	int flags[8];
	int hour;
	int i;
	int k;
	int n;
	int r;
	int c; unsigned char category;
	int mode;
	int id;

	itemdef = 0;
	if (g_7746cc != 0 && *(unsigned short*) g_7746cc != 0xfd) {
		itemdef = lpObjektePROT + *(unsigned short*) g_7746cc * 0x41;
	}
	type_row = &((JobProto*)lpGebaeudePROT)[*a0];
	if ((unsigned int)g_6b7fac > g_6a2520 + 500) {
		if (g_67a370 != 0) {
			info = *(char**) (g_67a370 + 0x3c8);
			if (info != 0 && *(int*) (info + 0x318) != 0) {
				((void (__cdecl*) (int, int, int, int)) *(int*) (info + 0x318)) (g_67a370, 6, (int) (info + 0x31c), 0);
			}
		}
		g_6a2520 = g_6b7fac;
	}
	hour = fcn_00500e20((int*) &g_7f4c00);
	i = 0;
	do {
		ent = g_7e4260[i];
		if (ent != 0 && (info = *(char**) (ent + 0x184)) != 0
		    && *(int*) (info + 0x2c) == *(int*) (a0 + 1)
		    && *(unsigned char*) (ent + 8) != 0
		    && *(int*) (info + 0x88) == g_67a370) {
			mode = 0;
			job[0] = 0;
			r = fcn_00530b20(ent, (int) a0, job);
			info = *(char**)(ent + 0x184);
			if (r != 0) {
				category = type_row->kind;
				if (category == 0x0d) {
					if (g_7746cc != 0) {
						if (*(unsigned short*) g_7746cc == 0x37
						    && *(int*) (info + 0x30) == *(int*) (g_7746cc + 2)) {
							goto flag_on;
						}
						if (*(unsigned short*) g_7746cc != 0xfd
						    || *(int*) (info + 0x30) != *(int*) (g_7746cc + 2)) {
							goto after;
						}
					}
					p = *(char**) (ent + 0x17c);
					mode = 1;
					if (p != 0 && *(int*) (p + 0xc8) != 0) {
						mode = 0;
					}
				}
				else {
					if (category == 8 && *(unsigned short*) g_7746cc == 0xdd
					    && *(char*) (ent + 0x180) == 0x15) {
						goto flag_on;
					}
					p = *(char**) (ent + 0x17c);
					mode = 1;
					if (p != 0 && *p == 4 && *(int*) (p + 0xc8) != 0) {
						mode = 0;
					}
				}
			}
			else {
				category = type_row->kind;
				if (category == 0x16 && g_7746cc != 0 && *(unsigned short*) g_7746cc == 0x120
				    && *(int*) (info + 0x30) == *(int*) (g_7746cc + 2)
				    && (*(unsigned int*) (ent + 0x1c8) & 0x1000) == 0) {
					strcpy(job, "besucher");
					goto flag_on;
				}
				if (category == 1 && *(char**) (ent + 0x170) == (char*) a0
				    && (*(unsigned int*) (ent + 0x1c8) & 0x1000) == 0) {
					strcpy(job, "bewohner");
					goto flag_on;
				}
				if (*(char*) (ent + 0x180) == 0 && *(char**) (ent + 0x16c) == (char*) a0
				    && *(int*) (info + 0x28) == -1) {
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
					goto flag_on;
				}
				goto after;
			}
			goto after;
flag_on:
			mode = 1;
after:
			if (*(char*) (ent + 0x165) == 0x1c && (*(unsigned char*) (ent + 0x1b4) & 1)
			    && *(int*) (info + 0x28) == -1) {
				strcpy(job, "faulenzen");
			}
			else if (!mode) {
				goto bottom;
			}
			if (job[0] != 0) {
				if (*(int*) (info + 0x28) != -1) {
					if (fcn_00426cc0(*(int*) (info + 0x28)) != 0) {
						goto next;
					}
				}
				if (*(int*) (info + 0x28) == -1) {
					k = 0;
					while (k < 8) {
						flags[k] = 1;
						k += 1;
					}
					for (q = (char*)g_7e4260; q < (char*)(g_7e4260 + 32); q += 4) {
						info2 = *(char**) q;
						if (info2 != 0 && (info2 = *(char**) (info2 + 0x184)) != 0
						    && (id = *(int*) (info2 + 0x28)) != -1
						    && (h = fcn_00426cc0(id)) != 0
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
					if (*(char*) (ent + 0x180) != 0x16) {
						if (itemdef != 0) {
							strcpy(name, itemdef + 1);
						}
						else {
							fcn_00511040((int) *a0, name);
						}
					}
					else {
						strcpy(name, "Training_Allgemein");
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
				goto next;
			}
bottom:
			if (*(char**) (ent + 0x16c) == (char*) a0
			    && (info = *(char**) (ent + 0x184)) != 0
			    && *(int*) (info + 0x28) != -1) {
				mode = 0;
				if (*(char*) (ent + 0x180) == 0) {
					mode = 1;
				}
				else if ((float) (g_7f4c04 & 0xffff) > g_696550[hour]) {
					mode = 1;
				}
				p = *(char**) (ent + 0x17c);
				if ((p != 0 && *p == 4 && *(int*) (p + 0xc8) != 0) || mode) {
					mode = 0;
					h = fcn_00426cc0(*(int*) (info + 0x28));
					if (h != 0) {
						for (q = (char*) 0x7e2ac4; q < (char*) 0x7e30c4; q += 0x20) {
							if (mode) {
								break;
							}
							if (*(int*) (q - 4) != 0 && *q != 0 && strstr(h, q) != 0) {
								mode = 1;
							}
						}
						if (mode) {
							fcn_00428720(h);
						}
					}
				}
			}
		}
next:
			i += 1;
	} while (i < 0x20);
}
