/*
 * Run one hotkey/command step for the current object (building or vehicle):
 * refresh the selected entity list, handle the "cut" action, then dispatch
 * the per-type handler and its associated window.
 */

#include <string.h>

#include "Develop/DieGildeAddOn/game/game_player.h"

typedef struct {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	char f14;
	char pad15[0x347];
} rec35c;
/* SIZE 0x35c */

typedef void (__cdecl* cmd_handler)(void*, int);

typedef struct {
	cmd_handler f0;
	cmd_handler f4;
	unsigned char f8;
	char pad9[0xb];
} cmd_entry;
/* SIZE 0x14 */

extern unsigned char g_7747b0;   /* 0x007747b0 */
extern int g_68bfb8;             /* 0x0068bfb8 */
extern int g_68bfbc;             /* 0x0068bfbc */
extern int g_6b5c60;             /* 0x006b5c60 */
extern int g_772f24;             /* 0x00772f24 */
extern int g_772f28;             /* 0x00772f28 */
extern int g_772f2c;             /* 0x00772f2c */
extern int g_772f30;             /* 0x00772f30 */
extern int g_772f34;             /* 0x00772f34 */
extern int g_772f38;             /* 0x00772f38 */
extern int g_772f3c;             /* 0x00772f3c */
extern int g_14ac5e8;            /* 0x014ac5e8 */
extern int g_14ac5ec;            /* 0x014ac5ec */

extern char g_9b0e20[];          /* 0x009b0e20 */
extern cmd_entry g_9b0844[];     /* 0x009b0844 */

extern char s_68d580[]; /* "cut_type:%i" */
extern char s_68b300[]; /* 0x0068b300 */

