// FUNCTION: GOLD 0x00587f60
// FUNCTION: GOLDTL 0x00590500

extern unsigned int g_6a9654;
extern int g_6b7fac;
extern int g_774800;
extern float g_664090;
extern int g_67a370;
extern char* g_7e4260[32];
extern char s_6a99c4[];

double __cdecl gm_RandomFloat01(void);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_00426fd0(char*);
void __cdecl fcn_00428340(int, int, int, int, int);

void __cdecl fcn_00590500(void)
{
	int va;
	char* list[32];
	int n;
	int vb;
	int i;
	int k;
	int s;
	char* e;
	char* e1;
	char* e2;

	e2 = 0;
	n = 0;
	vb = -1;
	va = 0;
	if ((*(volatile unsigned int*)&g_6b7fac) < g_6a9654 + 4500) {
		return;
	}
	g_6a9654 = (*(volatile unsigned int*)&g_6b7fac);
	if (g_774800 == 0 && (float) gm_RandomFloat01() < g_664090) {
		return;
	}
	for (i = 0; i < 32; i++) {
		e = g_7e4260[i];
		if (e != 0 && e[2] == 0x14 && *(char**) (e + 0x184) != 0
		    && *(int*) (*(char**) (e + 0x184) + 0x88) == g_67a370) {
			list[n++] = e;
		}
	}
	if (n == 0) {
		return;
	}
	e1 = list[gm_RandomMod(n)];
	if (n > 1) {
		k = gm_RandomMod(n);
		e2 = list[k];
		if (e2 == e1) {
			e2 = list[(k + 1) % n];
		}
	}
	if (e1 != 0) {
		if (e1[9] == 1) {
			va = (*(unsigned int*) (e1 + 4) & 1) + 3;
		} else {
			va = *(unsigned int*) (e1 + 4) % 3;
		}
	}
	if (e2 != 0) {
		if (e2[9] == 1) {
			vb = (*(unsigned int*) (e2 + 4) & 1) + 3;
		} else {
			vb = *(unsigned int*) (e2 + 4) % 3;
		}
	}
	s = fcn_00426fd0(s_6a99c4);
	if (s != 0) {
		fcn_00428340(s, 3, *(int*) (e1 + 0x184), va, vb);
	}
}
