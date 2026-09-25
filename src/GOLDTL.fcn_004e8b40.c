// FUNCTION: GOLDTL 0x4e8b40
// SIZE: 52
// FUNCTION: GOLD 0x004e6f80
// SIZE: 64

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

extern Rec18 g_68da68[];

int __cdecl fcn_004e8b40(int idx, Rec18* out)
{
	if (idx >= 0x28) {
		*out = g_68da68[0];
		return 0;
	}
	*out = g_68da68[idx];
	return 1;
}
