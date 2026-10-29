
extern int g_6b7fac;
extern int g_67a370;
extern int g_77250c;
extern char* g_14a5320[];

// SIZE 0x10c
struct s_7e6060 {
	int a;
	int t;
	char* o;
	char name[0x100];
};

extern struct s_7e6060 g_7e6060[64];

void __cdecl fcn_00472880(int);
char __cdecl fcn_00443e10(void*, int*);
void __cdecl fcn_0046bd20(int, int, int, int, int, char*, int);

/* ADDRESS: GOLDTL 0x00532650 */
void __cdecl fcn_00532650(void)
{
	char** q;
	char** s;
	char* e;
	char* m;
	char* name;
	int r[4];

	for (q = &g_7e6060[0].o; (int) q < (int) &g_7e6060[64].o;
		q = (char**) ((char*) q + sizeof(struct s_7e6060))) {
		if (*q != 0
			&& (*(volatile unsigned int*) &g_6b7fac) > (unsigned int) (((int*) q)[-1] + 0x12c)) {
			*q = 0;
		}
	}
	fcn_00472880(0x54);
	for (s = &g_7e6060[0].o; (int) s < (int) &g_7e6060[64].o;
		s = (char**) ((char*) s + sizeof(struct s_7e6060))) {
		e = *s;
		if (e == 0) {
			continue;
		}
		m = *(char**) (e + 0x34);
		if (*(int*) (m + 0x20c) != g_67a370) {
			continue;
		}
		if (*(int*) (m + 0x218) == 1) {
			m = *(char**) (e + 0x22c);
			if (m == 0) {
				continue;
			}
			if (*(int*) (m + 0x218) == 1) {
				continue;
			}
		}
		if (!fcn_00443e10(m, r)) {
			continue;
		}
		if (((char*) s)[4] != 0) {
			name = (char*) s + 4;
		} else {
			name = g_14a5320[((int*) s)[-2]];
		}
		fcn_0046bd20((r[2] - r[0]) / 2 + r[0] - 0x50, r[1] - 0x40, 0xa0, 0x60,
			g_77250c, name, 0x28);
	}
}
