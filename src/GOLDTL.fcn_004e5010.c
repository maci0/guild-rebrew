// FUNCTION: GOLDTL 0x4e5010
// SIZE: 91

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

void* __cdecl fcn_00508e40(int);

int __cdecl fcn_004e5010(unsigned char* a1)
{
	int i;
	int r;

	r = 1;
	for (i = 0; i < a1[0x30]; i++) {
		if (((Player35c*)g_9b0e20)[i].used != 0 && ((Player35c*)g_9b0e20)[i].x10 != -1 && fcn_00508e40(((Player35c*)g_9b0e20)[i].x10) != 0 &&
		    ((Player35c*)g_9b0e20)[i].x4 == 0) {
			r = 0;
			break;
		}
	}
	return r;
}
