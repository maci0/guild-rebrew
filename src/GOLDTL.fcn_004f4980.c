// FUNCTION: GOLD 0x004f2870
// SIZE: 83
// FUNCTION: GOLDTL 0x4f4980
// SIZE: 83

typedef struct
{
	char pad[0x1c];
	char kind;
	unsigned char sub;
	char tail[6];
} Rec24;
// SIZE 0x24

extern Rec24 g_68ff68[29];

int __cdecl fcn_004f4980(char* a1, int sub, Rec24* out)
{
	int i;

	for (i = 0; i < 29; i++) {
		if (a1[0x166] == g_68ff68[i].kind && sub == g_68ff68[i].sub) {
			*out = g_68ff68[i];
			return 1;
		}
	}
	return 0;
}
