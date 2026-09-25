// FUNCTION: GOLD 0x00577800
// SIZE: 120
// FUNCTION: GOLDTL 0x0057fdd0
// SIZE: 120

extern unsigned char* g_7746c4;
extern char* g_868050;
extern char g_6b5c60[];
extern unsigned short g_774970;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_00526920(char*, int, char*);

void __cdecl fcn_0057fdd0(int a)
{
	char* e;
	char* r;

	if (a == 0) {
		if (g_7746c4 == 0 || g_868050[*g_7746c4 * 589] != 2) {
			e = gm_StartFilteredEntitySearch(2, 5, 2, 4, g_774970);
			if (e != 0) {
				r = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0x13);
				if (r != 0) {
					fcn_00526920(e, *(int*) (r + 2), g_6b5c60);
				}
			}
		}
	}
}
