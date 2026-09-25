// FUNCTION: GOLD 0x4b48f0
// SIZE: 112
// FUNCTION: GOLDTL 0x4b4a60
// SIZE: 111

extern char g_7f4ca4[];
extern float g_662cf8;

int __cdecl fcn_004b4a60(char* a1, char* a2)
{
	int total;
	int match;
	int i;

	total = 0;
	match = 0;
	for (i = 0; i < 0x300; i++) {
		if ((unsigned char) g_7f4ca4[i * 0x21c - 2] < 10) {
			total++;
			if (g_7f4ca4[i * 0x21c + 8] == a1[0xc])
				match++;
		}
	}
	if ((float) match / total * g_662cf8 >= *(int*) (a2 + 0x14))
		return 1;
	return 0;
}
