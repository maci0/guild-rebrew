extern int g_6b8010;

// SIZE 0x21c
struct s_7f4ca0 {
	char pad[2];
	char kind;
	char pad2[0x219];
};

extern char g_7f4ca0[];
extern char* g_773da8;

// FUNCTION: GOLD 0x005287b0
// SIZE: 142
// FUNCTION: GOLDTL 0x52de50
// SIZE: 142

void __cdecl fcn_004432d0(int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_AddObjekt(void);
void __cdecl fcn_0052dd80(char*);
void __cdecl fcn_0052d9d0(char*);

void __cdecl fcn_0052de50(void)
{
	int save;
	struct s_7f4ca0* r;
	char* e;

	save = g_6b8010;
	r = 0;
	fcn_004432d0(0, 1);
	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_AddObjekt()) {
		if (*(unsigned short*) (e + 0x27) != 0xffff) {
			r = &((struct s_7f4ca0*)g_7f4ca0)[*(unsigned short*) (e + 0x27)];
		}
		if (r != 0 && r != ((struct s_7f4ca0*)g_773da8) && (r->kind == 6 || r->kind == 7 || r->kind == 5) &&
		    (e[0x5a] & 1) == 0) {
			fcn_0052dd80(e);
			fcn_0052d9d0(e);
		}
	}
	fcn_004432d0(save, 1);
}
