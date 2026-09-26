// FUNCTION: GOLDTL 0x005b5ce0
// SIZE: 464

typedef struct
{
	char pad0[0x18];
	int x18;
	int x1c;
	char pad20[0x4c];
	int x6c;
	char pad70[0x280];
	int x2f0;
} Ctl;
// SIZE 0x2f4

typedef struct
{
	int x;
	int y;
	unsigned short* obj;
	int icon;
	int x10;
	int label;
	int value;
	int x1c;
	unsigned char state;
} Gauge;

extern char* g_1015ea0;
extern char* g_14abbb0;
extern char* g_14abc28;

char* __cdecl fcn_005463a0(int, int, int, int, int);
void __cdecl fcn_0046f940(int, char*);
void __cdecl fcn_00517c00(int, int, int, char*);
void __cdecl fcn_005b5c70(Gauge*);

void __cdecl fcn_005b5ce0(char* e, Gauge* g, int a3, int a4)
{
	char buf[0x100];
	char* p;
	char* s;
	char* d;

	p = fcn_005463a0(2, 0, a3, 3, *(int*) (e + 1));
	if (p != 0 && *(int*) (p + a4 * 4 + 0xb0) != 0) {
		s = g_14abbb0;
		d = buf;
		while ((*d++ = *s++) != 0) {
		}
		g->state = 2;
		fcn_0046f940(g->label, buf);
		((Ctl*)g_1015ea0)[g->label].x18 = 0xa0;
		((Ctl*)g_1015ea0)[g->label].x1c = 0x28;
		g->state = 2;
		return;
	}
	if (g->obj != 0 && ((char*) g->obj)[8] != 0) {
		fcn_00517c00(*g->obj, 1, 1, buf);
		fcn_0046f940(g->label, buf);
		((Ctl*)g_1015ea0)[g->label].x6c = 1;
		((Ctl*)g_1015ea0)[g->label].x18 = 0xa0;
		g->state = 1;
		return;
	}
	fcn_005b5c70(g);
	s = g_14abc28;
	d = buf;
	while ((*d++ = *s++) != 0) {
	}
	g->state = 0;
	fcn_0046f940(g->label, buf);
	((Ctl*)g_1015ea0)[g->label].x18 = 0xa0;
	((Ctl*)g_1015ea0)[g->label].x1c = 0x28;
	fcn_0046f940(g->value, "");
	g->state = 0;
	((Ctl*)g_1015ea0)[g->icon].x2f0 = 0;
}
