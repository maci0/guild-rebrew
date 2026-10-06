// FUNCTION: GOLDTL 0x005acf90

extern int g_7746a0;
extern int g_14ab9d0;
extern char g_6ab158[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005aceb0(int);

void __cdecl fcn_005acf90(int a)
{
	int x;

	fcn_005338a0();
	while (fcn_005373e0(fcn_005acf90, 0x67fff) != 0) {
		x = fcn_005338d0(g_6ab158, g_14ab9d0, 0x16);
		if (g_7746a0 != 0 && g_7746a0 == x) {
			fcn_005aceb0(a);
		}
	}
}
