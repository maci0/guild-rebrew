extern int g_6b8010;
extern int g_67a370;

// SIZE 0x21c
struct s_7f4ca0 {
	char pad[2];
	char kind;
	char pad2[0x51];
	int res;
	char pad3[0x1c4];
};

extern char g_7f4ca0[];

// FUNCTION: GOLD 0x005283d0
// SIZE: 243
// FUNCTION: GOLDTL 0x52da70
// SIZE: 243

void __cdecl fcn_004432d0(int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl fcn_00502cd0(int, int, int, int, int, int, int);
char* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl fcn_004379a0(int, char*, int, void*, char*);
char __cdecl fcn_0052d970(char*, char*);
int __cdecl fcn_00413190(int);
void __cdecl fcn_00442a30(char*, int, int, int);

void __cdecl fcn_0052da70(int idx)
{
	int save;
	struct s_7f4ca0* r;
	char* e;
	char* d;
	int n;

	save = g_6b8010;
	r = &((struct s_7f4ca0*)g_7f4ca0)[idx];
	fcn_004432d0(0, 1);
	for (e = gm_StartFilteredEntitySearch(1, 4, idx); e != 0; e = gm_AddObjekt()) {
		if (*(char**) (e + 0x61) != 0) {
			fcn_004379a0(g_67a370, *(char**) (e + 0x61), 0x340, (void*) fcn_0052d970, e);
		}
	}
	for (e = fcn_00502cd0(0, 3, 7, 3, idx, 4, 0x1d); e != 0; e = gm_NextEntityQueryMatch()) {
		d = *(char**) (e + 0x3b);
		if (d != 0) {
			fcn_004432d0(fcn_00413190(*(int*) (d + 0x88)), 1);
			if (r != 0 && r->res != 0 && (r->kind == 5 || r->kind == 6 || r->kind == 7)) {
				n = r->res - 0x599;
				if (n != 0) {
					fcn_00442a30(**(char***) (d + 0x124),
					             *(int*) (**(char***) (d + 0x124) + 0x1cc), n, 1);
				}
			}
		}
	}
	fcn_004432d0(save, 1);
}
