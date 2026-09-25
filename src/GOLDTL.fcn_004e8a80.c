// FUNCTION: GOLDTL 0x4e8a80
// SIZE: 74

typedef struct
{
	unsigned char id;
	char pad1[3];
	int x4;
	unsigned char type;
	char pad9[3];
	int xc;
	unsigned char x10;
	char pad11[7];
} Rec18;
// SIZE 0x18

extern Rec18 g_9a9220[42];

int __cdecl fcn_004e8a80(int type, Rec18* out)
{
	int i;

	for (i = 0; i < 42; i++) {
		if (g_9a9220[i].type == type) {
			break;
		}
	}
	if (i >= 42) {
		return 0;
	}
	*out = g_9a9220[i];
	return 1;
}
