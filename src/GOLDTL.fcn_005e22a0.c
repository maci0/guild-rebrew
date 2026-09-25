// FUNCTION: GOLDTL 0x005e22a0
// SIZE: 621

typedef struct Flags215 {
	char pad0[0x215];
	unsigned char lit : 1;
	unsigned char mirror : 1;
} Flags215;
// SIZE 0x216

typedef struct Node {
	char pad0[0x34];
	Flags215* flags;
	char pad38[0x88 - 0x38];
	void* owner;
} Node;
// SIZE 0x8c

typedef struct Pair {
	int a;
	int b;
} Pair;
// SIZE 0x8

extern unsigned char g_776664;
extern unsigned char g_776665;
extern unsigned char g_776666;
extern unsigned char g_776667;
extern unsigned char g_776668;
extern unsigned char g_776669;
extern unsigned char g_77666b;
extern int g_77666c;
extern float g_776670[3];
extern float g_77667c;
extern float g_776680[3];
extern float g_77668c;
extern float g_776690[3];
extern float g_77669c;
extern int g_104061c;
extern unsigned char g_6752a4;
extern int g_104336c;
extern int g_67ac90;
extern int g_6b8010;
extern int g_7746c4;
extern int g_7746c8;
extern float g_67a964;
extern Node* g_14d0020[768];
extern char g_10432c0;
extern Pair g_6a2528[];
extern Pair g_6a2540[];
extern Pair g_6a2558;
extern Pair g_6a2560;
extern unsigned char g_774964;
extern int g_774694;
extern unsigned char g_6b8304;

void __cdecl fcn_00516de0(int, int);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_0043ac00(int, int, int);
void __cdecl fcn_00439690(unsigned char, int, unsigned char, int, int);
void __cdecl fcn_00403330(unsigned char);
void __cdecl fcn_0052ac60(int);
void __cdecl fcn_0043bbf0(unsigned char);
void __cdecl fcn_00598510(void);
void __cdecl fcn_0043ace0(int);
void __cdecl fcn_0041b820(float*, float*, float*);

void __cdecl fcn_005e22a0(void)
{
	unsigned char hi;
	float c[3];
	float b[3];
	float a[3];
	int depth;
	int width;
	int saved;
	int i;
	float s;

	depth = 0;
	width = g_104061c;
	hi = 0;
	if (g_776667 == 0) {
		hi = g_776667;
		g_6752a4 = 1;
		width = 0x20;
	} else if (g_776667 == 1) {
		g_6752a4 = g_776667;
		width = 0x20;
		hi = 1;
	} else if (g_776667 == 2) {
		g_6752a4 = 0;
		width = 0x40;
		hi = 1;
	}
	fcn_00516de0(g_104336c, 0);
	if (g_776666 == 0) {
		depth = 2;
	} else if (g_776666 == 1) {
		depth = 4;
	}
	if (depth != g_67ac90) {
		saved = g_6b8010;
		g_67ac90 = depth;
		fcn_004432d0(0, 0);
		fcn_0043ac00(0x40, 3, 0);
		fcn_004432d0(saved, 0);
	}
	fcn_00439690(g_776668, 0, 2 - g_776665, hi * width, 0);
	if (g_7746c4 == 0 && g_7746c8 == 0) {
		g_67a964 = (float) (1.0 - (g_77666c & 0xff) * 0.01);
	}
	for (i = 0; i < 768; i++) {
		if (g_14d0020[i] != 0 && g_14d0020[i]->owner == &g_10432c0) {
			g_14d0020[i]->flags->mirror = g_6752a4;
		}
	}
	fcn_00403330(g_77666b);
	g_6a2558 = g_6a2528[g_776669];
	g_6a2560 = g_6a2540[g_776669];
	if (g_774964) {
		fcn_0052ac60(g_774694);
	}
	if (g_6b8304 != g_776668) {
		fcn_0043bbf0(g_776668);
	}
	saved = g_6b8010;
	fcn_004432d0(0, 1);
	fcn_00598510();
	if (g_776664 == 0) {
		fcn_0043ace0(0);
	} else {
		fcn_0043ace0(1);
	}
	fcn_004432d0(saved, 1);
	s = (g_77667c + 0.5f) * 0.5f;
	for (i = 0; i < 3; i++) {
		a[i] = s + g_776670[i] - 0.5f;
		b[i] = g_77668c * g_776680[i];
		c[i] = g_77669c * g_776690[i];
	}
	fcn_0041b820(a, b, c);
}
