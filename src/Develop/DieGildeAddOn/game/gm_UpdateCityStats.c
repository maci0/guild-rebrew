#include <string.h>
#include "Develop/client_types.h"

#pragma pack(push, 2)
typedef struct
{
	int a;
	unsigned short b;
	short b2;
	int c;
	short d;
} Blob14;
#pragma pack(pop)

extern Blob14 g_99f590;
extern pos14_7f4c00 gm_GameTime;
extern char g_99f5e0[];
extern float g_773d4c, g_773d50, g_773d54, g_99ec14, g_6628cc;

#pragma intrinsic(memcpy)

float __cdecl gm_GetCityStatsSummary(char* p);

/* ADDRESS: GOLDTL 0x004fb2c0 */
int __cdecl gm_UpdateCityStats(void)
{
	float buf[10];
	float v;
	double d;

	v = gm_GetCityStatsSummary((char*) buf);
	if (g_773d4c == 0.0f) {
		memcpy(g_99f5e0, buf, 40);
		d = ((double) v + 1.0) * g_773d54;
		g_773d50 = (float) d;
		g_773d4c = (float) (d * 0.95);
	} else {
		memcpy(g_99f5e0, buf, 40);
		d = ((double) v + 1.0) * g_773d54;
		g_773d50 = (float) ((d - g_773d50) * g_6628cc + g_773d50);
	}
	g_99ec14 = (float) ((g_773d50 - g_773d4c) * 0.0007336182331406322);
	g_99f590 = *(Blob14*) &gm_GameTime;
	return (int) g_773d50;
}
