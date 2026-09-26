// FUNCTION: GOLDTL 0x551050
// SIZE: 259

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

extern char g_7f4ca0[];

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, unsigned short);
unsigned char* __cdecl gm_AddObjekt(void);
int __cdecl fcn_00504bd0(int);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_0050ff70(unsigned char*, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00551050(char* u)
{
	unsigned char* cand[16];
	char text[0x418];
	unsigned char* e;
	int n;

	n = 0;
	if (*(int*) (u + 0x70) != -2) {
		if (*(int*) (u + 0x70) != 0) {
			return;
		}
		for (e = gm_StartFilteredEntitySearch(1, 4, *(unsigned short*) (u + 8)); e != 0 && n < 16; e = gm_AddObjekt()) {
			if (fcn_00504bd0(*e) == 6) {
				cand[n++] = e;
			}
		}
		if (n != 0) {
			e = cand[fcn_0042e410(n)];
			if (e != 0) {
				fcn_0050ff70(e, -0x32);
			}
			if (((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].type == 6) {
				fcn_0051af00(text, 0x10b8, e);
				fcn_00545e80(((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].owner, ((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].owner, text, 0,
				    0x5ec, *(int*) (e + 1), -1, 0, 0);
			}
		}
	}
	fcn_00546190(u);
}
