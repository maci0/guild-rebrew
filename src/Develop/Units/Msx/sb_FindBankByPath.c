#include <string.h>
extern int* g_6b7d78;



int* __cdecl sb_FindBankByPath(int needle)
{
	int* node;

	node = g_6b7d78;
	while (node != 0) {
		if (strstr((char*) node + 0x32, (char*) needle) != 0) {
			break;
		}
		node = (int*) node[0x13c / 4];
	}
	return node;
}
