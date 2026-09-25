#include <string.h>

int __cdecl fcn_00464e60(char* s);
int __cdecl fcn_00464eb0(char* s);
int __cdecl fcn_00464a90(char* file, void* info, char* name, unsigned long nsize, void* extra, unsigned long esize, char* comment, unsigned long csize);
int __cdecl fcn_004645a0(const char* a, const char* b, int cs);

// FUNCTION: GOLDTL 0x464f30
// SIZE: 225
int __cdecl fcn_00464f30(char* s, const char* name, int cs)
{
	int err;
	unsigned long num_saved;
	unsigned long pos_saved;

	if (s == 0) {
		return -102;
	}
	if (strlen(name) >= 0x100) {
		return -102;
	}
	if (*(int*) (s + 0x18) == 0) {
		return -100;
	}
	num_saved = *(unsigned long*) (s + 0x10);
	pos_saved = *(unsigned long*) (s + 0x14);
	err = fcn_00464e60(s);
	while (err == 0) {
		char cur[0x101];

		fcn_00464a90(s, 0, cur, 0x100, 0, 0, 0, 0);
		if (fcn_004645a0(cur, name, cs) == 0) {
			return 0;
		}
		err = fcn_00464eb0(s);
	}
	*(unsigned long*) (s + 0x10) = num_saved;
	*(unsigned long*) (s + 0x14) = pos_saved;
	return err;
}
