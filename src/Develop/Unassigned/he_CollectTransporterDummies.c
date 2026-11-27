#include <string.h>
char __cdecl he_CollectTransporterDummies(char* name, int* list)
{
	if (strstr(name, "dummy_TRANSPORTER")) {
		list[list[0x20]] = (int) name;
		list[0x20]++;
	}
	return list[0x20] < 0x20;
}
