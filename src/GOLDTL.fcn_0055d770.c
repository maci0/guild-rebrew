// FUNCTION: GOLDTL 0x0055d770
// Transport event step: on the first call starts the transport (flag
// +0xd0); afterwards, once the carrier arrived (within 100 units of +0xd8)
// or +0xd4 ran past 6, files the arrival message and schedules the next
// step (+0x84).

typedef struct Level {
	unsigned char kind;
	char pad1[0x24c];
} Level;
// SIZE 0x24d

typedef struct Slot21c {
	char pad0[2];
	unsigned char kind;
	char pad3;
	int id;
	char pad8[0x214];
} Slot21c;
// SIZE 0x21c

typedef struct Handler {
	void(__cdecl* fn)(void*, int);
	int arg;
} Handler;
// SIZE 8

extern unsigned char* g_868050;
extern int g_6b8010;
extern Slot21c g_7f4ca0[];
extern int g_7e35c0[];
extern int g_774650;
extern char* g_7746c4;
extern unsigned short* g_7746cc;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_FindRecordById(int);
void __cdecl fcn_0055d6e0(char* e, char* r);
void __cdecl fcn_004c5c80(int);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
int __cdecl fcn_004c5290(int, int, int);
int __cdecl fcn_00451840(char*, char*, float);
int __cdecl fcn_00505340(char*);
void __cdecl fcn_004c5d20(int, int);
int __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
char* __cdecl fcn_005049a0(char*);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, char*);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_005ba910(void*, int);

void __cdecl fcn_0055d770(char* e)
{
	char* s44;
	Level* lv;
	int saved;
	char buf[0x400];
	char* b;
	char* c;
	char* r;
	char* o;
	char* h;
	unsigned char k;
	unsigned short w;

	s44 = gm_StartFilteredEntitySearch(1, 0, 0x44);
	gm_StartFilteredEntitySearch(1, 0, 0x45);
	b = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xb0));
	lv = (Level*) (g_868050 + *(unsigned char*) b * sizeof(Level));
	c = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xb4));
	saved = g_6b8010;
	r = gm_FindRecordById(*(int*) (e + 0xac));
	if (r == 0) {
		return;
	}
	fcn_0055d6e0(e, r);
	if (e[0xd0] == 0) {
		fcn_004c5c80(*(int*) (r + 2));
		fcn_004c5da0(*(int*) (r + 2), *(int*) (c + 1), -1, 0, 1, "Trans");
		*(int*) (e + 0xec) = fcn_004c5290(*(int*) (s44 + 1), *(int*) (b + 1), *(int*) (r + 2));
		e[0xd0] = 1;
	} else {
		o = *(char**) (r + 0x3b);
		if (o != 0 && *(int*) (o + 0x128) == 0 &&
		    ((*(int*) (o + 0x88) == 0x10432c0 && fcn_00451840(*(char**) (o + 0x34) + 0x4c, e + 0xd8, 100.0f)) ||
		     *(int*) (e + 0xd4) > 6)) {
			if (!fcn_00505340(c)) {
				*(int*) (e + 0xec) = fcn_004c5290(*(int*) (c + 1), *(int*) (s44 + 1), *(int*) (r + 2));
				fcn_004c5d20(*(int*) (r + 2), 0);
			}
			fcn_004c5420(*(int*) (r + 2), 0x13, 1, 0, 0x40);
			if (fcn_00505340(c)) {
				fcn_0051af00(buf, 0x1c43);
			} else if (lv->kind != 0x1d && lv->kind != 0x1f) {
				fcn_0051af00(buf, 0x1c41, 1, 0x1c39, b, *(unsigned short*) (c + 0x27), c);
			} else if (fcn_00505340(c)) {
				fcn_0051af00(buf, 0x1c43);
			} else {
				fcn_0051af00(buf, 0x1c44, c);
			}
			k = g_7f4ca0[*(unsigned short*) (e + 8)].kind;
			if (k == 6 || k == 7) {
				if (((Handler*) g_7e35c0)[g_774650].fn == fcn_005ba910) {
					if (g_7746c4 == c) {
						goto done;
					}
					if (fcn_00505340(c) && g_7746cc != 0) {
						w = *g_7746cc;
						if ((w >= 0x92 && w <= 0x97) || w == 0x2db) {
							goto done;
						}
					}
				}
				if (!(r[0x20] & 1) && e[0xf2] == 0) {
					h = fcn_005049a0(c);
					if (h != 0) {
						fcn_00545e80(g_7f4ca0[*(unsigned short*) (e + 8)].id, *(int*) (r + 2), buf, 0, 0x608,
						             *(int*) (c + 1), *(int*) (h + 2), 0, 0);
					} else {
						fcn_00545e80(g_7f4ca0[*(unsigned short*) (e + 8)].id, *(int*) (r + 2), buf, 0, 0x608,
						             *(int*) (c + 1), -1, 0, 0);
					}
				}
			}
		done:
			*(int*) (e + 0x84) = fcn_004c5620(3, e);
		}
	}
	fcn_004432d0(saved, 1);
}
