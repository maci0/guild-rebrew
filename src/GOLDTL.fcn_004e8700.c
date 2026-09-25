// FUNCTION: GOLDTL 0x4e8700
// SIZE: 42

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

void __cdecl fcn_004e8700(int v)
{
	int i;

	for (i = 41; i != 0; i--) {
		if (g_9a9220[i].type == 0x26) {
			g_9a9220[i].x4 = v;
			return;
		}
	}
}
