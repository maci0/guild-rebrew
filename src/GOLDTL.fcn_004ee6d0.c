// FUNCTION: GOLDTL 0x4ee6d0
// SIZE: 181

#include <string.h>

// SIZE 0x18
typedef struct {
	int tag;
	int id;
	int arg;
	int pad;
	float val;
	int pad2;
} Msg4ee6d0;

/* The clamp is the min/max macro expansion: its compare order lays out the
 * 0.0f and 1.0f arms as in the reference. */
#define MAXV(a, b) (((a) > (b)) ? (a) : (b))
#define MINV(a, b) (((a) < (b)) ? (a) : (b))

int __cdecl ahm_CheckFlag(void* a);
int __cdecl fcn_004c6d30(Msg4ee6d0* m);

int __cdecl fcn_004ee6d0(char* obj, int arg, float v)
{
	Msg4ee6d0 m;

	if (ahm_CheckFlag(obj) == 0) {
		return -1;
	}
	memset(&m, 0, sizeof(m));
	m.tag = 0x61437353;
	m.id = *(int*) (obj + 4);
	m.arg = arg;
	m.val = MINV(MAXV(v, 0.0f), 1.0f);
	return fcn_004c6d30(&m);
}