int __cdecl cut_GetRandSeed(void);
void __cdecl fcn_004e4f10(unsigned char*);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004c5790(int, void*);
void __cdecl fcn_005358e0(int);
int __cdecl fcn_00533a40(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_004c4df0(int, rec35c*);
int __cdecl cm_RequestSendCutInfo(int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_004e4fc0(unsigned char*);
void __cdecl fcn_004e5140(unsigned char*);
int __cdecl fcn_005373e0(int, int);
int __cdecl fcn_004e51a0(unsigned char*, int);
void __cdecl fcn_004e6c60(int);
int __cdecl sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x004e51d0 */
void __cdecl fcn_004e51d0(unsigned char* s, int id)
{
	rec35c c1;
	rec35c c2;
	struct {
		int head;
		char text[120];
	} msg;
	int saved;
	int i;
	unsigned char kind;
	int h;
	int ent;
	int pos;
	int found;
	rec35c* rec;

	saved = cut_GetRandSeed();
	fcn_004e4f10(s);
	if (g_7747b0 & 4) {
		if (*(int*) (s + 0xc) == *(int*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca4)) {
			if (g_772f3c != 0) {
				goto label_4e526f;
			}
			memset(&msg, 0, sizeof(msg));
			msg.head = *(int*) s;
			sprintf(msg.text, s_68d580, s[8]);
			fcn_004c5790(0x11, &msg);
		}
label_4e526f:
		if (g_772f3c == 0) {
			fcn_005358e0(g_14ac5e8);
		}
	}
	fcn_00533a40((int) &g_6b5c60);
	if (g_7747b0 & 8) {
		for (i = 0; i < (int) s[0x30]; i++) {
			g_772f28 = i;
			if (*(int*) (s + 0x34 + i * 4) == -1) {
				continue;
			}
			g_772f24 = gm_LookupEntityRecordById(*(int*) (s + 0x34 + i * 4));
			if (g_772f24 == 0) {
				*(int*) (s + 0x34 + i * 4) = -1;
				continue;
			}
			rec = &((rec35c*) g_9b0e20)[i];
			if (*(unsigned char*) (g_772f24 + 2) == 6) {
				g_772f34 = g_68bfbc + g_772f30;
				g_772f38 = 0;
				((cmd_entry*) g_9b0844)[s[8]].f0(rec, id);
			} else if (((cmd_entry*) g_9b0844)[s[8]].f4 != 0) {
				((cmd_entry*) g_9b0844)[s[8]].f4(rec, id);
			}
			d2_SetForm(*(int*) (s + 0x2c), 0);
			io_AppendText((int) ((char*) rec + 0x14));
			io_AppendText((int) s_68b300);
		}
	} else if (g_7747b0 & 4) {
		g_772f24 = (unsigned int) g_774970 * 0x21c + 0x7f4ca0;
		kind = *(unsigned char*) ((unsigned int) s[8] * 0x14 + 0x9b084c);
		if (kind == 1) {
			if (*(int*) (s + 0xc) == *(int*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca4)) {
				rec = (rec35c*) g_9b0e20;
				for (i = 0; i < (int) s[0x30]; i++) {
					ent = gm_LookupEntityRecordById(*(int*) (s + 0x34 + i * 4));
					if (ent != 0
							&& *(unsigned char*) (ent + 2) != 6
							&& *(unsigned char*) (ent + 2) != 7
							&& rec->f8 == 0) {
						c1 = *rec;
						g_772f24 = ent;
						if (((cmd_entry*) g_9b0844)[s[8]].f4 != 0) {
							((cmd_entry*) g_9b0844)[s[8]].f4(&c1, id);
						}
						c1.f8 = 1;
						c1.fc = 0;
						fcn_004c4df0(0x35c, &c1);
						h = cm_RequestSendCutInfo(*(int*) (ent + 4), *(int*) s);
						while (fcn_004c4450(h) == 0) {
							fcn_00535960();
						}
						fcn_004e5140(s);
						fcn_005373e0(0, g_68bfb8 | 0x8000);
					}
					rec++;
				}
			}
			g_772f24 = (unsigned int) g_774970 * 0x21c + 0x7f4ca0;
			ent = *(int*) (g_772f24 + 4);
			for (i = 0; i < (int) s[0x30]; i++) {
				if (*(int*) (s + 0x34 + i * 4) == ent) {
					g_772f34 = g_68bfbc + g_772f30;
					c1 = ((rec35c*) g_9b0e20)[i];
					g_772f38 = 0;
					((cmd_entry*) g_9b0844)[s[8]].f0(&c1, id);
					c1.f8 = 1;
					c1.fc = 0;
					fcn_004c4df0(0x35c, &c1);
					h = cm_RequestSendCutInfo(*(int*) (g_772f24 + 4), *(int*) s);
					while (fcn_004c4450(h) == 0) {
						fcn_00535960();
					}
					break;
				}
			}
			while (fcn_004e4fc0(s) == 0) {
				fcn_004e5140(s);
				fcn_00533a40(g_14ac5ec);
				fcn_005373e0(0, g_68bfb8 | 0x8000);
			}
		} else if (kind == 0) {
			pos = -1;
			found = -1;
			for (i = 0; i < (int) s[0x30]; i++) {
				if (*(int*) (s + 0x34 + i * 4) == *(int*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca4)) {
					pos = i;
					if (pos != -1) {
						found = fcn_004e51a0(s, pos);
					}
					break;
				}
			}
			while (fcn_004e4fc0(s) == 0) {
				fcn_004e5140(s);
				fcn_005373e0(0, g_68bfb8 | 0x8000);
				if (pos != -1
						&& (pos == 0 || ((rec35c*) g_9b0e20)[found].f8 == 1)
						&& ((rec35c*) g_9b0e20)[pos].f8 == 0) {
					g_772f28 = pos;
					c1 = ((rec35c*) g_9b0e20)[pos];
					g_772f24 = gm_LookupEntityRecordById(*(int*) (s + 0x34 + pos * 4));
					fcn_004e5140(s);
					g_772f34 = g_68bfbc + g_772f30;
					g_772f38 = 0;
					((cmd_entry*) g_9b0844)[s[8]].f0(&c1, id);
					c1.f8 = 1;
					c1.fc = 0;
					fcn_004c4df0(0x35c, &c1);
					h = cm_RequestSendCutInfo(*(int*) (g_772f24 + 4), *(int*) s);
					while (fcn_004c4450(h) == 0) {
						fcn_00535960();
					}
					fcn_004e5140(s);
					fcn_005373e0(0, g_68bfb8 | 0x8000);
				}
				if (*(int*) (s + 0xc) == *(int*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca4)) {
					for (i = 0; i < (int) s[0x30]; i++) {
						ent = gm_LookupEntityRecordById(*(int*) (s + 0x34 + i * 4));
						if (ent != 0
								&& *(unsigned char*) (ent + 2) != 6
								&& *(unsigned char*) (ent + 2) != 7
								&& (i == 0 || ((rec35c*) g_9b0e20)[fcn_004e51a0(s, i)].f8 == 1)
								&& ((rec35c*) g_9b0e20)[i].f8 == 0) {
							g_772f28 = i;
							c2 = ((rec35c*) g_9b0e20)[i];
							g_772f24 = ent;
							if (((cmd_entry*) g_9b0844)[s[8]].f4 != 0) {
								((cmd_entry*) g_9b0844)[s[8]].f4(&c2, id);
							}
							c2.f8 = 1;
							c2.fc = 0;
							fcn_004c4df0(0x35c, &c2);
							h = cm_RequestSendCutInfo(*(int*) (ent + 4), *(int*) s);
							while (fcn_004c4450(h) == 0) {
								fcn_00535960();
							}
							break;
						}
					}
				}
			}
			fcn_004e5140(s);
			fcn_005373e0(0, g_68bfb8 | 0x8000);
		}
	}
	g_772f2c += 1;
	fcn_004e6c60(saved);
}
