// FUNCTION: GOLD 0x0055d610
// FUNCTION: GOLDTL 0x565880

// SIZE 0x2f4
struct player {
	char name[0x54];
	unsigned short id;
	char pad56[0x29e];
};

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

extern char g_7f4ca0[];
extern char g_868060[];
extern unsigned char g_773d75;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00565880(char* u)
{
	char text[0x400];
	char* e;

	switch (*(int*) (u + 0x70)) {
	case 0:
		e = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0xac));
		if (e != 0) {
			fcn_0051af00(text, 0x190b, ((struct player*)g_868060)[*(unsigned char*) (u + 0xb0)].name, *(int*) (u + 0xb4));
			fcn_00545d40(((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].owner, -1, text, 0, 0x5ff, 0);
			fcn_004c51f0(*(int*) (e + 1), -1, ((struct player*)g_868060)[*(unsigned char*) (u + 0xb0)].id, *(int*) (u + 0xb4), g_773d75, 0);
		}
		fcn_00546190(u);
		return;
	case -2:
	case -1:
		fcn_00546190(u);
		break;
	}
}
