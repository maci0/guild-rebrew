#include <string.h>

int __cdecl gm_CheckPrivilege(int a1, char* a2, int a3);

int __cdecl gm_CheckPrivilege(int a1, char* a2, int a3);

/* ADDRESS: GOLDTL 0x00498f50 */
int __cdecl fcn_00498f50(int busy, char* name)
{
	int buf[0x88];

	if (busy != 0)
		return 0;
	memset(buf, 0, sizeof(buf));
	buf[0] = 1;
	return gm_CheckPrivilege(2, name, (int) buf) == 2 ? 0x16 : 0;
}

/* ADDRESS: GOLDTL 0x00498fb0 */
int __cdecl fcn_00498fb0(char* name)
{
	int buf[0x88];

	memset(buf, 0, sizeof(buf));
	buf[0] = 1;
	return gm_CheckPrivilege(2, name, (int) buf) == 2 ? 0x16 : 0;
}
