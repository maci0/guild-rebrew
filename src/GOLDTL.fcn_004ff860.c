// FUNCTION: GOLDTL 0x004ff860
// SIZE: 134
// FUNCTION: GOLD 0x004fd090
// SIZE: 144

typedef struct
{
	unsigned short id;
	unsigned char x2;
	char pad3;
	int x4;
	char pad8[0x54];
	int x5c;
	int x60;
	int x64;
	int x68[5];
	char pad7c[0x1a0];
} Ent21c;
// SIZE 0x21c

extern Ent21c g_7f4ca0[768];

int __cdecl fcn_004ff860(unsigned char* p)
{
	int id;
	int i;
	int j;
	int found;
	int cnt;

	if (p[2] == 6 || p[2] == 7) {
		return 0;
	}
	id = *(int*) (p + 4);
	for (i = 0; i < 768; i++) {
		found = 0;
		cnt = 0;
		if (g_7f4ca0[i].x4 != id && (g_7f4ca0[i].x2 == 6 || g_7f4ca0[i].x2 == 7)) {
			if (g_7f4ca0[i].x5c == id || g_7f4ca0[i].x60 == id || g_7f4ca0[i].x64 == id) {
				return 0;
			}
			for (j = 0; j < 5; j++) {
				if (g_7f4ca0[i].x68[j] == id) {
					found |= 1;
					cnt++;
				} else if (g_7f4ca0[i].x68[j] != -1) {
					cnt++;
				}
			}
			if (found && cnt < 5) {
				return 0;
			}
		}
	}
	return 1;
}
