// FUNCTION: GOLDTL 0x4e82d0
// SIZE: 133

typedef struct {
	unsigned char c0;
	char pad1[3];
	int id;
	unsigned char kind;
	char pad9[7];
	unsigned char f10;
	char pad11[3];
	int f14;
} rec18;
// SIZE 0x18

extern rec18 g_9a9220[];

char* __cdecl fcn_00508e40(int);

int __cdecl fcn_004e82d0(unsigned char* m)
{
	int i;

	if (m[6] == 0xff)
		return 1;
	for (i = 0; i < 42; i++) {
		if (g_9a9220[i].c0 == m[0])
			break;
	}
	if (i >= 42)
		return 0;
	if (g_9a9220[i].f10 != 1)
		return 0;
	if (g_9a9220[i].f14 != -1)
		return 0;
	if (*(int*) (m + 7) != -1 && fcn_00508e40(*(int*) (m + 7)) == 0)
		return 0;
	if (*(int*) (m + 1) != -1 && fcn_00508e40(*(int*) (m + 1)) == 0)
		return 0;
	return 1;
}
