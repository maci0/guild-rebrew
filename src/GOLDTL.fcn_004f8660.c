#include <string.h>
extern void __cdecl fcn_0051af00(char *buf, int id, ...);
extern void __cdecl fcn_004fa5f0(char *buf, int a1, int a2);

/* ADDRESS: GOLDTL 0x004f8660 */
int __cdecl fcn_004f8660(char *obj, int *msg)
{
	if (*msg != 3 && *msg != 1) {
		return 1;
	}
	if (obj[0x169] != 0x1c) {
		return 1;
	}
	if (*msg == 3 && obj[2] == 6) {
		char buf[0x200];

		memset(buf, 0, sizeof buf);
		fcn_0051af00(buf, 0x1da4, obj[9] ? 0x297 : 0x26f);
		fcn_004fa5f0(buf, 0, 0x657c7);
		return 2;
	}
	if (*msg == 1 && obj[2] == 6) {
		fcn_0051af00((char *) msg + 0x14, 0x679060, 0x1da3);
	}
	return 2;
}
