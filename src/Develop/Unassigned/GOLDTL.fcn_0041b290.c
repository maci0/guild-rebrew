#include <string.h>

#include "g_6b5dd0.h"

extern DISPLAY_ADAPTER_INFO* g_6b5dd0;
extern unsigned int g_6b5de8;

int __cdecl io_OpenRegistryKey(const char* sub, int mode);
int __cdecl io_ReadRegistryString(int, const char*, char*);
char __cdecl fcn_0041b3a0(char*, unsigned long*);
char __cdecl fcn_0041b470(char*, int*);
void __cdecl fcn_00410430(int);


/* Reads the saved display adapter and mode from the registry; returns 1
 * when both are still available. */
/* ADDRESS: GOLDTL 0x0041b290 */
char __cdecl fcn_0041b290(unsigned int* adapter, int* mode)
{
	int h;
	unsigned int i;
	char found;
	unsigned long guid[4];
	char buf[0x100];

	*mode = 0;
	found = 0;
	*adapter = 0xffffffff;
	h = io_OpenRegistryKey("d8_vesa", 1);
	if (h != -1) {
		if (io_ReadRegistryString(h, "d8_Guid", buf) && fcn_0041b3a0(buf, guid)) {
			for (i = 0; i < g_6b5de8; i++) {
				if (memcmp(guid, g_6b5dd0[i].guid, sizeof(guid)) == 0) {
					*adapter = i;
					if (io_ReadRegistryString(h, "d8_Mode", buf) && fcn_0041b470(buf, mode)) {
						found = 1;
					}
				}
			}
		}
		fcn_00410430(h);
	}
	return found;
}
