#include <stdio.h>
#include <stdlib.h>

#include "memtrack.h"

extern int g_6b6f64;
extern int g_6b6f68;
extern int g_6b6f6c;
extern int g_6b6f70;
extern int g_6b6f74;
extern int g_6b6f7c;
extern MemBlock* g_6b6f80;
extern char* g_14cc5e4;

void __cdecl fcn_0041d9e0(const char*);
void __cdecl fcn_0041df00(int);

// FUNCTION: GOLD 0x00422910
// FUNCTION: GOLDTL 0x41e0c0

/* Shuts the memory tracker down: reports leaks, frees every tracked block
 * and the pool list. */
void __cdecl fcn_0041e0c0(void)
{
	int i;
	MemBlock* b;
	char* p;
	char* next;
	char msg[0x400];

	if (g_6b6f6c != 0 || g_6b6f68 != 0 || g_6b6f7c != 0) {
		if (g_6b6f6c != 0 || g_6b6f68 != 0) {
			sprintf(msg, "[*] Memory-Shutdown-Anomaly: [*]\nUsed %i blocks in %i bytes.\n\n%i block(s) left in %i bytes.", g_6b6f74, g_6b6f70, g_6b6f6c, g_6b6f68);
			fcn_0041d9e0(msg);
		}
		if (g_6b6f7c != 0) {
			fcn_0041df00(0);
		}
		b = g_6b6f80;
		for (i = 0; i < g_6b6f64; i++, b++) {
			if (b->ptr != 0) {
				sprintf(msg, "-> Pointer not freed:%s", b->tag);
				free(b->ptr);
				b->ptr = 0;
			}
		}
	}
	g_6b6f74 = 0;
	g_6b6f6c = 0;
	g_6b6f70 = 0;
	g_6b6f68 = 0;
	g_6b6f64 = 0;
	for (p = g_14cc5e4; p != 0; p = next) {
		next = *(char**) (p + 0x24);
		free(p);
	}
	free(g_6b6f80);
	g_6b6f80 = 0;
}
