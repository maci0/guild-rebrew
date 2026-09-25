// FUNCTION: GOLD 0x004e86e0
// SIZE: 79
// FUNCTION: GOLDTL 0x4ea460
// SIZE: 79

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
extern Rec18 g_68da68[];

void* __cdecl fcn_00508e40(int);

int __cdecl fcn_004ea460(void)
{
	int n;
	int i;

	n = 7;
	for (i = 36; i != 0; i--) {
		if (n == 0) {
			break;
		}
		if (g_68da68[g_9a9220[i].type].x4 == 7) {
			if (g_9a9220[i].x4 != -1) {
				if (fcn_00508e40(g_9a9220[i].x4) != 0) {
					return 1;
				}
			} else {
				n--;
			}
		}
	}
	return 0;
}
