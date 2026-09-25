// FUNCTION: GOLD 0x0055e450
// SIZE: 531
// FUNCTION: GOLDTL 0x566700
// SIZE: 531

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

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_0050f950(int, int);
void __cdecl fcn_004c6430(int, int, int);
void __cdecl fcn_004c6650(int);
void __cdecl fcn_004c4510(char*, int);
int __cdecl fcn_004c4700(unsigned char, unsigned char, short, void*);
void __cdecl fcn_004c53a0(void);
int __cdecl fcn_00500480(char*, int*, int*);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
void __cdecl fcn_004c54c0(int, int, int, int);
char* __cdecl fcn_005049a0(char*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, char*);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00566700(char* u)
{
	int v;
	int a;
	int b;
	char text[0x400];
	char* h;
	char* q;

	v = 0;
	switch (*(int*) (u + 0x70)) {
	case 0:
		h = fcn_00508e40(*(int*) (u + 0xac));
		if (h == 0 || *(char**) (h + 0x16c) == 0
		    || fcn_0050f950(*(unsigned short*) (*(char**) (h + 0x16c) + 0x27), *(unsigned short*) h) > -0x1a) {
			goto kill;
		}
		fcn_004c6430(*(int*) (h + 4), 0, 0);
		fcn_004c6650(*(int*) (h + 4));
		fcn_004c4510(h, *(int*) (h + 4));
		fcn_004c4700(4, 1, h - g_aed32c + 0x16c, &v);
		fcn_004c53a0();
		if (fcn_00500480(h, &a, &b) != 0) {
			if (b != -1) {
				fcn_004c5da0(*(int*) (h + 4), a, b, 0, 0, "Entlassen");
			} else {
				fcn_004c5da0(*(int*) (h + 4), a, -1, 0, 1, "Entlassen");
			}
		}
		v = -5;
		fcn_004c54c0(g_7f4ca0[*(unsigned short*) (*(char**) (h + 0x16c) + 0x27)].owner, *(int*) (h + 4), v, 1);
		q = fcn_005049a0(*(char**) (h + 0x16c));
		fcn_0051af00(text, 0x1bac, *(unsigned short*) h, *(char**) (h + 0x16c));
		if (q != 0) {
			h = *(char**) (h + 0x16c);
			fcn_00545e80(g_7f4ca0[*(unsigned short*) (h + 0x27)].owner, -1, text, 0, 0x5f2, *(int*) (h + 1), *(int*) (q + 2), 0,
			    "_NACHRICHTEN_HS_01");
		} else {
			fcn_00545d40(g_7f4ca0[*(unsigned short*) (*(char**) (h + 0x16c) + 0x27)].owner, -1, text, 0, 0x5f2, "_NACHRICHTEN_HS_01");
		}
		fcn_00546190(u);
		return;
	case -2:
	case -1:
kill:
		fcn_00546190(u);
		break;
	}
}
