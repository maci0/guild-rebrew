#include <stdlib.h>
#include <windows.h>
#include "Develop/Units/m_alloc/m_alloc.h"

void __cdecl fcn_0045e610(void*, int);

/* d3sm shadow map record, 0x34 bytes; fields before 0x20 are unrecovered. */
typedef struct D3SM {
	char pad00[0x20];
	int size;
	char* entries;
	char* height;
	char pad2c[4];
	int flag;
} D3SM;

/* ADDRESS: GOLD 0x0045eea0 */
D3SM* __cdecl fcn_0045eea0(int src, int n, int flag)
{
	D3SM* sm;

	sm = 0;
	if (n != 0) {
		sm = (D3SM*) m_alloc(sizeof(D3SM), "d3_sm:Create");
		sm->flag = flag;
		sm->size = abs(n);
		sm->height = (char*) m_alloc(sm->size * sm->size, "d3_sm:CreateHeight");
		if (n > 0) {
			sm->entries = (char*) m_alloc(sm->size * sm->size * 28, "d3_sm:CreateEntries");
		} else {
			sm->entries = 0;
		}
		if (sm->height != 0) {
			fcn_0045e610(sm, src);
		}
		if (n < 0) {
			OutputDebugStringA("d3sm_Create(shadow)");
		} else {
			OutputDebugStringA("d3sm_Create");
		}
	}
	return sm;
}
