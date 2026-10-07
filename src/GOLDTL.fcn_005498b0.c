// FUNCTION: GOLDTL 0x005498b0

#include <string.h>

#pragma pack(push, 2)
typedef struct {
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time;
// SIZE 0xe
#pragma pack(pop)

typedef struct {
	int f0;
	unsigned char type;
	char pad5[3];
	int who;
	int fc;
	char pad10[0x18];
	Time t;
	unsigned char f36;
	char pad37[0x21];
	int f58;
	char pad5c[0x9c];
} Msg;
// SIZE 0xf8

extern char g_7f4ca4[];
extern Time g_7f4c00;

void __cdecl fcn_0051af00(char *, int, ...);
void __cdecl fcn_00545e80(int, int, char *, int, int, int, int, int, int);
void __cdecl fcn_004c5530(Msg *);
float __cdecl fcn_004feff0(char *);
int __cdecl fcn_00567170(char *, int *, int *, int);
void __cdecl fcn_00529160(int, int, int, int);
char *__cdecl fcn_00426cc0(int);
int __cdecl fcn_00428720(char *);
void __cdecl fcn_004c5da0(int, int, int, int, int, char *);

void __cdecl fcn_005498b0(char *a1, char *a2, char *a3, char *a4, int a5, float a6)
{
	int x0;
	int x4;
	Msg m;
	char buf[0x800];

	if (a6 <= 0.0f) {
		if (a3[2] == 6 || a3[2] == 7) {
			fcn_0051af00(buf, 0x1632, *(unsigned short *) a2, a4);
			fcn_00545e80(*(int *) (a3 + 4), *(int *) (a4 + 1), buf, 0, 0x5ed, *(int *) (a4 + 1), -1, 0, 0);
		}
		memset(&m, 0, sizeof(m));
		m.type = 0x71;
		if (a1 != 0) {
			m.who = *(int *) (g_7f4ca4 + *(unsigned short *) (a1 + 8) * 0x21c);
		} else {
			m.who = *(int *) (a3 + 4);
		}
		m.fc = -1;
		m.t = g_7f4c00;
		m.f36 = 2;
		m.f58 = *(int *) (a2 + 4);
		fcn_004c5530(&m);
	} else {
		if (fcn_004feff0(a2) * 0.5f > a6 && fcn_00567170(a2, &x0, &x4, 0) != 0 && *(char **) (a2 + 0x184) != 0) {
			fcn_00529160(0, 0, *(unsigned short *) a2, 0);
			if (*(int *) (*(char **) (a2 + 0x184) + 0x28) != -1) {
				fcn_00428720(fcn_00426cc0(*(int *) (*(char **) (a2 + 0x184) + 0x28)));
			}
			if (x4 == -1) {
				fcn_004c5da0(*(int *) (a2 + 4), x0, x4, 0, 1, "Unfall");
			} else {
				fcn_004c5da0(*(int *) (a2 + 4), x0, x4, 0, 0, "Unfall");
			}
			if (a3[2] == 6 || a3[2] == 7) {
				fcn_0051af00(buf, 0x1631, *(unsigned short *) a2, a4, a5 + 0x1626);
				fcn_00545e80(*(int *) (a3 + 4), *(int *) (a4 + 1), buf, 0, 0x5ed, *(int *) (a4 + 1), -1, 0, 0);
			}
			return;
		}
		if (a3[2] == 6 || a3[2] == 7) {
			fcn_0051af00(buf, 0x1630, *(unsigned short *) a2, a4, a5 + 0x1626);
			fcn_00545e80(*(int *) (a3 + 4), *(int *) (a4 + 1), buf, 0, 0x5ed, *(int *) (a4 + 1), -1, 0, 0);
		}
	}
}
