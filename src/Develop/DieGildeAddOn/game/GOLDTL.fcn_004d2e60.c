


#include "Develop/DieGildeAddOn/game/game_data.h"
extern int main_LoopFlags;
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char g_68bd68[];
extern char g_68bd54[];
extern char g_68bd44[];
extern char g_68bd2c[];
extern char g_68bd14[];
extern char g_68bcec[];

unsigned short __cdecl gm_RandomMod(int);
void __cdecl msx_OverrideMusicTrack(char*);
void __cdecl d3_UpdateWeatherAndSkyBlend(void);
void __cdecl fcn_0052a960(char*);
char* __cdecl evt_LoadGfxScript(char*);
void __cdecl evt_RunScript(char*);
void __cdecl evt_WaitAndCancelScript(int);

void __cdecl cut_RunGfxCutscene(void)
{
	int r;
	char* p;

	d2_SuppressOverlay = 1;
	if (msx_MusicEnabled != 0) {
		r = gm_RandomMod(100);
		if (r < 20)
			msx_OverrideMusicTrack(g_68bd68);
		else if (r < 40)
			msx_OverrideMusicTrack(g_68bd54);
		else if (r < 60)
			msx_OverrideMusicTrack(g_68bd44);
		else if (r < 80)
			msx_OverrideMusicTrack(g_68bd2c);
		else
			msx_OverrideMusicTrack(g_68bd14);
	}
	main_LoopFlags = 0x7d6c6;
	d3_UpdateWeatherAndSkyBlend();
	fcn_0052a960(((char*)&gm_GameTime));
	p = evt_LoadGfxScript(g_68bcec);
	if (p != 0) {
		evt_RunScript(p);
		evt_WaitAndCancelScript(*(int*) (p + 0x100));
	}
	d2_SuppressOverlay = 0;
}
