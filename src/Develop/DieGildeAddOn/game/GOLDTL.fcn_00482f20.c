
// 0x100dc20 is one 0xb00-byte block (owner, light count at +0x18, lights at
// +0x300); declaring it as one struct makes the light copy reload the count
// after each store, as the reference does.

#pragma pack(push, 1)
// SIZE 0x43
typedef struct {
	unsigned short id;
	char pad2[0x1a];
	int owner;
	char pad20[0x23];
} Slot;

// SIZE 0x41
typedef struct {
	unsigned char kind;
	char pad1[0x40];
} Kind;

// SIZE 0x24d
typedef struct {
	char pad0[0x247];
	unsigned char level;
	char pad248[5];
} Level;
#pragma pack(pop)

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern unsigned short *lpObjekteINST;
extern char *lpObjektePROT;
extern int g_100e74c;
extern char *g_100dbc0[16];
extern unsigned char *lpGebaeudePROT;
extern int g_100b0a8;
extern int g_100b0ac;
extern int g_100b0f4;
extern float g_100b0e0;
extern int g_100d10c;
extern float g_100d0f4;
extern LightState g_100dc20;
extern Seg g_100b0c0[];

char *__cdecl fcn_00502cd0(int, int, int, int, int, ...);
void __cdecl fcn_00487970(char *, char *, int);
void __cdecl fcn_00487c00(char *, char *, int);
char *__cdecl gm_NextEntityQueryMatch(void);
char *__cdecl fcn_005463a0(int, int, int, int, int);
char *__cdecl he_fn_Handlung(void);
void __cdecl ai_MeisterCollectTrans(char *);
void __cdecl fcn_00485970(char *, char *, int);
void __cdecl fcn_0048c5b0(char *, char *);
void __cdecl fcn_0048cdb0(char *, char *);

void __cdecl fcn_00482f20(char *a)
{
	int flag;
	char *t;
	char *m;
	char *e;
	char *h;
	Slot *s;
	float f;
	int i;
	unsigned char lvl;

	if ((*(unsigned int *) (a + 4) + (unsigned short) g_7f4c00.b) % 3 == 0) {
		if (*(int *) (a + 0x1b4) & 0x20) {
			return;
		}
		t = fcn_00502cd0(*(int *) (*(char **) (a + 0x16c) + 0x5d), 2, 6, 0, 0x116);
		if (t == 0) {
			return;
		}
		fcn_00487970(t, a, 0x14);
		fcn_00487c00(t, a, 0x32);
		flag = 1;
		s = (Slot*) lpObjekteINST;
		for (i = 0; flag && i < 0x5008; s++, i++) {
			if (s->id != 0 && ((Kind*) lpObjektePROT)[s->id].kind == 0x1d && s->owner == *(int *) (*(char **) (a + 0x16c) + 1) &&
			    s->id == 0x136) {
				flag = 0;
			}
		}
		g_100e74c = 0;
		h = *(char **) (a + 0x16c);
		for (m = fcn_00502cd0(*(int *) (h + 0x5d), 3, 6, 4, 0x1d, 3, *(unsigned short *) (h + 0x27)); m != 0;
		     m = gm_NextEntityQueryMatch()) {
			if (*(int *) (m + 0x1c) != *(int *) (*(char **) (a + 0x16c) + 1)) {
				continue;
			}
			for (e = fcn_005463a0(2, 0, 0xb, 3, *(int *) (*(char **) (a + 0x16c) + 1)); e != 0; e = he_fn_Handlung()) {
				if (*(int *) (e + 0xac) == *(int *) (m + 2)) {
					break;
				}
			}
			if (e == 0 && g_100e74c < 0x10) {
				g_100dbc0[g_100e74c++] = m;
			}
		}
		if (g_100e74c == 0) {
			ai_MeisterCollectTrans(a);
			return;
		}
		*(int *) (a + 0x1b4) |= 0x20;
		fcn_00485970(a, t, flag);
		h = *(char **) (a + 0x16c);
		lvl = ((Level*) lpGebaeudePROT)[*(unsigned char *) h].level;
		if (lvl == 1) {
			f = *(int *) (h + 0x39) * 1.5625e-05f;
		} else if (lvl == 2) {
			f = *(int *) (h + 0x39) * 7.8125e-06f;
		} else if (lvl == 3) {
			f = *(int *) (h + 0x39) * 3.90625e-06f;
		}
		f = f * 0.5f + 0.25f;
		if (g_100b0a8 != 0) {
			if (g_100b0ac != 0) {
				if (g_100b0f4 * g_100b0e0 * f > (1.0f - f) * g_100d10c * g_100d0f4) {
					fcn_0048c5b0(a, t);
				} else {
					fcn_0048cdb0(a, t);
				}
			} else {
				fcn_0048c5b0(a, t);
			}
		} else if (g_100b0ac != 0) {
			fcn_0048cdb0(a, t);
		}
		if (g_100dc20.owner == *(char **) (a + 0x16c)) {
			for (i = 0; g_100dc20.count < 4 && i < g_100b0a8; i++) {
				g_100dc20.lights[g_100dc20.count] = g_100b0c0[i];
				g_100dc20.count++;
			}
		}
	} else {
		*(int *) (a + 0x1b4) &= ~0x20;
	}
}
