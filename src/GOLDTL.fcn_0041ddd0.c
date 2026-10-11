// FUNCTION: GOLD 0x00422620
// FUNCTION: GOLDTL 0x0041ddd0

#include "memtrack.h"

extern int g_6b6f78;
extern int g_6b6f64;
extern MemBlock* g_6b6f80;
extern int g_6b6f6c;
extern int g_6b6f68;
void __cdecl free(void* p);

void __cdecl fcn_0041ddd0(void* p)
{
	MemBlock* s;
	int i;
	int size;

	if (p == 0) {
		return;
	}
	s = g_6b6f80;
	g_6b6f78--;
	for (i = 0; i < g_6b6f64; i++) {
		if (s->ptr == p) {
			break;
		}
		s++;
	}
	if (i == g_6b6f64) {
		return;
	}
	size = s->size;
	s->ptr = 0;
	free(p);
	g_6b6f6c--;
	s->pool->used_blocks--;
	g_6b6f68 -= size;
	s->pool->used -= size;
}
