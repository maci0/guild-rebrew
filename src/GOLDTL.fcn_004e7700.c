// FUNCTION: GOLD 0x4e5bf0
// FUNCTION: GOLDTL 0x4e7700

#include <string.h>





#include "Develop/DieGildeAddOnServer/server_stats.h"
void __cdecl fcn_004e7660(unsigned short*, char*);

void __cdecl fcn_004e7700(unsigned short* e)
{
	char buf[0x1fb8];

	if (e == 0 || *e == 0xffff)
		return;
	memset(buf, 0, sizeof(buf));
	srv_FormatStatIdentity((unsigned char*) e, buf + strlen(buf));
	srv_FormatStatAttributes((char*) e, buf + strlen(buf));
	srv_FormatStatSkills((unsigned char*) e, buf + strlen(buf));
	srv_FormatStatAemter((unsigned char*) e, buf + strlen(buf));
	srv_FormatStatTreasury(e, buf + strlen(buf));
	fcn_004e7660(e, buf + strlen(buf));
}
