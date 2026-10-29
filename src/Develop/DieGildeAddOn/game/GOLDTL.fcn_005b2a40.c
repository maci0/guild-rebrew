#include <string.h>

extern char* g_14b5a08;
extern char* g_14b5a14;
extern char* g_14b5a18;

void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

/* ADDRESS: GOLDTL 0x005b2a40 */
void __cdecl fcn_005b2a40(unsigned short* a0, int n, char** arr)
{
	char buf[0x80];
	char* e;
	int i;
	int found;
	int limit;

	if (n < 1 || n >= 4) {
		return;
	}
	fcn_0051af00((void*) 0x774a80, 0x41bf, *a0);
	for (i = 0; i < n; i++) {
		e = arr[i];
		if (e[2] == 6 || e[2] == 7) {
			fcn_00545d40(*(int*) (e + 4), -1, (void*) 0x774a80, 1, 0x5fb, (void*) 0x6ab480);
		}
	}
	strcpy((char*) 0x774a80, g_14b5a08);
	if (n > 1) {
		limit = n - 1;
		for (i = 0; i < 4; i++) {
			if (i >= limit) {
				break;
			}
			fcn_0051af00(buf, 0x41bb, *(unsigned short*) arr[i]);
			strcat((char*) 0x774a80, buf);
		}
		found = 0;
		for (; i < 4; i++) {
			if (found) {
				break;
			}
			fcn_0051af00(buf, 0x41bc, *(unsigned short*) arr[i]);
			strcat((char*) 0x774a80, buf);
			found = 1;
		}
		strcat((char*) 0x774a80, g_14b5a18);
	}
	else {
		for (i = 0; i < 4; i++) {
			if (i >= 1) {
				break;
			}
			fcn_0051af00(buf, 0x41bb, *(unsigned short*) arr[i]);
			strcat((char*) 0x774a80, buf);
		}
		strcat((char*) 0x774a80, g_14b5a14);
	}
	fcn_00545d40(*(int*) (a0 + 2), -1, (void*) 0x774a80, 1, 0x5fb, (void*) 0x6ab464);
}
