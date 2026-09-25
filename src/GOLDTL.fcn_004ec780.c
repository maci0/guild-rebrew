// FUNCTION: GOLD 0x004eaa00
// SIZE: 65
// FUNCTION: GOLDTL 0x4ec780
// SIZE: 65

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

void __cdecl fcn_004e8240(unsigned char, int, int, int, int);

void __cdecl fcn_004ec780(int type)
{
	int i;

	for (i = 0; i < 30; i++) {
		if (g_9a9220[i].id == type) {
			fcn_004e8240(g_9a9220[i].id, 0, 0, 3, 0xff);
			return;
		}
	}
}
