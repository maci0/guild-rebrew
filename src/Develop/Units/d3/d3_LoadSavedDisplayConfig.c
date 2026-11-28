#include <string.h>

#include "Develop/Units/d3/display_adapter_info.h"

extern DISPLAY_ADAPTER_INFO* g_6b5dd0;
extern unsigned int g_6b5de8;

int __cdecl io_OpenRegistryKey(const char* sub, int mode);
int __cdecl io_ReadRegistryString(int, const char*, char*);
char __cdecl d3_ParseGuid(char*, unsigned long*);
char __cdecl d3_ParseDisplayMode(char*, int*);
void __cdecl io_CloseRegistryKey(int);


/* Reads the saved display adapter and mode from the registry; returns 1
 * when both are still available. */
/* ADDRESS: GOLDTL 0x0041b290 */
/* ADDRESS: GOLDDE 0x00418fd0 */
char __cdecl d3_LoadSavedDisplayConfig(unsigned int* adapter, int* mode)
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
		if (io_ReadRegistryString(h, "d8_Guid", buf) && d3_ParseGuid(buf, guid)) {
			for (i = 0; i < g_6b5de8; i++) {
				if (memcmp(guid, g_6b5dd0[i].guid, sizeof(guid)) == 0) {
					*adapter = i;
					if (io_ReadRegistryString(h, "d8_Mode", buf) && d3_ParseDisplayMode(buf, mode)) {
						found = 1;
					}
				}
			}
		}
		io_CloseRegistryKey(h);
	}
	return found;
}
