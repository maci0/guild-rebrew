// FUNCTION: GOLDTL 0x4d34b0
// SIZE: 50

extern int g_772f10;
extern char g_68b82c[];

int __cdecl fcn_0065f220(char*, char*);

char __cdecl fcn_004d34b0(char* s, char** arr)
{
	if (fcn_0065f220(s, g_68b82c) == 0) {
		arr[g_772f10] = s;
		g_772f10++;
	}
	return 1;
}
