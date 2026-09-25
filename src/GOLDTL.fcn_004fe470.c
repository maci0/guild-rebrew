// FUNCTION: GOLD 0x004fbd10
// SIZE: 384
// FUNCTION: GOLDTL 0x004fe470
// SIZE: 384

extern int g_6b8010;
extern char* g_7746c4;
extern char* g_7746c8;
extern char g_675908[];
extern char g_68149c[];
extern char g_6753fc[];

char* __cdecl fcn_00508e40(int id);
char* __cdecl gm_StartFilteredEntitySearch(int mode, int kind, int type);
char* __cdecl fcn_00502cd0(int obj, int mode, ...);
int __cdecl gm_CheckEntityType(char* e);
int __cdecl fcn_005155e0(char* e);
int __cdecl fcn_00515540(char* q);
void __cdecl fcn_004432d0(int a, int b);
char* __cdecl fcn_00407330(void);
void __cdecl fcn_004fe2e0(char* o, int h, int x, int y, int view, char* name);
void __cdecl fcn_00404a00(char* v, int n, ...);
void __cdecl fcn_00402a00(char* v, int a);

char* __cdecl fcn_004fe470(int id, int type, int sub, int x, int y)
{
	int old;
	char* o;
	char* b;
	char* q;
	char* m;
	int h;

	q = 0;
	old = g_6b8010;
	o = fcn_00508e40(id);
	if (o == 0 || *(char**) (o + 0x184) != 0) {
		return 0;
	}
	b = gm_StartFilteredEntitySearch(1, 1, type);
	if (b == 0) {
		return 0;
	}
	if (sub != -1) {
		q = fcn_00502cd0(*(int*) (b + 0x5d), 1, 1, sub);
		if (q == 0) {
			return 0;
		}
	}
	if (gm_CheckEntityType(b)) {
		h = fcn_005155e0(b);
	} else if (q != 0) {
		h = fcn_00515540(q);
	} else {
		h = 0;
	}
	if (h < 0) {
		return 0;
	}
	fcn_004432d0(h, 1);
	if (q != 0) {
		m = fcn_00407330();
		if (m != 0) {
			fcn_004fe2e0(o, h, x, y, 0, m);
		} else {
			fcn_004fe2e0(o, h, x, y, 0, g_675908);
		}
	} else {
		fcn_004fe2e0(o, h, 0, 0, *(int*) (b + 0x61), g_68149c);
	}
	if (*(char**) (o + 0x184) != 0) {
		fcn_00404a00(*(char**) (o + 0x184), 1, g_6753fc);
	}
	fcn_004432d0(old, 1);
	if (*(char**) (o + 0x184) == 0) {
		return 0;
	}
	*(int*) (*(char**) (o + 0x184) + 0x2c) = type;
	*(int*) (*(char**) (o + 0x184) + 0x30) = sub;
	if ((g_7746c4 != 0 && g_7746c4 != b) || (g_7746c8 != 0 && g_7746c8 != b)) {
		fcn_00402a00(*(char**) (o + 0x184), 0);
	}
	return *(char**) (o + 0x184);
}
