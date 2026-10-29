#include <stdio.h>
#include <string.h>

extern int g_67ac90;

int __cdecl fcn_00449ac0(char*, char*);

/* ADDRESS: GOLDTL 0x00449db0 */
char __cdecl fcn_00449db0(char* a, int b, int mode, char* key, char* val)
{
	int i;

	if (mode < 0) {
		if ((*(unsigned char*) &g_67ac90 & 0x80) != 0) {
			strcpy(key, a);
			strcat(key, "_s");
			if (b != 0 && val != 0) {
				strcpy(val, (char*) b);
				strcat(val, "_s");
			}
			return 1;
		}
		return 0;
	}
	if (mode == 0) {
		if ((g_67ac90 & 0x7f) == 2) {
			i = 2;
			do {
				if (i > 0) {
					sprintf(key, (char*) 0x67adf0, a, i - 1);
					if (b != 0 && val != 0) {
						sprintf(val, (char*) 0x67adf0, (char*) b, i - 1);
					}
				} else {
					strcpy(key, a);
					if (b != 0 && val != 0) {
						strcpy(val, (char*) b);
					}
				}
				if (fcn_00449ac0(key, (char*) 0x67ade8)) {
					return 1;
				}
			} while (--i >= 0);
			return 0;
		}
		strcpy(key, a);
		if (b != 0 && val != 0) {
			strcpy(val, (char*) b);
		}
	} else {
		if ((g_67ac90 & 0x7f) == 2) {
			i = 2 - mode;
		} else {
			i = mode;
		}
		sprintf(key, (char*) 0x67adf0, a, i - 1);
		if (b != 0 && val != 0) {
			sprintf(val, (char*) 0x67adf0, (char*) b, i - 1);
		}
	}
	return 1;
}
