// FUNCTION: GOLDTL 0x548f00
// SIZE: 407

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

extern struct house g_7f4ca0[];
extern char* g_aed32c;
extern char g_6a58c0[];
extern char g_6b5c60[];

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AddObjekt(void);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);

void __cdecl fcn_00548f00(void)
{
	short zero2;
	int zero4;
	char* e;
	unsigned char t;
	unsigned short house;

	e = gm_StartFilteredEntitySearch(1, 5, 0x16);
	while (e != 0) {
		house = *(unsigned short*) (e + 0x27);
		if (house != 0xffff && (e[0x5a] & 1) == 0) {
			zero4 = 0;
			zero2 = 0;
			t = g_7f4ca0[house].type;
			if ((t == 6 || t == 7) && *(short*) (e + 0x69) > 0) {
				if ((double) *(short*) (e + 0x6b) / *(short*) (e + 0x69) < 0.5) {
					char text[0x200];

					fcn_0051af00(text, 0x18a1, e, *(short*) (e + 0x69), *(int*) (e + 0x65));
					fcn_00545e80(g_7f4ca0[*(unsigned short*) (e + 0x27)].owner, -1, text, 0, 0x5fc, *(int*) (e + 1), -1, 0, g_6a58c0);
				} else {
					char text2[0x200];

					fcn_0051af00(text2, 0x18a2, e, *(short*) (e + 0x69), *(int*) (e + 0x65));
					fcn_00545e80(g_7f4ca0[*(unsigned short*) (e + 0x27)].owner, -1, text2, 0, 0x5fc, *(int*) (e + 1), -1, 0, g_6b5c60);
				}
			}
			fcn_004c4510(e, *(int*) (e + 1));
			fcn_004c4570(4, 1, e - g_aed32c + 0x6d, e + 0x65);
			fcn_004c4570(4, 1, e - g_aed32c + 0x65, &zero4);
			fcn_004c4570(2, 1, e - g_aed32c + 0x6b, &zero2);
			fcn_004c4570(2, 1, e - g_aed32c + 0x69, &zero2);
			fcn_004c5360();
		}
		e = gm_AddObjekt();
	}
}
