#include "client_sound.h"

void __cdecl fcn_00423670(char* obj, int a, int b);


int __cdecl fcn_004193f0(char* obj, void* label, int mode, float amount)
{
	SOUND_SOURCE req;
	double scaled;

	if (obj == 0 || label == 0) {
		return 0;
	}
	scaled = amount * g_662b40;
	req.objekt = label;
	req.playbackControl = 1;
	req.voice = obj;
	*(int*) (obj + 0xc) = 1;
	*(int*) (obj + 0x14) = 0;
	req.volume = mode;
	req.range = (float)scaled;
	fcn_00418fb0(&req);
	fcn_004190d0(&req);
	if (*(int*) (obj + 0x24) == 0) {
		return 0;
	}
	fcn_00423670(obj, 0, 0);
	return 1;
}
