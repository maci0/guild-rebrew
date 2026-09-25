// FUNCTION: GOLDTL 0x005dfe80
// SIZE: 478

typedef struct IdList {
	char pad0[0x28];
	int* ids;
	int count;
} IdList;

typedef struct Obj2f4 {
	char pad0[0x20];
	int kind;
	char pad24[0x2f4 - 0x24];
} Obj2f4;
// SIZE 0x2f4

extern int g_6b7fac;
extern char g_77534d;
extern int g_7e46ac;
extern IdList* g_77255c;
extern Obj2f4* g_1015ea0;
extern int g_100f1dc;
extern int g_774654;
extern int g_14ce8e0;
extern char s_68d760[];
extern char s_68d74c[];
extern char s_68d730[];
extern char s_68d714[];
extern char s_68d704[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00519190(int);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_004693b0(int);
void __cdecl fcn_00469470(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00469630(int);
void __cdecl fcn_004707d0(int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005dfe80(int arg, unsigned int flags)
{
	int h;
	int wflags;
	int result;
	int start;
	int ctx;
	int i;
	int id;

	start = g_6b7fac;
	result = 0;
	if (g_77534d) {
		return 0;
	}
	wflags = g_7e46ac & ~0x38;
	if (flags & 2) {
		h = fcn_00470820(0, 0, s_68d760);
	} else if (flags & 0x10) {
		h = fcn_00470820(0, 0, s_68d74c);
	} else if (flags & 0x20) {
		h = fcn_00470820(0, 0, s_68d730);
	} else if (flags & 0x100) {
		h = fcn_00470820(0, 0, s_68d714);
		fcn_004727a0(h, 1);
	} else {
		h = fcn_00470820(0, 0, s_68d704);
	}
	if (flags & 8) {
		wflags = 0x717c6;
	}
	fcn_00519190(arg);
	fcn_00471b60(h);
	g_77534d = 1;
	ctx = fcn_004693b0(0);
	for (i = 0; i < g_77255c->count; i++) {
		id = g_77255c->ids[i];
		if (g_1015ea0[id].kind != 0x40) {
			fcn_00469470(ctx, id);
		}
	}
	while (fcn_005373e0(fcn_005dfe80, wflags)) {
		fcn_00469630(ctx);
		if (flags & 0x40) {
			fcn_004707d0(h);
		}
		if (g_100f1dc != 2) {
			if (g_100f1dc == 1) {
				g_774654 = 1;
				result = 0;
			}
		} else {
			g_774654 = 1;
			result = 1;
		}
		if (g_14ce8e0) {
			g_774654 = 1;
		}
		if ((flags & 4) && (unsigned int) g_6b7fac > (unsigned int) (start + 500)) {
			g_774654 = 1;
		}
	}
	g_77534d = 0;
	fcn_00469510(ctx);
	fcn_00471e30(h);
	return result;
}

