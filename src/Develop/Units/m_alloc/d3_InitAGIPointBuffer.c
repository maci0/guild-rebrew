char str_d3_io_a_AGIPointBuffer[] = "d3_io_a:AGIPointBuffer";
extern char str_d3_io_a_AGIPointBuffer[];

#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl fcn_0064f026(char* s, const char* delim);
int __cdecl atoi(const char* s);
void* __cdecl m_alloc(int size, char* tag);

/* ADDRESS: GOLD 0x0044ece0 */
/* ADDRESS: GOLDTL 0x0044d5a0 */
/* ADDRESS: GOLDDE 0x00443330 */
void __cdecl d3_InitAGIPointBuffer(int unused, char* s)
{
	int n;

	n = atoi(fcn_0064f026(0, " "));
	*(int*) (s + 0x24) = n;
	if (n > 0 && *(void**) (s + 0x30) == 0) {
		*(int*) (s + 0x28) = 0;
		*(int*) (s + 0x2c) = 0;
		*(void**) (s + 0x30) = m_alloc(0x60000, str_d3_io_a_AGIPointBuffer);
	}
}
