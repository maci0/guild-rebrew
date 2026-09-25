// FUNCTION: GOLDTL 0x00411590
// SIZE: 113

#include <windows.h>

extern unsigned short g_14cf300[];

int __cdecl fcn_00411590(void)
{
	int i;
	int k;

	for (i = 0; i < 0x100; i++) {
		k = VkKeyScanA((CHAR) i);
		if (k != -1) {
			if ((k & 0xff00) == 0x600) {
				k = (k & 0xff) | 0x400;
			}
			g_14cf300[i] = (unsigned short) (((MapVirtualKeyA(k & 0xff, 0) ^ k) & 0xff) ^ k);
		} else {
			g_14cf300[i] = 0xffff;
		}
	}
	return 1;
}
