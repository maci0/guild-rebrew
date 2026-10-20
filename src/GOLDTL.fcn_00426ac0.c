#include <string.h>

extern char g_6792a8[];

void* __cdecl fcn_0064d740(void* dst, const void* src, unsigned int n);

/* ADDRESS: GOLDTL 0x00426ac0 */
int __cdecl fcn_00426ac0(char* src, char* dst, int* lines)
{
	char* q;
	int i;
	int j;
	int n;
	int run;
	int k;

	n = 0;
	strcpy(dst, src);
	if (lines != 0) {
		*lines = 0;
	}
	for (i = 0; i < strlen(dst); i++) {
		switch (dst[i]) {
		case 9:
			dst[i] = ' ';
			break;
		case 10:
		case 13:
		case 16:
			if (lines != 0 && dst[i] == '\n') {
				n++;
				lines[n] = i + 1;
			}
			dst[i] = ' ';
			break;
		case '/':
			if (dst[i + 1] == '*') {
				q = strstr(dst + i + 1, g_6792a8);
				if (q != 0) {
					memset(dst + i, ' ', q - (dst + i) + 2);
				}
			}
			break;
		}
	}
	for (i = 0; i < strlen(dst); i++) {
		if (dst[i] == ' ' && dst[i + 1] == ' ') {
			run = 1;
			while (dst[i + run] == ' ') {
				run++;
			}
			if (lines != 0 && run > 1) {
				fcn_0064d740(dst + i + 1, dst + i + run, strlen(dst + i + run) + 1);
				for (j = 0; j < n; j++) {
					k = lines[j];
					if (k >= i) {
						k = k - run + 1;
						if (k < i) {
							k = i;
						}
						lines[j] = k;
						if (lines[j] < 0) {
							lines[j] = 0;
						}
					}
				}
			}
		}
	}
	lines[n] = -1;
	return strlen(dst);
}
