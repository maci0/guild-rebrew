#include "client_types.h"

int __cdecl fcn_004e8b40(int idx, Rec18_68da68* out);

/* ADDRESS: GOLDTL 0x004e9180 */
int __cdecl fcn_004e9180(void* rec, int role)
{
	Rec18_68da68 r[2];

	if (role == 0 || role > 0x1b) {
		return 0;
	}
	if (!fcn_004e8b40(role, &r[0])) {
		return 0;
	}
	if (!fcn_004e8b40(*(unsigned char*) ((char*) rec + 0x166), &r[1])) {
		return 0;
	}
	if (r[0].x4 != r[1].x4) {
		return 0;
	}
	if (r[0].type % 3 == 0 && r[1].type % 3 != 0) {
		return 1;
	}
	if (r[0].type % 3 == 2 && r[1].type % 3 == 0) {
		return 1;
	}
	if (r[0].type % 3 == 1 && r[1].type % 3 == 2) {
		return 1;
	}
	return 0;
}
