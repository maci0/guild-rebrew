/* Loads the network savegame header and publishes the net slot record. */

#include <stdio.h>
#include <string.h>

/* SIZE 0x6a */
struct netinfo {
	short a;
	short b;
	short size;
	char name[0x20];
	char mode;
	char pad;
	short port;
	char rest[0x40];
};

/* SIZE 0x70 */
struct netslot {
	struct netinfo info;
	int x;
};

extern struct netinfo g_7e2520;
extern struct netslot g_9baa70;

extern char g_7e21a0[];
extern char g_7e2000[];
extern char g_6a1ea4[];
extern char g_6a3a1c[];
extern char g_9bada0[];
extern char g_9badb0[];
extern int g_6b7fdc;
extern int g_7747b0;
extern unsigned char g_6a375c;
extern short g_7e2510;
extern int g_9baadc;
extern int g_9badc0;
extern int g_9badc4;
extern int g_9badc8;
extern int g_9badcc;

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
int __cdecl fcn_005e0930(void);
int __cdecl ls_LoadSavegameHeader(void* stream, char* dest);
int __cdecl CloseVfsStream(void* stream);

/* ADDRESS: GOLDTL 0x00539600 */
int __cdecl fcn_00539600(void)
{
	char hdr[0xfc];
	char path[0x104];
	void* f;
	unsigned int i;
	char c;

	if (fcn_005e0930()) {
		sprintf(path, g_6a1ea4, g_7e21a0);
		f = vfs_Tfopen(path, (char*) 0x6750e8, *(struct VFS_DIR**) 0x6b7fdc);
		if (f != 0) {
			ls_LoadSavegameHeader(f, hdr);
			c = hdr[0x31];
			memcpy(g_7e2000, g_6a3a1c, 10);
			g_7747b0 |= 0x50;
			g_6a375c = c;
			g_7e2520.mode = c;
			g_7e2520.size = 0x6a;
			g_7e2520.a = 1;
			g_7e2520.b = 4;
			g_7e2520.port = g_7e2510;
			i = 0;
			do {
				c = hdr[5 + i];
				g_7e2520.name[i] = c;
				i++;
			} while (c != 0);
			i = 0;
			do {
				c = g_7e21a0[i];
				g_7e2520.rest[i] = c;
				i++;
			} while (c != 0);
			memcpy(g_7e2520.rest + 0x20, hdr + 0x78, 0x20);
			g_9baa70.info = g_7e2520;
			memset(g_9bada0, 0, 0x30);
			g_9badc0 = *(int*) (hdr + 0x60) & 0xff;
			g_9baadc = 0x7f;
			g_9badc4 = *(int*) (hdr + 0x6c) & 0xff;
			i = 0;
			do {
				c = hdr[0x40 + i];
				g_9bada0[i] = c;
				i++;
			} while (c != 0);
			if (*(int*) hdr >= 0x10054) {
				i = 0;
				do {
					c = hdr[0x50 + i];
					g_9badb0[i] = c;
					i++;
				} while (c != 0);
				g_9badc8 = *(int*) (hdr + 0x63) & 0xff;
				g_9badcc = *(int*) (hdr + 0x64);
			}
			CloseVfsStream(f);
			return 1;
		}
	}
	return 0;
}
unsigned char _dpad_7e2520[480];
