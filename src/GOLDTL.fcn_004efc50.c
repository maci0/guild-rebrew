// FUNCTION: GOLD 0x4eddf0
// SIZE: 119
// FUNCTION: GOLDTL 0x004efc50
// SIZE: 119

#include <string.h>

typedef struct
{
	int id;
	int flags;
	float s[3];
	char pad[0x15c];
} Slot170;
// SIZE 0x170

typedef struct
{
	char b[14];
} Blob14;
// SIZE 0xe

extern Slot170 g_7731b8[8];
extern Blob14 g_772fe8;
extern Blob14 g_7f4c00;
extern int g_9a9200[8];

void __cdecl fcn_004efc50(void)
{
	int i;

	memset(g_7731b8, 0, sizeof(g_7731b8));
	for (i = 0; i < 8; i++) {
		g_7731b8[i].id = -1;
		g_7731b8[i].s[0] = 1.0f;
		g_7731b8[i].s[1] = 1.0f;
		g_7731b8[i].s[2] = 1.0f;
	}
	g_772fe8 = g_7f4c00;
	memset(g_9a9200, 0, sizeof(g_9a9200));
	g_9a9200[0] = -1;
}
