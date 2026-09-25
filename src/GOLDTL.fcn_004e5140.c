// FUNCTION: GOLD 0x004e37a0
// SIZE: 94
// FUNCTION: GOLDTL 0x4e5140
// SIZE: 94

typedef struct
{
	int used;
	int x4;
	int x8;
	int xc;
	int x10;
	char name[0x348];
} Player35c;
// SIZE 0x35c

extern Player35c g_9b0e20[];
extern char g_68b300[];

void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00519190(char*);

void __cdecl fcn_004e5140(unsigned char* a1)
{
	int i;

	for (i = 0; i < a1[0x30]; i++) {
		if (g_9b0e20[i].xc == 0 && g_9b0e20[i].x8 != 0) {
			fcn_004727a0(*(int*) (a1 + 0x2c), 0);
			fcn_00519190(g_9b0e20[i].name);
			fcn_00519190(g_68b300);
			g_9b0e20[i].xc = 1;
		}
	}
}
