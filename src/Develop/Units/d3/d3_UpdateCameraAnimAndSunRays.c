

extern int d3_ActiveCameraAnimation;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d3/d3_camera.h"
extern char* SonnenstrahlenObjekt;
extern int d3_ActiveScene;
#ifdef REBREW_GOLD
#define OBJ_SND_OFF 0x208
#else
#define OBJ_SND_OFF 0x20c
#endif

void __cdecl d3_FreeObjectAnimation(void*);
void __cdecl d3_UpdateSunRays(char*);

/* ADDRESS: GOLD 0x00411c10 */
void __cdecl d3_UpdateCameraAnimAndSunRays(void)
{
	if ((*(char**)&d3_ActiveCameraAnimation) != 0) {
		d3_CameraAnimating = 1;
		if ((*(char**)&d3_ActiveCameraAnimation)[0x2d] & 0x20) {
			d3_FreeObjectAnimation(d3_ActiveCamera);
			d3_CameraAnimating = 0;
			(*(char**)&d3_ActiveCameraAnimation) = 0;
		}
	}
	if (SonnenstrahlenObjekt != 0 && d3_ActiveScene == *(int*) (SonnenstrahlenObjekt + OBJ_SND_OFF)) {
		d3_UpdateSunRays(SonnenstrahlenObjekt);
	}
}
