struct rec_4cc590 {
	char pad0[2];
	char kind;
	char pad3;
	int id;
	char pad8[0x164];
	int owner;
	char pad170[0xac];
};
// SIZE 0x21c

extern char g_7f4ca0[];
extern int g_14cbca0;
extern int g_699364;
extern char g_68a9d0[];
extern int(__stdcall* g_662318)(void);

void __cdecl fcn_0042e4c0(int);
int __cdecl fcn_004c4dc0(unsigned char*, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned short __cdecl fcn_0050a7e0(int, int, int, int, int, int, int, int);
char* __cdecl gm_FindRecordById(int);
void __cdecl fcn_004fe470(int, int, int, int, int);
char* __cdecl fcn_00502fe0(int, int, int);
void __cdecl fcn_004ce9e0(struct rec_4cc590*);

// FUNCTION: GOLD 0x004cba10
// SIZE: 375
// FUNCTION: GOLDTL 0x4cc590
// SIZE: 375

int __cdecl fcn_004cc590(unsigned char* a1, char* a2)
{
	char* e;
	char* r;
	int id;

	if (g_14cbca0 != -1)
		g_699364 = *(int*) (a1 + 0x10);
	else
		*(int*) (a1 + 0x22) = g_662318();
	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 1;
		*(int*) (a2 + 6) = 0;
	}
	fcn_0042e4c0(*(int*) (a1 + 0x22));
	if (*(int*) (a1 + 0x17) == -1) {
		e = 0;
	} else {
		*(int*) (a1 + 0x17) = fcn_004c4dc0(a1, *(int*) (a1 + 0x17));
		e = gm_StartFilteredEntitySearch(1, 1, *(int*) (a1 + 0x17));
		if (e == 0)
			return 1;
	}
	id = fcn_0050a7e0(a1[0x14], -1, -1, 0x14, 0, a1[0x1f], a1[0x20], 0);
	if (id == 0xffff)
		return 1;
	if (*(int*) (a1 + 0x1b) != -1 && (r = gm_FindRecordById(*(int*) (a1 + 0x1b))) != 0)
		fcn_004fe470(((struct rec_4cc590*)g_7f4ca0)[id].id, *(int*) (e + 1), *(int*) (r + 2), 0, 0);
	else
		fcn_004fe470(((struct rec_4cc590*)g_7f4ca0)[id].id, *(int*) (e + 1), -1, 0, 0);
	((struct rec_4cc590*)g_7f4ca0)[id].owner = 0;
	((struct rec_4cc590*)g_7f4ca0)[id].kind = 0xd;
	if (a1[0x21] != 0) {
		fcn_00502fe0(((struct rec_4cc590*)g_7f4ca0)[id].id, a1[0x21], 1);
		fcn_004ce9e0(&((struct rec_4cc590*)g_7f4ca0)[id]);
	}
	(*(int*)g_68a9d0) = ((struct rec_4cc590*)g_7f4ca0)[id].id;
	if (a2 != 0) {
		a2[0] = 1;
		a2[1] = 1;
		*(struct rec_4cc590**) (a2 + 6) = &((struct rec_4cc590*)g_7f4ca0)[id];
	}
	return 0;
}
