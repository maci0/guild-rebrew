


typedef struct
{
	char pad0[0x247];
	unsigned char x247;
	char pad248[5];
} Shop;
// SIZE 0x24d

extern unsigned char* lpGebaeudePROT;
extern int g_7746d8;
extern int g_7746a0;
extern int g_14abaa4;
extern int g_14abaf4;
extern int g_14ad108;
extern int g_14ad178;
extern int g_14a7c98;
extern int g_14a7b50;
extern int g_14a7d28;
extern char s_6ab260[];
extern char s_6ab24c[];
extern char s_6aa544[];
extern char s_6aa584[];
extern char s_6ab230[];
extern char s_6ab214[];
extern char s_6aa34c[];
extern char s_6a9924[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_00442d50(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005ad5a0(unsigned char*);
void __cdecl fcn_005ad950(unsigned char*);
void __cdecl fcn_005adfa0(unsigned char*);
void __cdecl fcn_005ae000(unsigned char*);
void __cdecl fcn_005b6300(unsigned char*, char*);
void __cdecl fcn_005ada30(unsigned char*);
void __cdecl fcn_005cf560(unsigned char*);

void __cdecl fcn_005ae1b0(unsigned char* arg)
{
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
	int g;
	int r;
	Shop* t;

	d = 0;
	a = 0;
	b = 0;
	c = 0;
	g = 0;
	f = 0;
	e = 0;
	fcn_005338a0();
	t = &((Shop*)lpGebaeudePROT)[arg[0]];
	if (t->x247 >= 2) {
		r = fcn_00445600(0, 0xc0, 0, s_6ab260);
		if (r != 0) {
			fcn_00442d50(r, 1);
		}
	}
	else {
		r = fcn_00445600(0, 0xc0, 0, s_6ab260);
		if (r != 0) {
			fcn_00442d50(r, 0);
		}
	}
	if (fcn_005373e0((void*) fcn_005ae1b0, 0x67fff) != 0) {
		do {
			if (g_7746d8 & 0x200) {
				a = fcn_005338d0(s_6ab24c, g_14abaa4, 0x17);
				b = fcn_005338d0(s_6aa544, g_14abaf4, 0x17);
				if (t->x247 >= 2) {
					c = fcn_005338d0(s_6aa584, g_14ad108, 0x17);
				}
				d = fcn_005338d0(s_6ab230, g_14ad178, 0x17);
				e = fcn_005338d0(s_6ab214, g_14a7c98, 0x16);
			}
			if (g_7746d8 & 0x400) {
				f = fcn_005338d0(s_6aa34c, g_14a7b50, 0xc);
				g = fcn_005338d0(s_6a9924, g_14a7d28, 0x16);
			}
			if (g_7746a0 != 0) {
				if (g_7746a0 == a) {
					fcn_005ad5a0(arg);
				}
				else if (g_7746a0 == b) {
					fcn_005ad950(arg);
				}
				else if (g_7746a0 == c) {
					fcn_005adfa0(arg);
				}
				else if (g_7746a0 == d) {
					fcn_005ae000(arg);
				}
				else if (g_7746a0 == f) {
					fcn_005b6300(arg, s_6aa34c);
				}
				else if (g_7746a0 == e) {
					fcn_005ada30(arg);
				}
				else if (g_7746a0 == g) {
					fcn_005cf560(arg);
				}
			}
		} while (fcn_005373e0((void*) fcn_005ae1b0, 0x67fff) != 0);
	}
}
