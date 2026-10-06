// FUNCTION: GOLDTL 0x00423010

// SIZE 0x30
typedef struct {
	int h;
	char* sample;
	int prio;
	int loop;
	int time;
	int flags;
	int f18;
	int f1c;
	int f20;
	int vol;
	int pan;
	int f2c;
} Voice;

extern int g_6b7d7c;
extern char* g_6b7e88;
extern int g_6b7e8c;
extern int g_6b7e90;
extern int g_678dec;
extern int g_6b7fac;
int __cdecl fcn_0042aaa0(int h);
void __cdecl fcn_004237f0(Voice* v, int a);

void __cdecl fcn_00423010(int fade)
{
	int i;
	int t;
	Voice* v;

	if (g_6b7d7c == 0) {
		return;
	}
	if (fade == 0) {
		for (i = 0; i < g_6b7e8c; i++) {
			v = &((Voice*)g_6b7e88)[i];
			if (v->sample != 0 && fcn_0042aaa0(v->h) == 4) {
				fcn_004237f0(v, 0);
			}
		}
		return;
	}
	t = (*(volatile int*)&g_6b7fac) * 8 + (*(volatile int*)&g_6b7fac) * 4 + (*(volatile int*)&g_6b7fac);
	g_678dec = fade;
	g_6b7e90 = 1;
	for (i = 0; i < g_6b7e8c; i++) {
		v = &((Voice*)g_6b7e88)[i];
		if (v->sample != 0 && fcn_0042aaa0(v->h) == 4) {
			v->time = t;
		}
	}
}
