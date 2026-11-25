#include <string.h>

/* ADDRESS: GOLDTL 0x0042f240 */
char* __cdecl fcn_0042f240(unsigned int* a0, char* a1, char* a2, char* out)
{
	char buf[0x100];
	char* cur;
	char** link;

	if (a1 == 0) {
		return 0;
	}
	if (a1 != a2) {
		strcpy(out, a1);
		if (a0 != 0) {
			strcat(out, (char*) *a0);
			link = (char**) (a1 + 0x110);
			if (*link == 0)
				goto done;
			do {
				cur = *link;
				if (cur == a2)
					goto done;
				strcpy(buf, cur);
				strcat(buf, out);
				strcpy(out, buf);
				link = (char**) (cur + 0x110);
			} while (*link != 0);
			return out;
		} else {
			out[strlen(out) - 1] = '\0';
			link = (char**) (a1 + 0x110);
			if (*link == 0)
				goto done;
			do {
				cur = *link;
				if (cur == a2)
					goto done;
				strcpy(buf, cur);
				strcat(buf, out);
				strcpy(out, buf);
				link = (char**) (cur + 0x110);
			} while (*link != 0);
			return out;
		}
	}
	strcpy(out, (char*) *a0);
done:
	return out;
}
