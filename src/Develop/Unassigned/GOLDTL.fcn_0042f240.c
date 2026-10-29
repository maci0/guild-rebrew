#include <string.h>

/* ADDRESS: GOLDTL 0x0042f240 */
char* __cdecl fcn_0042f240(unsigned int* a0, char* a1, char* a2, char* a3)
{
	char buf[0x100];
	char* cur;
	char* next;

	if (a1 == 0) {
		return 0;
	}
	if (a1 == a2) {
		strcpy(a3, (char*) *a0);
		return a3;
	}
	strcpy(a3, a1);
	if (a0 != 0) {
		strcat(a3, (char*) *a0);
		if (*(char**) (a1 + 0x110) == 0) {
			return a3;
		}
		cur = *(char**) (a1 + 0x110);
		while (cur != a2) {
			strcpy(buf, cur);
			strcat(a3, buf);
			next = *(char**) (cur + 0x110);
			if (next == 0) {
				return a3;
			}
			cur = next;
		}
		return a3;
	}
	a3[strlen(a3) - 1] = '\0';
	if (*(char**) (a1 + 0x110) == 0) {
		return a3;
	}
	cur = *(char**) (a1 + 0x110);
	while (cur != a2) {
		strcpy(buf, cur);
		strcat(a3, buf);
		next = *(char**) (cur + 0x110);
		if (next == 0) {
			return a3;
		}
		cur = next;
	}
	return a3;
}
