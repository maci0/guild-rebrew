


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

extern char g_7f4ca0[];
#ifdef REBREW_GOLD
#define SND_TABLE_ADDR 0x770b80
#define SND_INDEX_ADDR 0x6f25b8
#else
#define SND_TABLE_ADDR 0x7f4ca0
#define SND_INDEX_ADDR 0x774970
#endif
#define SND_INDEX (*(unsigned short*) SND_INDEX_ADDR)
#define SND_TABLE ((char*) SND_TABLE_ADDR)
extern float g_662cf8;
extern float g_664e88;
extern float g_6660d4;

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);
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
	if (SND_TABLE[SND_INDEX * 540 + 9] != e[9] && (*(int*) (e + 0x1c8) & 0x800000)) {
		for (p = fcn_005463a0(1, 0, 0x6f); p != 0; p = he_fn_Handlung()) {
			if (*(int*) (p + 0xac) == *(int*) (SND_TABLE + SND_INDEX * 540 + 4)
			    && *(int*) (s->e + 4) == *(int*) (p + 0xb0)) {
				s->x20 = 0x6cc;
				break;
			}
		}
	}
	s->x24 = 0;
	if (cm_ChkCutsceneReady(*(int*) (s->e + 4), SND_INDEX) > 0) {
		s->x24 = 0x6cd;
	} else {
		for (p = fcn_005463a0(1, 0, 0x18); p != 0; p = he_fn_Handlung()) {
			if (*(unsigned short*) (p + 8) == SND_INDEX && *(int*) (s->e + 4) == *(int*) (p + 0xc4)) {
				s->x24 = 0x6ce;
				break;
			}
		}
	}
	s->x28 = 0;
	for (p = fcn_005463a0(1, 0, 0x45); p != 0; p = he_fn_Handlung()) {
		if (*(int*) (p + 0xac) == *(int*) (SND_TABLE + SND_INDEX * 540 + 4)
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
