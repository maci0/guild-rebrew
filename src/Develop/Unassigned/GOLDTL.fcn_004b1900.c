#include <string.h>

extern char* g_773da8;

int __cdecl atoi(const char* s);
void __cdecl fcn_004c5530(char* msg);

/* ADDRESS: GOLDTL 0x004b1900 */
int __cdecl fcn_004b1900(int a1, int a2, char* s)
{
	char msg[0xf8];
	char c;
	int n;

	if (s[0] != '-') {
		return 0;
	}
	if (strlen(s + 1) < 2) {
		return 0;
	}
	c = s[1];
	if (c != 'N' && c != 'S' && c != 'O' && c != 'W' && c != 'A') {
		return 0;
	}
	n = atoi(s + 1);
	if (n > 0) {
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x51;
		*(int*) (msg + 8) = *(int*) (g_773da8 + 4);
		msg[0x58] = (char) n;
		*(int*) (msg + 0xc) = -1;
		msg[0x36] = 0x12;
		msg[0x59] = c;
		fcn_004c5530(msg);
	}
	return 1;
}
