

typedef struct {
	int a;
	int b;
	int c;
	int d;
} Msg;
// SIZE 0x10

typedef void (__cdecl* MsgFn)(Msg*);

typedef struct {
	char pad0[8];
	int kind;
	char padc[0x38 - 0xc];
	MsgFn cb;
	char pad3c[4];
	int key;
	int wait;
	int next;
	int alt_key;
} Cfg;
// SIZE 0x50

typedef struct {
	int state;
	int want;
	char pad8[4];
	unsigned int since;
	int ticks;
	char pad14[4];
	Cfg* cfg;
	char pad1c[0x2c - 0x1c];
	int done;
	int busy;
	char pad34[0x3c - 0x34];
	int mode;
	char pad40[0x50 - 0x40];
	int arg;
} Seq;
// SIZE 0x54

extern int g_774a14;
extern Seq* g_665f08;
extern volatile unsigned int g_6b7fac;

void __cdecl fcn_005804f0(void);
void __cdecl fcn_00584160(int);

void __cdecl fcn_0057e880(int a, int b, int c, int d)
{
	Msg m;

	if (g_774a14 == 0 || g_665f08->cfg == 0) {
		return;
	}
	m.a = a;
	m.b = b;
	m.c = c;
	m.d = d;
	if (g_665f08->cfg->kind != 2) {
		if (g_665f08->want != 4 && g_665f08->want != 0xa) {
			return;
		}
		if (g_665f08->cfg->cb != 0) {
			g_665f08->cfg->cb(&m);
			g_665f08->ticks++;
			return;
		}
		if (g_665f08->cfg->key == 3) {
			if (g_6b7fac > g_665f08->cfg->wait + g_665f08->since) {
				g_665f08->state = g_665f08->cfg->next;
				g_665f08->want = g_665f08->cfg->next;
				g_665f08->since = g_6b7fac;
				g_665f08->done = 1;
			}
			return;
		}
		if (g_665f08->cfg->key != a) {
			goto tick;
		}
		if (c == 0) {
			g_665f08->state = g_665f08->cfg->next;
			g_665f08->want = g_665f08->state;
		} else {
			g_665f08->state = 0xb;
			g_665f08->want = g_665f08->state;
		}
		goto stamp;
	}
	if (g_665f08->want != 4 && g_665f08->want != 9 && g_665f08->want != 0xa) {
		return;
	}
	if (g_665f08->cfg->cb != 0) {
		g_665f08->cfg->cb(&m);
		return;
	}
	if (g_665f08->mode == 1) {
		if (c == 0) {
			if (g_665f08->cfg->key == a) {
				g_665f08->want = 5;
				g_665f08->since = g_6b7fac;
				if (b != 0) {
					g_665f08->arg = b;
					g_665f08->state = g_665f08->want;
					g_665f08->ticks++;
					return;
				}
			}
		} else if (c == 1 && g_665f08->cfg->key == a) {
			g_665f08->want = 4;
			g_665f08->since = g_6b7fac;
			g_665f08->busy = 0;
			fcn_005804f0();
			fcn_00584160(2);
		}
		g_665f08->state = g_665f08->want;
		g_665f08->ticks++;
		return;
	}
	if (g_665f08->mode != 3) {
		goto tick;
	}
	if (g_665f08->want == 9) {
		if (g_665f08->cfg->alt_key != 0 && g_665f08->cfg->alt_key == a) {
			g_665f08->state = 0xa;
			g_665f08->want = 0xa;
			g_665f08->since = g_6b7fac;
			g_665f08->ticks++;
			return;
		}
		if (g_665f08->cfg->key != a || c != 1) {
			goto tick;
		}
		g_665f08->state = 4;
		g_665f08->want = 4;
		g_665f08->since = g_6b7fac;
		g_665f08->busy = 0;
		fcn_005804f0();
		fcn_00584160(2);
		g_665f08->ticks++;
		return;
	}
	if (g_665f08->want == 0xa) {
		if (g_665f08->cfg->key != a || c != 1) {
			goto tick;
		}
		g_665f08->state = 0xb;
		g_665f08->want = 0xb;
	} else {
		if (g_665f08->want != 4 || g_665f08->cfg->key != a || c != 0) {
			goto tick;
		}
		g_665f08->state = 9;
		g_665f08->want = 9;
	}
stamp:
	g_665f08->since = g_6b7fac;
tick:
	g_665f08->ticks++;
}
