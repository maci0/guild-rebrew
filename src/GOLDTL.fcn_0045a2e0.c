// FUNCTION: GOLDTL 0x45a2e0

extern int* g_6b89e8;
extern int g_6b89c4[8];
extern char g_662dc8[15][9];

char* __cdecl fcn_0066080a(char*);
char* __cdecl fcn_0064d470(char*, char*);

int __cdecl fcn_0045a2e0(int x, int y, int* img)
{
	int off;
	int k;
	int i;

	off = (img[0] - 1 & y) * img[0] + (img[0] - 1 & x);
	if ((((unsigned char*) img[5])[off] & 0x80) != 0) {
		return 0;
	}
	if (g_6b89e8 != img) {
		for (k = 0; k < 8; k++) {
			g_6b89c4[k] = 1;
			if (((char*) img)[0x7e24 + k * 0x40] != 0) {
				for (i = 0; i < 15; i++) {
					if (fcn_0064d470(fcn_0066080a((char*) img + 0x7e24 + k * 0x40), g_662dc8[i]) != 0) {
						g_6b89c4[k] = i;
						break;
					}
				}
			}
		}
		g_6b89e8 = img;
	}
	return g_6b89c4[((unsigned char*) img[5])[off]];
}
