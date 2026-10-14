#include <stdio.h>

#include "../DieGildeAddOn/game/aemter.h"
#include "server_stats.h"
#include "../rebrew_types.h"
#include "../rebrew_globals.h"


/* Name and unit inferred from the adjacent client statistic formatters. */
void __cdecl srv_FormatStatIdentity(unsigned char* entity, char* out)
{
	char* name;

	if (entity[2] >= 10)
		name = g_68d780[10];
	else
		name = g_68d780[entity[2]];
	sprintf(out, "%i\t%i\t%i\t%s\t%s\t%i\t%s\t%i\t%s\t%s\t%s\t%s\t",
	    g_current_year, *(int*) (entity + 4), *(unsigned short*) entity, name,
	    entity + 0x30, entity[8], g_14a6544[entity[9]], *(unsigned short*) (entity + 0xa),
	    g_14a6538[entity[0xc]], g_14a5770[entity[0xd]], g_14a57e0[entity[0x164]],
	    g_14a5b54[entity[0x165]]);
}

/* Name and unit inferred from the adjacent client statistic formatters. */
void __cdecl srv_FormatStatAemter(unsigned char* entity, char* out)
{
	sprintf(out, "%s\t%s\t%s\t%s\t",
	    g_14a5c6c[entity[0x166]], g_14a5c6c[entity[0x167]],
	    g_14a5c6c[entity[0x168]], g_14a5c6c[entity[0x169]]);
}
