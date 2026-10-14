extern unsigned char* g_868050;




#include <string.h>

int __cdecl fcn_00511040(int idx, char* out)
{
	unsigned char* t;

	t = g_868050 + idx * 0x24d;
	if (*t == 0x1d) {
		strcpy(out, "FRIEDHOF");
		return 1;
	}
	if (*t == 0x1f) {
		strcpy(out, "ZIGEUNERLAGER");
		return 1;
	}
	strcpy(out, (char*) t + 1);
	return 1;
}
