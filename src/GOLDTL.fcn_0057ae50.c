// FUNCTION: GOLD 0x005729b0
// SIZE: 430
// FUNCTION: GOLDTL 0x57ae50
// SIZE: 430

/* 'sPgf': tag the effect object with its owner id */
#define FX_MAGIC 0x66675073

extern int g_6b8010;

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl fcn_00426cc0(int);
char* __cdecl fcn_00426fd0(const char* name);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00455350(char*, char*, float*);
void __cdecl fcn_00428340(char* o, int n, ...);
void __cdecl fcn_00428720(char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_0057ae50(char* u)
{
	float pos[4];
	char* q;
	char* e;
	char* o;
	int saved;

	q = fcn_005463a0(1, 1, *(int*) (u + 0xac));
	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0x10));
	if (e == 0 || *(char**) (e + 0x61) == 0 || q == 0 || *(int*) (q + 0x70) == -2 || *(int*) (q + 0x70) == -1) {
		o = fcn_00426cc0(*(int*) (u + 0xb0));
		if (o != 0 && *(int*) o == FX_MAGIC && *(int*) (o + 4) == *(int*) (u + 0x10)) {
			saved = g_6b8010;
			fcn_004432d0(0, 1);
			fcn_00428720(o);
			fcn_004432d0(saved, 1);
		}
		fcn_00546190(u);
		return;
	}
	if (*(int*) (u + 0xb0) != -1) {
		o = fcn_00426cc0(*(int*) (u + 0xb0));
		if (o != 0) {
			if (*(int*) o == FX_MAGIC && *(int*) (o + 4) == *(int*) (u + 0x10)) {
				return;
			}
			*(int*) (u + 0xb0) = -1;
		}
	}
	if (*(int*) (u + 0xb4) == 2) {
		o = fcn_00426fd0("LOCATIONS\\NEKROMANTENTURM\\NEBEL_DES_GRAUENS_GROSS.esc");
	} else if (*(int*) (u + 0xb4) == 1) {
		o = fcn_00426fd0("LOCATIONS\\NEKROMANTENTURM\\NEBEL_DES_GRAUENS_MITTEL.esc");
	} else {
		o = fcn_00426fd0("LOCATIONS\\NEKROMANTENTURM\\NEBEL_DES_GRAUENS_KLEIN.esc");
	}
	if (o == 0) {
		return;
	}
	*(int*) o = FX_MAGIC;
	*(int*) (o + 4) = *(int*) (u + 0x10);
	saved = g_6b8010;
	fcn_004432d0(0, 1);
	fcn_00455350(*(char**) (e + 0x61), *(char**) (e + 0x61) + 0x4c, pos);
	pos[1] += 500.0f;
	fcn_00428340(o, 3, (int) pos[0], (int) pos[1], (int) pos[2]);
	*(int*) (o + 0x104) = 0;
	fcn_004432d0(saved, 1);
	*(int*) (u + 0xb0) = *(int*) (o + 0x100);
}
