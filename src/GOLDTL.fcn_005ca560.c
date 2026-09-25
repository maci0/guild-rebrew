// FUNCTION: GOLDTL 0x005ca560
// SIZE: 480

typedef struct
{
	char* e;
	char pad4[0x18];
	int x1c;
	int x20;
	int x24;
	int x28;
} Sel;
// SIZE 0x2c

extern unsigned short g_774970;
extern char g_7f4ca0[];
extern float g_662cf8;
extern float g_664e88;
extern float g_6660d4;

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
int __cdecl cm_ChkCutsceneReady(int, unsigned short);
float __cdecl fcn_004fef80(char*);

int __cdecl fcn_005ca560(Sel* s)
{
	char* e;
	char* p;
	float v;

	e = s->e;
	if (e == 0) {
		return 0;
	}
	s->x1c = e[0xc] != 0 ? 0x6c9 : 0x6ca;
	s->x20 = 0;
	if (g_7f4ca0[g_774970 * 540 + 9] != e[9] && (*(int*) (e + 0x1c8) & 0x800000)) {
		for (p = fcn_005463a0(1, 0, 0x6f); p != 0; p = fcn_005462a0()) {
			if (*(int*) (p + 0xac) == *(int*) (g_7f4ca0 + g_774970 * 540 + 4)
			    && *(int*) (s->e + 4) == *(int*) (p + 0xb0)) {
				s->x20 = 0x6cc;
				break;
			}
		}
	}
	s->x24 = 0;
	if (cm_ChkCutsceneReady(*(int*) (s->e + 4), g_774970) > 0) {
		s->x24 = 0x6cd;
	} else {
		for (p = fcn_005463a0(1, 0, 0x18); p != 0; p = fcn_005462a0()) {
			if (*(unsigned short*) (p + 8) == g_774970 && *(int*) (s->e + 4) == *(int*) (p + 0xc4)) {
				s->x24 = 0x6ce;
				break;
			}
		}
	}
	s->x28 = 0;
	for (p = fcn_005463a0(1, 0, 0x45); p != 0; p = fcn_005462a0()) {
		if (*(int*) (p + 0xac) == *(int*) (g_7f4ca0 + g_774970 * 540 + 4)
		    && *(int*) (s->e + 4) == *(int*) (p + 0xb0)) {
			s->x28 = 0x6cb;
			break;
		}
	}
	if (s->x28 == 0) {
		v = fcn_004fef80(s->e);
		if (v < g_662cf8) {
			s->x28 = 0x6d2;
			return 1;
		}
		if (v < g_664e88) {
			s->x28 = 0x6d1;
			return 1;
		}
		if (v < g_6660d4) {
			s->x28 = 0x6d0;
			return 1;
		}
		s->x28 = 0x6cf;
	}
	return 1;
}
