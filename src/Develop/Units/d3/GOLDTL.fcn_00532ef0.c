


// SIZE 0x90
typedef struct {
	char pad0[0x4c];
	float pos[3];
	char pad58[0x84 - 0x58];
	float rot[3];
} View;

extern int d3_ActiveCameraAnimation;
extern int d3_CameraAnimating;
extern float g_14ce880[3];
extern float g_7e3a40[3];
extern float d3_CameraTargetRotation[3];
#include "Develop/Units/d3/d3_camera.h"
extern int g_774650;
#include "client_dialog_state.h"
extern int g_774658;
extern int g_77465c;
extern char* g_7746a8;
extern int g_7e2a9c;

#include "client_scene_transform.h"
void __cdecl fcn_00433780(View* v);
void __cdecl fcn_00438b40(View* v, float* p);
void __cdecl fcn_00438cb0(View* v, float* r);
void __cdecl fcn_0052d820(void);
void __cdecl fcn_00530510(void);

void __cdecl fcn_00532ef0(void)
{
	int done;
	char* e;

	done = 0;
	if (d3_ActiveCameraAnimation != 0) {
		if (CompareVector3WithinTolerance(g_14ce880, g_7e3a40, 0.1f)) {
			fcn_00433780(((View*)d3_ActiveCamera));
			d3_ActiveCameraAnimation = 0;
			d3_CameraAnimating = 0;
			done = 1;
			fcn_00438b40(((View*)d3_ActiveCamera), g_7e3a40);
			fcn_00438cb0(((View*)d3_ActiveCamera), d3_CameraTargetRotation);
		} else {
			fcn_00433780(((View*)d3_ActiveCamera));
			d3_ActiveCameraAnimation = 0;
			d3_CameraAnimating = 0;
		}
	}
	if (g_774650 > g_774658 && done == 0) {
		if (g_77465c >= g_774650 - g_774654) {
			fcn_0052d820();
			g_77465c = g_774650 - g_774654;
			if (g_7746a8 != 0) {
				e = *(char**) (g_7746a8 + 0x1d4);
				if (e != 0 && *(void**) (e + 0x18c) != 0) {
					(*(void(__cdecl**)(char*, int, char*, int)) (e + 0x18c))(g_7746a8, 3, e + 0x190, 0);
				}
				g_7746a8 = 0;
			}
			if (g_7e2a9c != 0) {
				fcn_00530510();
			}
		}
	} else if ((!CompareVector3WithinTolerance(((View*)d3_ActiveCamera)->rot, d3_CameraTargetRotation, 0.1f) || !CompareVector3WithinTolerance(((View*)d3_ActiveCamera)->pos, g_7e3a40, 0.1f)) &&
		   done == 0) {
		fcn_0052d820();
		if (g_7746a8 != 0) {
			e = *(char**) (g_7746a8 + 0x1d4);
			if (e != 0 && *(void**) (e + 0x18c) != 0) {
				(*(void(__cdecl**)(char*, int, char*, int)) (e + 0x18c))(g_7746a8, 3, e + 0x190, 0);
			}
			g_7746a8 = 0;
		}
	}
	if (g_7e2a9c != 0) {
		fcn_00530510();
	}
}
