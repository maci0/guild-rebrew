extern int g_6b8010;
extern char* g_7e2aa0;
extern int g_773dd8;
extern char g_7f4ca0[];

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_00530510(void);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
char* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl fcn_00506300(char*);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_004550b0(int, int);
void __cdecl fcn_00442be0(int);
int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(int);
void __cdecl fcn_00504130(char*);

/* ADDRESS: GOLD 0x004cb100 */
/* ADDRESS: GOLDTL 0x004cbc90 */

int __cdecl fcn_004cbc90(char* a1, char* a2)
{
	int saved;
	char* e;
	char* q;
	int r;
	int i;

	saved = g_6b8010;
	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (a1 + 0x10));
	if (e == 0)
		return 1;
	if (e == g_7e2aa0)
		fcn_00530510();
	for (q = fcn_00502cd0(0, 2, 7, 4, 0x1d); q != 0; q = gm_NextEntityQueryMatch()) {
		if (*(int*) (q + 0x1c) == *(int*) (e + 1))
			fcn_00506300(q);
	}
	for (i = 0; i < 768; i++) {
		if (*(char**) (g_7f4ca0 + i * 540 + 0x16c) == e)
			*(char**) (g_7f4ca0 + i * 540 + 0x16c) = 0;
	}
	fcn_004432d0(0, 1);
	if (g_773dd8 != 0)
		fcn_004550b0(*(int*) (e + 0x61), g_773dd8);
	fcn_00442be0(*(int*) (e + 0x61));
	if (*(int*) (e + 0x95) != -1) {
		r = fcn_00426cc0(*(int*) (e + 0x95));
		if (r != 0)
			fcn_00428720(r);
		*(int*) (e + 0x95) = -1;
	}
	fcn_004432d0(saved, 1);
	fcn_00504130(e);
	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	return 0;
}
