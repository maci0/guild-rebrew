#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl fcn_004355d0(char*, const char*);
void __cdecl fcn_00435630(char*, char*, char);

#include "client_scene_transform.h"

void __cdecl fcn_00405540(char* object, int enabled)
{
    char* animation;
    char* motion;
    char* node;

    if (*(void**) (object + 0x128) != 0) {
        animation = *(char**) (object + 0x70);
        if (animation != 0) {
            motion = *(char**) (animation + 0x68);
            node = *(char**) (*(char**) (object + 0x34) + 0x1ec);
            if (enabled != 0) {
                fcn_004355d0(node + 0xf4, motion);
                object[0x8c] |= 4;
            } else {
                fcn_00435630(node + 0xf4, motion, 1);
                object[0x8c] &= 0xfb;
            }
        }
    }
}


/* Returns the camera offset and rotation for one of the four character
 * views, relative to the character's node. */
void __cdecl fcn_004055a0(char* obj, int view, float* pos, float* rot)
{
	if (obj == 0) {
		return;
	}
	switch (view) {
	case 0:
		pos[0] = -3.0f;
		pos[1] = 63.0f;
		pos[2] = 36.0f;
		rot[1] = 3.14159274f;
		rot[0] = 0.0f;
		rot[2] = 0.0f;
		break;
	case 1:
		pos[0] = -10.0f;
		pos[1] = 63.0f;
		pos[2] = -14.0f;
		rot[0] = 0.0872664675f;
		rot[1] = 0.0f;
		rot[2] = 0.0f;
		break;
	case 2:
		pos[0] = 10.0f;
		pos[1] = 63.0f;
		pos[2] = -14.0f;
		rot[0] = 0.0872664675f;
		rot[1] = 0.0f;
		rot[2] = 0.0f;
		break;
	case 3:
		pos[0] = 0.0f;
		pos[1] = 65.0f;
		pos[2] = 0.0f;
		rot[1] = 0.0f;
		rot[0] = 0.0f;
		rot[2] = 0.0f;
		break;
	}
	if (obj[0x8c] & 0x10) {
		pos[1] = (float) (pos[1] - 15.0);
	}
	fcn_00455540(*(char**) (obj + 0x34), pos, pos);
	rot[0] = *(float*) (*(char**) (obj + 0x34) + 0x84) + rot[0];
	rot[1] = *(float*) (*(char**) (obj + 0x34) + 0x88) + rot[1];
	rot[2] = *(float*) (*(char**) (obj + 0x34) + 0x8c) + rot[2];
}
