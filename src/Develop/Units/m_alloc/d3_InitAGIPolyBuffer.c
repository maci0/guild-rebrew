char d3_AgiPolyBufferTag[] = "d3_io_a:AGIPolyBuffer";
extern char d3_AgiPolyBufferTag[];

#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl fcn_0064f026(char* s, const char* delim);
int __cdecl atoi(const char* s);
void* __cdecl m_alloc(int size, char* tag);

/* ADDRESS: GOLD 0x0044ed30 */
/* ADDRESS: GOLDTL 0x0044d5f0 */
void __cdecl d3_InitAGIPolyBuffer(int unused, char* s)
{
	int n;

	n = atoi(fcn_0064f026(0, " "));
	*(int*) (s + 0x14) = n;
	if (n > 0 && *(void**) (s + 0x20) == 0) {
		*(int*) (s + 0x18) = 0;
		*(int*) (s + 0x1c) = 0;
		*(void**) (s + 0x20) = m_alloc(0xe0000, d3_AgiPolyBufferTag);
	}
}
