// FUNCTION: GOLD 0x4e5bf0
// FUNCTION: GOLDTL 0x4e7700

#include <string.h>

void __cdecl fcn_004e73f0(unsigned short*, char*);
void __cdecl fcn_004e7490(unsigned short*, char*);
void __cdecl fcn_004e7550(unsigned short*, char*);
void __cdecl fcn_004e75a0(unsigned short*, char*);
void __cdecl fcn_004e7600(unsigned short*, char*);
void __cdecl fcn_004e7660(unsigned short*, char*);

void __cdecl fcn_004e7700(unsigned short* e)
{
	char buf[0x1fb8];

	if (e == 0 || *e == 0xffff)
		return;
	memset(buf, 0, sizeof(buf));
	fcn_004e73f0(e, buf + strlen(buf));
	fcn_004e7490(e, buf + strlen(buf));
	fcn_004e7550(e, buf + strlen(buf));
	fcn_004e75a0(e, buf + strlen(buf));
	fcn_004e7600(e, buf + strlen(buf));
	fcn_004e7660(e, buf + strlen(buf));
}
