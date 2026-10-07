extern char* g_773da8;

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	struct pos14 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};

// SIZE 0x21c
struct s_7f4ca0 {
	int f0;
	int f4;
	char pad[0x214];
};

extern char g_7f4ca0[];

// FUNCTION: GOLDTL 0x547460

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_004c5530(struct msg*);

void __cdecl fcn_00547460(void)
{
	struct msg m;
	char* e;
	char* p;

	e = gm_StartFilteredEntitySearch(1, 5, 0xf);
	if (e != 0 && *(unsigned short*) (e + 0x27) != 0xffff) {
		for (p = fcn_005463a0(1, 0, 0x22); p != 0; p = fcn_005462a0()) {
			if (*(int*) (p + 0x10) == *(int*) (e + 1)) {
				return;
			}
		}
		m.b4 = 0x22;
		m.f8 = ((struct s_7f4ca0*)g_7f4ca0)[*(unsigned short*) (e + 0x27)].f4;
		m.fc = *(int*) (e + 1);
		m.b36 = 2;
		m.b58 = 1;
		fcn_004c5530(&m);
	}
}
