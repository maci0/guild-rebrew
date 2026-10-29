#include "client_types.h"

int __cdecl fcn_004e8b40(int idx, Rec18_68da68* out);

/* ADDRESS: GOLDTL 0x004e9180 */
int __cdecl fcn_004e9180(void* rec, int role)
{
	Rec18_68da68 r1;
	Rec18_68da68 r2;
	int step;

	if (role == 0 || role > 0x1b) {
		return 0;
	}
	if (!fcn_004e8b40(role, &r1)) {
		return 0;
	}
	if (!fcn_004e8b40(*(unsigned char*) ((char*) rec + 0x166), &r2)) {
		return 0;
	}
	if (r1.x4 != r2.x4) {
		return 0;
	}
	step = r1.type % 3;
	if (step == 0 && r2.type % 3 != 0) {
		return 1;
	}
	if (step == 2 && r2.type % 3 == 0) {
		return 1;
	}
	if (step == 1 && r2.type % 3 == 2) {
		return 1;
	}
	return 0;
}
