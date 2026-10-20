#include "client_types.h"

int __cdecl fcn_004e8b40(int idx, Rec18_68da68* out);
char* __cdecl fcn_00508e40(int a1);

/* ADDRESS: GOLDTL 0x00508f80 */
int __cdecl fcn_00508f80(unsigned short a0, int a1)
{
	Rec18_68da68 rec;
	int v6;
	char* v3;
	int idx;

	idx = a0 * 0x21c;
	if (*(int*) (0x7f4ca4 + idx) == -1 || *(unsigned char*) (0x7f4ca8 + idx) <= 0)
		return 0;
	if (!fcn_004e8b40(*(unsigned char*) (0x7f4e07 + idx), &rec))
		return 1;
	v6 = (*(unsigned int*) ((char*) &rec + 8) & 0xff) + 1;
	if ((char) *(unsigned int*) ((char*) &rec + 8) == '\n')
		return v6;
	if (a1 != 0)
		return v6;
	v3 = fcn_00508e40(*(int*) (0x7f4d00 + idx));
	if (v3 != 0) {
		if (v6 > fcn_00508f80(*(unsigned short*) v3, 1))
			return v6;
		return fcn_00508f80(*(unsigned short*) v3, 1);
	}
	return v6;
}
