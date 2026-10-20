#include <string.h>

extern float g_66291c;

float __cdecl fcn_0050f980(unsigned short, unsigned short, int);
void __cdecl fcn_005ca560(void*);
int __cdecl fcn_005cf720(int, int, int, int);

/* ADDRESS: GOLDTL 0x005cb670 */
int __cdecl fcn_005cb670(char* a0, int n, char* a2, int a3)
{
	char* h;
	int count;
	int i;
	int t;
	float d;

	count = 0;
	if (n == 0) {
		h = (char*) 0x7f4ca0;
		while ((int) h < 0x85a0a0) {
			if (h != a0 && *(unsigned short*) h != 0xffff
			    && *(unsigned char*) (h + 2) >= 2 && *(unsigned char*) (h + 2) <= 7) {
				d = fcn_0050f980(*(unsigned short*) a0, *(unsigned short*) h, 1);
				if (g_66291c <= d && *(int*) (h + 0x210) != *(int*) (a0 + 4)) {
					count++;
				}
			}
			h += 0x21c;
		}
		return count;
	}
	memset(a2, 0, n * 0x38);
	h = (char*) 0x7f4ca0;
	while ((int) h < 0x85a0a0) {
		if (h != a0 && *(unsigned short*) h != 0xffff
		    && *(unsigned char*) (h + 2) >= 2 && *(unsigned char*) (h + 2) <= 7) {
			d = fcn_0050f980(*(unsigned short*) a0, *(unsigned short*) h, 1);
			if (g_66291c <= d && *(int*) (h + 0x210) != *(int*) (a0 + 4)) {
				if (*(int*) (a2 + n * 0x38 - 0xc) < (int) d) {
					*(int*) (a2 + n * 0x38 - 0x38) = (int) h;
					*(int*) (a2 + n * 0x38 - 0xc) = (int) d;
					count++;
					for (i = n - 1; i > 0; i--) {
						if (*(int*) (a2 + (i - 1) * 0x38 + 0x2c) < *(int*) (a2 + i * 0x38 + 0x2c)) {
							t = *(int*) (a2 + (i - 1) * 0x38);
							*(int*) (a2 + (i - 1) * 0x38) = *(int*) (a2 + i * 0x38);
							*(int*) (a2 + i * 0x38) = t;
							d = (float) *(int*) (a2 + (i - 1) * 0x38 + 0x2c);
							*(int*) (a2 + (i - 1) * 0x38 + 0x2c) = *(int*) (a2 + i * 0x38 + 0x2c);
							*(int*) (a2 + i * 0x38 + 0x2c) = (int) d;
						}
					}
				}
			}
		}
		h += 0x21c;
	}
	if (n < count) {
		count = n;
	}
	for (i = 0; i < count; i++) {
		fcn_005ca560(a2 + i * 0x38);
		*(int*) (a2 + i * 0x38 + 0x30) = fcn_005cf720(*(unsigned short*) a0,
			*(unsigned short*) *(int*) (a2 + i * 0x38), a3, 0);
	}
	return count;
}
