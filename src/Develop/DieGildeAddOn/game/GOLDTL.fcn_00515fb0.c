#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;



void __cdecl gm_GetSeason(char*);
int __cdecl gm_CheckEntityType(unsigned char*);
void __cdecl d3snd_PlayAmbientVoice(const char*, int, int);

void __cdecl d3snd_PlayBuildingAmbient(unsigned char* e)
{
	gm_GetSeason(((char*)&gm_GameTime));
	if (e != 0 && gm_CheckEntityType(e) && *(short*) (e + 0x29) == 0xfd && *e == 0x1e) {
		d3snd_PlayAmbientVoice("AesteKnacken_s", 0x50, 0x1f40);
	}
}
