#include <string.h>

int __cdecl fcn_00479010(void* surface);
int __cdecl fcn_004790d0(void* surface);

/* ADDRESS: GOLD 0x004796b0 */
int __cdecl fcn_004796b0(char* surface)
{
	unsigned int effects[25];
	int saved;
	void* object;
	if (surface == 0) {
		return 0;
	}
	saved = *(int*) (surface + 0x34);
	if (*(int*) (surface + 0x20) == 0) {
		if (saved != 0) {
			fcn_00479010(surface);
		}
		memset(*(void**) (surface + 0x1c), 0,
			*(unsigned int*) (surface + 0xc) * *(unsigned int*) (surface + 8));
	} else {
		if (saved != 0) {
			fcn_004790d0(surface);
		}
		memset(effects, 0, sizeof(effects));
		effects[20] = 0;
		effects[0] = 0x64;
		object = *(void**) (surface + 0x20);
		(*(int (__stdcall**) (void*, int, int, int, int, void*))
			(*(char**) object + 0x14))(object, 0, 0, 0, 0x1000400, effects);
	}
	if (saved != 0) {
		fcn_00479010(surface);
	} else {
		fcn_004790d0(surface);
	}
	return 1;
}
