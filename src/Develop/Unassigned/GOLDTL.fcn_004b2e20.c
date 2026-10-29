#include <stdio.h>
#include <string.h>

extern int g_1052de0;
extern char g_67fca0[];

void __cdecl fcn_0051af00(int, int, ...);

/* ADDRESS: GOLDTL 0x004b2e20 */
void __cdecl hst_ParseText_Real(int out, int src)
{
	char buf[0x17d0];
	char msg[0x100];
	char* open;
	char* hash;
	char* scan;
	char* p;
	int c;

	if (g_1052de0 == 0) {
		return;
	}
	memset(buf, 0, sizeof(buf));
	if (src < 0x4800) {
		p = *(char**) (src * 4 + 0x14a5320);
		if (p == 0) {
			return;
		}
		if (strlen(p) > 0x17c0) {
			return;
		}
		strncpy(buf, p, 0x17c0);
	} else {
		strcpy(buf, (char*) src);
	}
	open = 0;
	hash = 0;
	scan = buf;
	while (*scan) {
		c = *scan;
		if (c == '[') {
			if (open != 0) {
				sprintf(msg, (char*) 0x680b28, src - (int) g_67fca0);
				return;
			}
			open = scan;
			scan++;
		} else if (c == '#') {
			if (open == 0 || hash != 0) {
				sprintf(msg, (char*) 0x680b28, src - (int) g_67fca0);
				return;
			}
			hash = scan;
			scan++;
		} else if (c == ']') {
			if (open == 0 || hash == 0) {
				sprintf(msg, (char*) 0x680b28, src - (int) g_67fca0);
				return;
			}
			memmove(hash, scan + 1, strlen(scan + 1) + 1);
			memmove(open, open + 1, strlen(open + 1) + 1);
			scan = hash - 1;
			hash = 0;
			open = 0;
		} else {
			scan++;
		}
	}
	if (open != 0) {
		return;
	}
	if (hash != 0) {
		return;
	}
	fcn_0051af00(out, 0x679060, buf);
}
