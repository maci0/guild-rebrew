extern int g_6b7ec8;
extern char* g_14c9320[0x20];
extern char* g_6b7e98;
extern int g_6791d0;
extern int g_6791c8;
extern int g_6b8010;

void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00429490(char*);
void __cdecl fcn_004291c0(char*);

// FUNCTION: GOLD 0x0042ada0
// SIZE: 326
// FUNCTION: GOLDTL 0x429670
// SIZE: 326

/* Runs a script until it blocks, with the script pushed as the current one
 * for the duration. */
void __cdecl fcn_00429670(char* s)
{
	int saved;
	char* c;

	saved = -1;
	g_6791d0 = -1;
	if (g_6b7ec8 < 0x20) {
		g_14c9320[g_6b7ec8] = g_6b7e98;
		g_6b7ec8++;
	}
	g_6b7e98 = s;
	if (*(int*) (s + 0x104) == -1 || *(int*) (s + 0x104) == g_6791c8 || *(int*) (s + 0xc8c) != 0 || (s[0x124] & 2) || *(int*) (s + 0x118) == 0) {
		c = *(char**) (s + 0xc94);
		if (c != 0 && *(int*) (c + 0x30) != *(int*) (s + 0x104) && *(int*) (c + 0x2c) != *(int*) (s + 0x104)) {
			if (g_6b7ec8 > 0) {
				g_6b7e98 = g_14c9320[--g_6b7ec8];
				g_14c9320[g_6b7ec8] = 0;
			}
			return;
		}
		if (*(int*) (s + 0xc8c) != 0 || (s[0x124] & 2)) {
			saved = g_6b8010;
			fcn_004432d0(*(int*) (s + 0xc90), 1);
		}
		if (*(int*) (s + 0xc60) != 0) {
			fcn_00429490(s);
		}
		if (*(int*) (s + 0xc60) == 0) {
			do {
				fcn_004291c0(s);
			} while (*(int*) (s + 0xc84) == 2 && (s[0x124] & 1));
		}
		if (saved != -1) {
			fcn_004432d0(saved, 1);
		}
	}
	if (g_6b7ec8 > 0) {
		g_6b7e98 = g_14c9320[--g_6b7ec8];
		g_14c9320[g_6b7ec8] = 0;
	}
}
