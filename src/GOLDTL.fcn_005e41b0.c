


#include <stdio.h>
#include <string.h>

// SIZE 0x8
typedef struct {
	int id;
	int pad;
} Peer;

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char kind;
	char pad3;
	int handle;
	char pad8[0x214];
} Ent;

// SIZE 0x7c
typedef struct {
	int handle;
	unsigned int crc;
	char pad[0x74];
} Hello;

extern int g_7e46ac;
extern Peer g_7f3ac0[8];
extern unsigned char g_7747b0;
extern char* g_14ac60c;
extern unsigned char g_6a375c;
extern char g_7f4ca0[];
extern char g_7e2480[];
extern char g_774980;
extern char g_773de8;
typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* g_6b7fdc;
extern unsigned short g_774970;
extern char g_6b5c60[];

void __cdecl fcn_00535850(int, char*);
void __cdecl fcn_005e3fa0(char*);
void* __cdecl fcn_0042ff50(const char* name, const char* mode, struct VFS_DIR* root);
int __cdecl fcn_0051e490(void* stream, int flags);
#include "Develop/Units/vfs/vfs.h"
#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
unsigned int __cdecl fcn_00401000(unsigned char*, unsigned int);
int __cdecl fcn_004c5790(int, void*);
void __cdecl fcn_00535960(void);
void __cdecl fcn_0051e080(char*, char*, int);
void __cdecl fcn_00533a40(char*);

void __cdecl fcn_005e41b0(char* name, char* title)
{
	unsigned int crc;
	Hello m;
	char path[0x104];
	char hdr[0xfc];
	int i;
	void* f;
	int n;

	crc = 0;
	g_7e46ac |= 0x20000;
	for (i = 0; i < 8; i++) {
		g_7f3ac0[i].id = -1;
	}
	if (g_7747b0 & 4) {
		fcn_00535850(g_7e46ac, g_14ac60c);
		g_6a375c = 0;
		for (i = 0; i < 768; i++) {
			if (((Ent*)g_7f4ca0)[i].id != 0xffff && (((Ent*)g_7f4ca0)[i].kind == 6 || ((Ent*)g_7f4ca0)[i].kind == 7)) {
				g_6a375c++;
			}
		}
		strcpy(g_7e2480, title);
		g_773de8 = g_774980;
		fcn_005e3fa0("Gamedata/cities/standard.scr");
		sprintf(path, "Gamedata\\network\\%s.SAV", name);
		f = fcn_0042ff50(path, "wb", g_6b7fdc);
		if (f != 0) {
			fcn_0051e490(f, 5);
			CloseVfsStream(f);
		}
		f = fcn_0042ff50(path, "rb", g_6b7fdc);
		if (f != 0) {
			ls_LoadSavegameHeader(f, hdr);
			crc = fcn_00401000((unsigned char*) hdr, 0x78);
			CloseVfsStream(f);
		}
		memset(&m, 0, sizeof(m));
		m.handle = ((Ent*)g_7f4ca0)[g_774970].handle;
		m.crc = crc;
		fcn_004c5790(0x10, &m);
		n = 0;
		while (n < g_6a375c) {
			n = 0;
			for (i = 0; i < 8; i++) {
				if (g_7f3ac0[i].id != -1) {
					n++;
				}
			}
			fcn_00535960();
		}
		fcn_00535850(g_7e46ac, g_14ac60c);
		sprintf(path, "Gamedata\\network\\%s.SRV", name);
		fcn_0051e080(path, title, 6);
		sprintf(path, "Gamedata\\network\\%s.SAV", name);
		fcn_0051e080(path, title, 5);
		fcn_00533a40(g_6b5c60);
	}
}
