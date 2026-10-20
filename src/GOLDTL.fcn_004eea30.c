#include <string.h>

typedef struct {

	int tag;
	int obj;
	int id;
	int xc;
	float f;
	int x14;
} Msg18F;

extern float g_6628a8;
extern float g_6628a0;

int __cdecl ahm_CheckFlag(void* p);
int __cdecl fcn_004ec950(void* p, int id);
int __cdecl fcn_004c6d30(void* m);

/* ADDRESS: GOLDTL 0x004eea30 */
int __cdecl fcn_004eea30(void* a0, int a1, float a2)
{
	Msg18F m;

	if (ahm_CheckFlag(a0) == 0) {
		return -1;
	}
	if (fcn_004ec950(a0, a1) == 0) {
		return -1;
	}
	memset(&m, 0, sizeof(m));
	m.tag = 0x61535263;
	m.obj = *(int*) ((char*) a0 + 4);
	m.id = a1;
	if (a2 > g_6628a8) {
		if (a2 < g_6628a0) {
			m.f = a2;
		} else {
			m.f = 1.0f;
		}
	} else {
		m.f = 0.0f;
	}
	return fcn_004c6d30(&m);
}
