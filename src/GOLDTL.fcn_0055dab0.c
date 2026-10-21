#include <string.h>

typedef struct Level {
	unsigned char kind;
	char pad1[0x24c];
} Level;
/* SIZE 0x24d */

typedef struct Slot21c {
	char pad0[2];
	unsigned char kind;
	char pad3;
	int id;
	char pad8[0x214];
} Slot21c;
/* SIZE 0x21c */

typedef struct Handler {
	void(__cdecl* fn)(void*, int);
	int arg;
} Handler;
/* SIZE 8 */

extern unsigned char* g_868050;
extern char g_868060[];
extern Slot21c g_7f4ca0[];
extern int g_7e35c0[][2];
extern int g_774650;
extern char* g_7746c8;
extern int g_6b8010;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindRecordById(int);
void __cdecl fcn_0055d6e0(char*, char*);
void __cdecl fcn_004c5c80(int);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
int __cdecl fcn_004c5290(int, int, int);
int __cdecl fcn_00505340(char*);
void __cdecl fcn_004c5d20(int, int);
int __cdecl fcn_00529710(char*, char*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_005ba910(void*, int);

/* ADDRESS: GOLDTL 0x0055dab0 */
void __cdecl fcn_0055dab0(char* e)
{
	char* s44;
	char* b;
	char* c;
	char* r;
	Level* lv;
	int saved;
	int code;
	char text[0x104];
	char msg[0x400];
	unsigned char k;

	s44 = gm_StartFilteredEntitySearch(1, 0, 0x44);
	gm_StartFilteredEntitySearch(1, 0, 0x45);
	b = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xb0));
	c = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xb4));
	saved = g_6b8010;
	r = gm_FindRecordById(*(int*) (e + 0xac));
	if (r == 0) {
		return;
	}
	fcn_0055d6e0(e, r);
	if (e[0xd0] == 0) {
		fcn_004c5c80(*(int*) (r + 2));
		if (!fcn_00505340(b)) {
			fcn_004c5d20(*(int*) (r + 2), 1);
		}
		fcn_004c5da0(*(int*) (r + 2), *(int*) (c + 1), -1, 0, 0, "Trans");
		if (!fcn_00505340(b)) {
			*(int*) (e + 0xec) = fcn_004c5290(*(int*) (s44 + 1), *(int*) (b + 1), *(int*) (r + 2));
		}
		e[0xd0] = 1;
	} else {
		if (!fcn_00529710(r, c)) {
			fcn_004432d0(saved, 1);
			return;
		}
		*(int*) (e + 0xec) = fcn_004c5290(*(int*) (c + 1), *(int*) (s44 + 1), *(int*) (r + 2));
		k = *(unsigned char*) c;
		if (k == 0x47) {
			fcn_0051af00(msg, 0x1c3b, 1, 0x1c39, g_868060 + *(int*) (c + 0x65) * 0x2f4);
			if ((g_7e35c0[g_774650][0] != 0x5ba910 || g_7746c8 != c) &&
			    !(r[0x20] & 1) && e[0xf2] == 0) {
				he_MessageBoxQuickjump(g_7f4ca0[*(unsigned short*) (e + 8)].id, *(int*) (r + 2), msg, 0,
				    0x609, *(int*) (c + 1), -1, 0, "_NACHRICHTEN_HS_60");
			}
		} else if (*(unsigned char*) b == 0x47) {
			fcn_0051af00(msg, 0x1c3d, 1, 0x1c39, g_868060 + *(int*) (b + 0x65) * 0x2f4,
			    *(unsigned short*) (c + 0x27), c);
			if ((g_7e35c0[g_774650][0] != 0x5ba910 || g_7746c8 != c) &&
			    !(r[0x20] & 1) && e[0xf2] == 0) {
				he_MessageBoxQuickjump(g_7f4ca0[*(unsigned short*) (e + 8)].id, *(int*) (r + 2), msg, 0,
				    0x609, *(int*) (c + 1), -1, 0, "_NACHRICHTEN_HS_59");
			}
		} else {
			lv = (Level*) (g_868050 + k * sizeof(Level));
			code = 0x609;
			if (k == 0x1e) {
				memcpy(text, "_NACHRICHTEN_HS_58", 0x13);
			} else if (k == 0x1f) {
				memcpy(text, "_NACHRICHTEN_HS_57", 0x13);
			} else if (k == 0x20) {
				memcpy(text, "_NACHRICHTEN_HS_56", 0x13);
			} else {
				text[0] = 0;
			}
			if (lv->kind != 0x1d && lv->kind != 0x1f) {
				fcn_0051af00(msg, 0x1c3f, 1, 0x1c39, *(unsigned short*) (c + 0x27), c);
			} else {
				code = 0x608;
				if (fcn_00505340(c)) {
					fcn_0051af00(msg, 0x1c43);
				} else {
					fcn_0051af00(msg, 0x1c44, c);
				}
			}
			if ((g_7e35c0[g_774650][0] != 0x5ba910 || g_7746c8 != c) &&
			    !(r[0x20] & 1) && e[0xf2] == 0) {
				if (text[0] != 0) {
					he_MessageBoxQuickjump(g_7f4ca0[*(unsigned short*) (e + 8)].id, *(int*) (r + 2),
					    msg, 0, code, *(int*) (c + 1), -1, 0, text);
				} else {
					he_MessageBoxQuickjump(g_7f4ca0[*(unsigned short*) (e + 8)].id, *(int*) (r + 2),
					    msg, 0, code, *(int*) (c + 1), -1, 0, 0);
				}
			}
		}
		*(int*) (e + 0x84) = fcn_004c5620(3, e);
	}
	fcn_004432d0(saved, 1);
}
