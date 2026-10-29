


// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_004c2db0(int, int);
char* __cdecl fcn_0058e220(char*, char*);
unsigned short* __cdecl fcn_004f65a0(struct house*, int, int*, int*);
float __cdecl fcn_004f4770(char*);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_004c58b0(int, int);
void __cdecl fcn_005782f0(struct house*, int);
int __cdecl fcn_00519190();
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_004c30a0(int, int, char*, int, int);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00428720(char*);

void __cdecl fcn_0058e510(char* e, char* res)
{
	char* m;
	int list[4];
	unsigned short* p;
	int b;
	int h;
	int t;
	int i;
	int v;
	int cnt;
	float f;

	fcn_004c2db0(*(int*) (res + 0x14), *(int*) (res + 0x4c));
	m = fcn_0058e220(e, res);
	p = fcn_004f65a0(&((struct house*)g_7f4ca0)[g_774970], 4, list, &cnt);
	b = p == 0;
	f = fcn_004f4770(e);
	if (gm_RandomFloat01() + f - 0.1f < 1.0f) {
		b = 2;
	}
	h = fcn_00470820(0, 0, "Locations\\Friedhof\\Friedhof");
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	d2_SetForm(h, 0);
	fcn_005340f0(g_772514);
	g_100f1dc = -1;
	d2_SetForm(h, 1);
	t = fcn_004c2db0(*(int*) (res + 0x14), *(int*) (res + 0x4c));
	if (b == 0) {
		for (i = 0; i < cnt; i++) {
			fcn_004c58b0(list[i], ((struct house*)g_7f4ca0)[g_774970].handle);
		}
		fcn_005782f0(&((struct house*)g_7f4ca0)[g_774970], 1);
		fcn_00519190(0x40ef, 0x40cc, *p);
		fcn_004c30a0(t, 0, "GEIST_KOMMT", gm_RandomMod(8), 0xfa);
	} else if (b == 1) {
		v = (gm_RandomMod(0x200) + 0x200) << 5;
		fcn_004c5150(((struct house*)g_7f4ca0)[g_774970].handle, -1, g_773d75, v);
		fcn_00519190(0x40f0, 0x40cc, v);
		fcn_004c30a0(t, 0, "GEIST_KOMMT", gm_RandomMod(8), 0xfa);
	} else {
		fcn_00519190(0x40d3, 0x40cc);
		fcn_004c30a0(t, 0, "GEIST_KOMMT_NICHT", gm_RandomMod(8), 0xfa);
	}
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_0058e510, 0x777c7) != 0);
	fcn_00471e30(h);
	if (m != 0) {
		fcn_00428720(m);
	}
}
