


extern unsigned short* g_7e431c;
typedef struct
{
	char type;
	char pad1[64];
} Rec65;
// SIZE 0x41

extern char* g_99ec10;
extern unsigned char* g_7746c8;
extern unsigned short g_774970;
extern int g_774650;
extern int g_774658;
extern int g_7e2700;
extern int g_7e2708;
extern unsigned char* g_7e2704;
extern int g_7746b8;
extern int g_7746f0;
extern unsigned char* g_868050;

int __cdecl fcn_00506380(int, unsigned char*, unsigned short*, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_005a86a0(int);
void __cdecl fcn_005167c0(unsigned char*, int);
void __cdecl fcn_00516c50(unsigned char*, int);
void __cdecl fcn_00597ec0(unsigned char*);

void __cdecl fcn_0059a0e0(void)
{
	int x;
	unsigned char* e;
	char* r;

	if (g_7e431c != 0) {
		r = &((Rec65*)g_99ec10)[*g_7e431c].type;
		if ((*r == 6 || *r == 2) && (fcn_00506380(g_774970, g_7746c8, g_7e431c, 0) & 0x4000)) {
			x = fcn_00502cd0(*(int*) (g_7746c8 + 0x5d), 2, 6, 0, 0xfd);
			fcn_005a86a0((int) g_7e431c);
			fcn_005167c0(g_7746c8, 0xfd);
			fcn_00516c50(g_7746c8, x);
			g_774658 = g_774650;
		}
	}
	if (g_7e2700 != 0 && g_7e2708 != 0 && g_7e2704 == g_7746c8) {
		x = fcn_00502cd0(*(int*) (g_7746c8 + 0x5d), 2, 6, 0, 0xfd);
		if (g_7e2708 != x) {
			fcn_005a86a0(g_7e2708);
			fcn_005167c0(g_7746c8, 0xfd);
			fcn_00516c50(g_7746c8, x);
		} else {
			g_7e2700 = 0;
			g_7e2708 = 0;
			g_7e2704 = 0;
		}
	}
	if (g_7746b8 != 0 && g_7746f0 == 0) {
		x = fcn_00502cd0(*(int*) (g_7746c8 + 0x5d), 2, 6, 0, 0xfd);
		fcn_005a86a0(g_7746b8);
		fcn_005167c0(g_7746c8, 0xfd);
		fcn_00516c50(g_7746c8, x);
	}
	e = g_7746c8;
	r = ((char*)g_868050) + *e * 589;
	if (*e == 0x20 || *e == 0x1f || *e == 0x1e || r[0] == 0x1f || r[0] == 0x1d) {
		fcn_00597ec0(e);
	}
}
