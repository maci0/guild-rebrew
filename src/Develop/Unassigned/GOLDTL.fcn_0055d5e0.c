#include <string.h>
char __cdecl fcn_0055d5e0(char* name, int* list)
{
	if (strstr(name, "dummy_TRANSPORTER")) {
		list[list[0x20]] = (int) name;
		list[0x20]++;
	}
	return list[0x20] < 0x20;
}
