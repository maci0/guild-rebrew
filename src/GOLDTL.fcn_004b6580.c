// FUNCTION: GOLDTL 0x4b6580
// SIZE: 197

typedef struct {
	int f0;
	int f4;
	char st[0xe];
	char pad16[2];
	int f18;
	int f1c;
	char f20;
	char pad21[3];
} rec24;
// SIZE 0x24

extern char g_6a3440;
extern rec24 g_10069a0[128];

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);

int __cdecl fcn_004b6580(void* stream)
{
	int i;

	if (stream == 0)
		return 0;
	if (!ls_ReadVfsDataChecked(&g_6a3440, 1, 1, stream))
		return 0;
	for (i = 0; i < 128; i++) {
		if (!ls_ReadVfsDataChecked(&g_10069a0[i].f0, 4, 1, stream))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_10069a0[i].f4, 4, 1, stream))
			return 0;
		if (!ls_ReadVfsDataChecked(g_10069a0[i].st, 0xe, 1, stream))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_10069a0[i].f18, 4, 1, stream))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_10069a0[i].f1c, 4, 1, stream))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_10069a0[i].f20, 1, 1, stream))
			return 0;
	}
	return 1;
}
