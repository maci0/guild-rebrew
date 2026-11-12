#include <string.h>

/* ADDRESS: GOLDTL 0x0042f240 */
char* __cdecl fcn_0042f240(unsigned int* a0, char* a1, char* a2, char* a3)
{
	char buf[0x100];
	char* cur;
	char** link;

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
		link = (char**) (a1 + 0x110);
		if (*link == 0) {
			return a3;
		}
		while ((cur = *link) != a2) {
			strcpy(buf, cur);
			strcat(buf, a3);
			strcpy(a3, buf);
			link = (char**) (cur + 0x110);
			if (*link == 0) {
				return a3;
			}
		}
		return a3;
	}
	a3[strlen(a3) - 1] = '\0';
	link = (char**) (a1 + 0x110);
	if (*link == 0) {
		return a3;
	}
	while ((cur = *link) != a2) {
		strcpy(buf, cur);
		strcat(buf, a3);
		strcpy(a3, buf);
		link = (char**) (cur + 0x110);
		if (*link == 0) {
			return a3;
		}
	}
	return a3;
}
