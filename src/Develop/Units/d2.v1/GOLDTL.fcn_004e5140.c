


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

extern char g_9b0e20[];
extern char g_68b300[];

void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00519190(char*);

void __cdecl fcn_004e5140(unsigned char* a1)
{
	int i;

	for (i = 0; i < a1[0x30]; i++) {
		if (((Player35c*)g_9b0e20)[i].xc == 0 && ((Player35c*)g_9b0e20)[i].x8 != 0) {
			d2_SetForm(*(int*) (a1 + 0x2c), 0);
			fcn_00519190(((Player35c*)g_9b0e20)[i].name);
			fcn_00519190(g_68b300);
			((Player35c*)g_9b0e20)[i].xc = 1;
		}
	}
}
