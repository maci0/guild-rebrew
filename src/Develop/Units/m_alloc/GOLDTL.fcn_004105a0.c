

// SIZE 0xd5
typedef struct {
	char pad[0xd4];
	unsigned char b0 : 5;
	unsigned char b5 : 1;
} S4105a0;

#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl SetEmitterInitFill(S4105a0** a1, char* fill)
{
	S4105a0* emitter;

	emitter = *a1;
	if (m_is_tracked(emitter) == 0) {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676bfc);
		return 0;
	}
	emitter->b5 = *fill;
	return 0;
}
