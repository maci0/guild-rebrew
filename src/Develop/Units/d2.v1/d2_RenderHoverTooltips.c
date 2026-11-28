
extern volatile int gm_GameTicks;
extern int d3_ActiveScene;
extern int d2_ScreenSurface;
extern char* txt_TextEntries[];

// SIZE 0x10c
struct s_7e6060 {
	int a;
	int t;
	char* o;
	char name[0x100];
};

extern struct s_7e6060 g_7e6060[64];

void __cdecl d2_SelectFont(int);
char __cdecl d3_GetObjectScreenRect(void*, int*);
void __cdecl d2_DrawWordWrappedText(int, int, int, int, int, char*, int);

/* ADDRESS: GOLDTL 0x00532650 */
void __cdecl d2_RenderHoverTooltips(void)
{
	char** q;
	char** s;
	char* e;
	char* m;
	char* name;
	int r[4];
	int x, y;

	for (q = &g_7e6060[0].o; (int) q < (int) &g_7e6060[64].o;
		q = (char**) ((char*) q + sizeof(struct s_7e6060))) {
		if (*q != 0
			&& (unsigned int) gm_GameTicks > (unsigned int) (((int*) q)[-1] + 0x12c)) {
			*q = 0;
		}
	}
	d2_SelectFont(0x54);
	for (s = &g_7e6060[0].o; (int) s < (int) &g_7e6060[64].o;
		s = (char**) ((char*) s + sizeof(struct s_7e6060))) {
		e = *s;
		if (e == 0) {
			continue;
		}
		m = *(char**) (e + 0x34);
		if (*(int*) (m + 0x20c) != d3_ActiveScene) {
			continue;
		}
		if (*(int*) (m + 0x218) != 1) {
			if (!d3_GetObjectScreenRect(m, r)) { continue; }
		} else {
			m = *(char**) (e + 0x22c);
			if (m == 0) {
				continue;
			}
			if (*(int*) (m + 0x218) == 1) {
				continue;
			}
			if (!d3_GetObjectScreenRect(m, r)) { continue; }
		}
		y = r[1] - 0x40;
		x = (r[2] - r[0]) / 2 + r[0] - 0x50;
		if (((char*) s)[4] != 0) {
			name = (char*) s + 4;
		} else {
			name = txt_TextEntries[((int*) s)[-2]];
		}
		d2_DrawWordWrappedText(x, y, 0xa0, 0x60,
			d2_ScreenSurface, name, 0x28);
	}
}
