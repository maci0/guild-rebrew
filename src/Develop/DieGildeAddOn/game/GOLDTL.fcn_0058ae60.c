extern int g_7746d8;
extern char* g_14b5494;
extern int g_14ce8e0;
extern int g_774654;
extern char* g_7746a0;

void __cdecl fcn_005338a0(void);
char* __cdecl fcn_005338d0(char* name, char* path, int arg);
int __cdecl fcn_005373e0(void* p, int mask);
void __cdecl fcn_0058acb0(int unused, char* p);
void __cdecl fcn_00586c10(int h);
void __cdecl fcn_0058ae60(int a0, char* a1);

/* ADDRESS: GOLDTL 0x0058ae60 */
void __cdecl fcn_0058ae60(int a0, char* a1)
{
	char* v;

	v = 0;
	fcn_005338a0();
	if (!fcn_005373e0((void*) fcn_0058ae60, 0x67fff)) {
		return;
	}
	do {
		if (g_7746d8 & 0x400) {
			v = fcn_005338d0("contact_KANONE", g_14b5494, 0x16);
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_7746a0 != 0) {
			if (*(int*) (a1 + 0x1c) != 0) {
				fcn_0058acb0(a0, a1);
			} else if (g_7746a0 == v) {
				fcn_00586c10(a0);
			}
		}
	} while (fcn_005373e0((void*) fcn_0058ae60, 0x67fff));
}
