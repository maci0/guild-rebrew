#include "Develop/DieGildeAddOn/game/ch_script.h"



#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d3_ActiveScene;
extern int evt_ActiveContextId;
extern char* evt_CurrentScript;
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
#include "Develop/Units/d3/client_scene_transform.h"
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

char* __cdecl DummyBlocked(char** a, int* range)
{
	float pos[4];
	char* result;
	char* e;
	char* t;
	int i;

	result = 0;
	if (*a == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 0;
	}
	i = 0;
	d3_TransformPoint(*a, *a + 0x4c, pos);
	for (; i < 0x300; i++) {
		e = ((char**)ch_CharacterSlots)[i];
		if (e != 0 && *(char**) (e + 0x88) == ((char*)d3_ActiveScene) && *(int*) (e + 0x2c) == evt_ActiveContextId) {
			if (CompareVector3WithinTolerance((float*) (*(char**) (e + 0x34) + 0x4c), pos, (float) *range)) {
				result = ((char**)ch_CharacterSlots)[i];
				break;
			}
			t = *(char**) (((char**)ch_CharacterSlots)[i] + 0x128);
			if (t != 0 && t[9] == 0x2d && CompareVector3WithinTolerance((float*) (t + 0x134), pos, (float) *range)) {
				result = ((char**)ch_CharacterSlots)[i];
				break;
			}
		}
	}
	return result;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_14d0020[532480];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_14d0024[3100];
unsigned char _dpad_14d0c44[4860];
unsigned char _dpad_14d1f44[262140];
unsigned char _dpad_1511f48[262136];
unsigned char _dpad_1552004[12];
unsigned char _dpad_1552014[12];
#endif
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_14d0024[3100];
unsigned char _dpad_14d0c44[4860];
unsigned char _dpad_14d1f44[262140];
unsigned char _dpad_1511f48[262136];
unsigned char _dpad_1552004[12];
unsigned char _dpad_1552014[12];
#endif
