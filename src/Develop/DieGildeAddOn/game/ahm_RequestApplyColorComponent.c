

#include <string.h>

// SIZE 0x18
typedef struct {
	int tag;
	int id;
	int arg;
	int pad;
	float val;
	int pad2;
} AHM_APPLY_COLOR_MSG;

/* The clamp is the min/max macro expansion: its compare order lays out the
 * 0.0f and 1.0f arms as in the reference. */
#define MAXV(a, b) (((a) > (b)) ? (a) : (b))
#define MINV(a, b) (((a) < (b)) ? (a) : (b))

int __cdecl ahm_CheckFlag(void* a);
int __cdecl cm_RequestAhmCommand(AHM_APPLY_COLOR_MSG* m);

/* ADDRESS: GOLDDE 0x004dab10 */
int __cdecl ahm_RequestApplyColorComponent(char* obj, int arg, float factor)
{
	AHM_APPLY_COLOR_MSG m;

	if (ahm_CheckFlag(obj) == 0) {
		return -1;
	}
	memset(&m, 0, sizeof(m));
	m.tag = 0x61437353;
	m.id = *(int*) (obj + 4);
	m.arg = arg;
	m.val = MINV(MAXV(factor, 0.0f), 1.0f);
	return cm_RequestAhmCommand(&m);
}
