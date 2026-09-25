// FUNCTION: GOLDTL 0x5703b0
// SIZE: 416

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3[0x219];
};

extern struct pos14 g_7f4c00;
extern unsigned short g_7f4c04;
extern struct house g_7f4ca0[];
extern int g_7747f0;
extern char g_774964;
extern char* g_773d78;
extern char g_6b5c60[];

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
unsigned short __cdecl fcn_0042e410(int);
char* __cdecl fcn_005049a0(char*);
char* __cdecl gm_SetupEntityQuery(char*);
void __cdecl fcn_00526920(char*, int, char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_005703b0(char* u)
{
	char* list[0x40];
	int n;
	char* e;
	char* p;

	n = 0;
	if (g_7747f0 == 0) {
		*(int*) (u + 0x70) = -1;
	}
	switch (*(int*) (u + 0x70)) {
	case 0:
		if (g_774964 != 0) {
			g_7f4ca0[*(unsigned short*) (u + 8)].type = 5;
			(*(int*) (u + 0x70))++;
		}
		break;
	case 1:
		if (g_7f4c04 >= 0x16) {
			(*(int*) (u + 0x70))++;
			break;
		}
		for (e = gm_StartFilteredEntitySearch(1, 4, *(unsigned short*) (u + 8)); e != 0 && n < 0x40; e = gm_AddObjekt()) {
			list[n++] = e;
		}
		list[n++] = g_773d78;
		if (n != 0) {
			p = list[fcn_0042e410(n)];
			if (fcn_0042e410(4) != 0 && p != g_773d78 && ((e = fcn_005049a0(p)) != 0 || (e = gm_SetupEntityQuery(p)) != 0)) {
				fcn_00526920(p, *(int*) (e + 2), g_6b5c60);
			} else {
				fcn_00526920(p, -1, g_6b5c60);
			}
		}
		*(struct pos14*) (u + 0x52) = g_7f4c00;
		*(short*) (u + 0x56) += fcn_0042e410(2);
		*(int*) (u + 0x58) = fcn_0042e410(0x3c);
		break;
	case 2:
		g_7f4ca0[*(unsigned short*) (u + 8)].type = 6;
	case -2:
	case -1:
		fcn_00546190(u);
		break;
	}
}
