// FUNCTION: GOLDTL 0x004ad8c0
// SIZE: 725

typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[5];
	unsigned char rank;
	char pade[0x1be];
	int mask;
	char pad1d0[0x4c];
} Player;
// SIZE 0x21c

extern Player g_7f4ca0[768];
extern int g_664e1c[3];
extern int g_664e28[3];
extern int g_6653bc;
extern unsigned char g_773d75;

void __cdecl fcn_00508d80(int, int *);
int __cdecl fcn_0064d228(void);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_00507400(int, int);
int __cdecl gm_IsInRange(int);
int __cdecl fcn_004c4fc0(int, int, int, int, int, int, int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
float __cdecl gm_RandomFloat01(void);
char *__cdecl fcn_004c4480(int);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
void __cdecl fcn_004c4510(char *, int);
void __cdecl fcn_004c4570(int, int, int, int *);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5420(int, int, int, int, int);

void __cdecl fcn_004ad8c0(void)
{
	int cnt;
	int seven;
	int kind;
	float score[3];
	int owner[3];
	int kinds[3];
	int ids[15];
	int i;
	int j;
	int k;
	int h;
	int x;
	int v;
	int mask;
	char *o;
	Player *p;

	ids[0] = 1;
	ids[1] = 2;
	ids[2] = 3;
	ids[3] = 4;
	ids[4] = 5;
	ids[5] = 6;
	ids[6] = 7;
	ids[7] = 8;
	ids[8] = 9;
	ids[9] = 10;
	ids[10] = 11;
	ids[11] = 12;
	ids[12] = 13;
	ids[13] = 14;
	ids[14] = 15;
	score[0] = 0.0f;
	score[1] = 0.0f;
	score[2] = 0.0f;
	owner[0] = -1;
	owner[1] = -1;
	owner[2] = -1;
	kinds[0] = 15;
	kinds[1] = 21;
	kinds[2] = 27;
	for (i = 0; i < 768; i++) {
		p = &g_7f4ca0[i];
		if (p->rank >= 7 &&
		    (p->type == 6 || p->type == 7 || p->type == 5 || p->type == 4 ||
			p->type == 3 || p->type == 2)) {
			k = 3;
			do {
				j = k - 1;
				if ((p->mask & g_664e28[j]) == 0 && (p->mask & g_664e1c[j]) != 0) {
					if (p->handle != owner[(j + 1) % 3] && p->handle != owner[(j + 2) % 3]) {
						score[j] += 0.67f;
						owner[j] = p->handle;
					}
					score[j] += 0.33f;
				}
			} while (--k != 0);
		}
	}
	fcn_00508d80(15, ids);
	for (j = 0, k = 0; j < 3; j++) {
		for (cnt = (int) score[j]; cnt < 2; cnt++) {
			x = fcn_00507400(ids[k++], (unsigned short) fcn_0042e410(3) + 4);
			h = fcn_004c4fc0(3, -1, -1, fcn_0042e410(8) + 0x19, -1, x, 0, gm_IsInRange(x));
			if (h != -1) {
				do {
					if (fcn_004c4450(h) != 0) {
						break;
					}
					fcn_00535960();
				} while (1);
			}
			if (fcn_004c4450(h) != 1) {
				return;
			}
			seven = 7;
			v = (int) (g_6653bc * ((gm_RandomFloat01() + 1.0f) * 0.5f));
			kind = kinds[j];
			o = fcn_004c4480(h);
			fcn_004c5150(*(int *) (o + 4), -1, g_773d75, v);
			fcn_004c4510(o, *(int *) (o + 4));
			fcn_004c4570(1, 1, 0xd, &seven);
			fcn_004c4570(1, 1, 0x167, &kind);
			fcn_004c5360();
			mask = g_664e1c[j];
			if (j == 2) {
				mask |= g_664e1c[(unsigned short) fcn_0042e410(j)];
			}
			fcn_004c5420(*(int *) (o + 4), 0x1cc, 4, mask, 0);
		}
	}
}
