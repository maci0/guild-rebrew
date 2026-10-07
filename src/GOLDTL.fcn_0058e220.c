/* Entity row walked by fcn_0058e220. */
// SIZE 0x21c
typedef struct
{
	char pad0[9];
	unsigned char b9;
	char pada[0x164 - 0xa];
	unsigned char b164;
	char pad165[0x21c - 0x165];
} fcn_0058e220_Ent;

extern fcn_0058e220_Ent g_7f4ca0[];
extern unsigned short g_774970;
extern volatile unsigned int g_6b7fac;
extern int g_774654;
extern char g_6a97f8[];
extern char g_6a97d4[];
extern char g_68b3f8[];
extern char g_6a97b8[];

void __cdecl fcn_0058e4a0(int n, int* a, int* b, int base);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int a1, int idx);
void __cdecl fcn_00471db0(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00426fd0(char* name);
char* __cdecl fcn_004fd9d0(int, int);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_004284d0(int, char*);
int __cdecl fcn_004273c0(void);
int __cdecl fcn_004c30a0(int, int, char*, int, int);
int __cdecl fcn_00423460(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00519190(int);
void __cdecl fcn_00471e30(int);

typedef struct { char pad[0x48]; int x48; int x4c; } S58;

// FUNCTION: GOLDTL 0x0058e220
int __cdecl fcn_0058e220(int a1, S58* a2)
{
	int h;
	unsigned int wait[9];
	int snd[8];
	int ids[8];
	char name[0x100];
	char text[0x400];
	int w;
	char* p;
	char* q;
	unsigned int t0;
	int i;
	int j;
	int k;

	fcn_0058e4a0(8, snd, ids, 0x40d7);
	w = fcn_00470820(0, 0, g_6a97f8);
	fcn_00473a90(0, 0);
	fcn_00471db0(w, 1);
	fcn_004727a0(w, 0);
	h = fcn_00426fd0(g_6a97d4);
	if (h != 0) {
		p = fcn_004fd9d0(g_7f4ca0[g_774970].b9, g_7f4ca0[g_774970].b164);
		if (p == 0)
			fcn_004fd9d0(g_7f4ca0[g_774970].b9, 0);
		q = fcn_004fd9d0(a2->x4c, a2->x48);
		if (q == 0)
			q = fcn_004fd9d0(a2->x4c, 0);
		fcn_0064d41a(text, g_68b3f8, p + 4, q + 4);
		fcn_004284d0(h, text);
	}
	k = fcn_004273c0();
	i = 0;
	if (k != 0) {
		for (; i < 8; i++) {
			k = snd[i] - 0x40d7;
			fcn_0064d41a(name, g_6a97b8, k / 6 + 1, k % 6);
			wait[i] = fcn_004c30a0(-7, 0, name, -1, 0x64);
		}
		for (j = 0; j < 8; j++) {
			while (fcn_00423460(wait[j]) == 0)
				fcn_005373e0(0, 0x743c7);
			fcn_004727a0(w, 0);
			fcn_00519190(snd[j]);
			while (fcn_00423460(wait[j]) != 0)
				fcn_005373e0(0, 0x743c7);
		}
	} else {
		t0 = g_6b7fac;
		wait[0] = 0x47;
		wait[1] = 0xf8;
		wait[2] = 0xf8;
		wait[3] = 0xf8;
		wait[4] = 0xf8;
		wait[5] = 0xf8;
		wait[6] = 0xf8;
		wait[7] = 0xf8;
		wait[8] = 0xf8;
		do {
			if (wait[i] + t0 < g_6b7fac) {
				t0 = g_6b7fac;
				fcn_004727a0(w, 0);
				if (i >= 8) {
					g_774654 = 1;
				} else {
					fcn_004727a0(w, 0);
					fcn_00519190(snd[i]);
					i++;
				}
			}
		} while (fcn_005373e0(fcn_0058e220, 0x743c7) != 0);
	}
	fcn_00471e30(w);
	return h;
}
