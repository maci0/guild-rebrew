// FUNCTION: GOLDTL 0x5016c0
// SIZE: 46

typedef struct
{
	char used;
	char pad[0x2f3];
} Rec2f4;
// SIZE 0x2f4

extern Rec2f4 g_868060[4];
extern char g_7f4c00[];

void __cdecl fcn_005020e0(int, char*);

void __cdecl fcn_005016c0(void)
{
	int i;

	for (i = 0; i < 4; i++) {
		if (g_868060[i].used == 0) {
			break;
		}
		fcn_005020e0(i, g_7f4c00);
	}
}
