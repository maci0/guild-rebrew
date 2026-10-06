// FUNCTION: GOLD 0x4e3750
// FUNCTION: GOLDTL 0x4e4fc0

typedef struct
{
	int used;
	int x4;
	int x8;
	int xc;
	int x10;
	char tail[0x348];
} Player35c;
// SIZE 0x35c

extern char g_9b0e20[];

int __cdecl fcn_004e4fc0(unsigned char* a1)
{
	int i;
	int r;

	r = 1;
	for (i = 0; i < a1[0x30]; i++) {
		if (((Player35c*)g_9b0e20)[i].used != 0 && ((Player35c*)g_9b0e20)[i].x8 == 0 && ((Player35c*)g_9b0e20)[i].x10 != -1) {
			r = 0;
			break;
		}
	}
	return r;
}
