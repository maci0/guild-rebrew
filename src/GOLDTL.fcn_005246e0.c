#include "Develop/DieGildeAddOn/loadsave/loadsave.h"

/* ADDRESS: GOLDTL 0x005246e0 */
unsigned int __cdecl fcn_005246e0(unsigned int stream)
{
	char* p;
	char* q;
	int i;
	int j;
	int value;

	value = 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5e0, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5e4, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5e8, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5ec, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5f0, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5f4, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5f8, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5fc, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f600, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f604, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99ec14, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f590, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f594, 2, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f596, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f59a, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x773d4c, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x773d50, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5a0, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5a4, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5a8, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5ac, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5b0, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5b4, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5b8, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5bc, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5c0, 4, 1, (void*) stream))
		return 0;
	p = (char*) 0x99ec24;
	do {
		if (!ls_ReadVfsDataChecked(p - 4, 4, 1, (void*) stream))
			return 0;
		if (!ls_ReadVfsDataChecked(p, 4, 1, (void*) stream))
			return 0;
		if (!ls_ReadVfsDataChecked(p + 4, 4, 1, (void*) stream))
			return 0;
		if (!ls_ReadVfsDataChecked(p + 8, 4, 1, (void*) stream))
			return 0;
		if (!ls_ReadVfsDataChecked(p + 0x0c, 4, 1, (void*) stream))
			return 0;
		p += 0x14;
	} while (p < (char*) 0x99ed64);
	if (!ls_ReadVfsDataChecked((void*) 0x99f6a0, 0x44, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f6e4, 0x44, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f728, 0x44, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f76c, 0x44, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f7b0, 0x44, 1, (void*) stream))
		return 0;
	p = (char*) 0x99ef82;
	while (1) {
		q = p;
		for (j = 0; j < 8; j++) {
			if (!ls_ReadVfsDataChecked(q - 2, 2, 1, (void*) stream))
				return 0;
			if (!ls_ReadVfsDataChecked(q, 2, 1, (void*) stream))
				return 0;
			if (!ls_ReadVfsDataChecked(q + 2, 1, 1, (void*) stream))
				return 0;
			if (!ls_ReadVfsDataChecked(q + 6, 4, 1, (void*) stream))
				return 0;
			q += 0x18;
		}
		p += 0xc0;
		if ((char*) 0x99f582 <= p)
			return 1;
	}
	return 0;
}
