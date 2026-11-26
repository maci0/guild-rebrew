#include <string.h>

extern char* gm_CityEntity;

int __cdecl atoi(const char* s);
void __cdecl cm_SendCopyEntityData(char* msg);

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
		*(int*) (msg + 8) = *(int*) (gm_CityEntity + 4);
		msg[0x58] = (char) n;
		*(int*) (msg + 0xc) = -1;
		msg[0x36] = 0x12;
		msg[0x59] = c;
		cm_SendCopyEntityData(msg);
	}
	return 1;
}
