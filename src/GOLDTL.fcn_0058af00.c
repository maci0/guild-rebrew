// FUNCTION: GOLD 0x005828c0
// FUNCTION: GOLDTL 0x58af00

extern int g_7746d8;
extern int g_14b5308;
extern int g_14b538c;
extern int g_14b53c8;
extern int g_14b534c;
extern char g_6a9640[];
extern char g_6a9624[];
extern char g_6a9604[];
extern char g_6a95e8[];
extern int g_14ce8e0;
extern int g_774654;
extern int g_7746a0;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void (__cdecl*)(int, char*), int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_0058acb0(int, char*);
void __cdecl fcn_0058a250(int);
void __cdecl fcn_00589930(int);
void __cdecl fcn_0058a6b0(int);
void __cdecl fcn_00589d00(int);

void __cdecl fcn_0058af00(int a, char* b)
{
	int k1;
	int k2;
	int k3;
	int k4;

	k1 = 0;
	k2 = 0;
	k3 = 0;
	k4 = 0;
	fcn_005338a0();
	while (fcn_005373e0(fcn_0058af00, 0x67fff) != 0) {
		if (g_7746d8 & 0x400) {
			k1 = fcn_005338d0(g_6a9640, g_14b5308, 0x16);
			k2 = fcn_005338d0(g_6a9624, g_14b538c, 0x16);
			k3 = fcn_005338d0(g_6a9604, g_14b53c8, 0x16);
			k4 = fcn_005338d0(g_6a95e8, g_14b534c, 0x16);
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_7746a0 != 0) {
			if (*(int*) (b + 0x1c) != 0) {
				fcn_0058acb0(a, b);
			} else if (g_7746a0 == k1) {
				fcn_0058a250(a);
			} else if (g_7746a0 == k2) {
				fcn_00589930(a);
			} else if (g_7746a0 == k3) {
				fcn_0058a6b0(a);
			} else if (g_7746a0 == k4) {
				fcn_00589d00(a);
			}
		}
	}
}
