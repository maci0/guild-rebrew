

extern int g_7746a0;
extern int g_14b5a20;
extern char g_6ad4c0[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005e5a50(int);

/* ADDRESS: GOLD 0x5a3c70 */
void __cdecl fcn_005e68e0(int a)
{
	int x;

	fcn_005338a0();
	while (fcn_005373e0(fcn_005e68e0, 0x67fff) != 0) {
		x = fcn_005338d0(g_6ad4c0, g_14b5a20, 0x16);
		if (g_7746a0 != 0 && g_7746a0 == x) {
			fcn_005e5a50(a);
		}
	}
}
