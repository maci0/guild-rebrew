#include "Develop/Units/d3/d3_animation.h"

#include "client_lighting.h"

extern volatile int g_6b7fac;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_00434ba0(char* anim, char* mesh);
int __cdecl d3_StepAnimFrame(D3_ANIMATION_OPTIONS flags, int v, int lo, int hi, int max);
int __cdecl d3_CreateObjectMesh(char* e);
char __cdecl d3_BindAnimTrackNodes(char* obj);
void __cdecl d3_UpdateObjectAnimPose(int obj);

/* Claims the first free animation slot of the context, fills it from the
 * named animation and the 12-byte options block, and returns the slot. */
/* ADDRESS: GOLDTL 0x00434970 */
char* __cdecl d3_AttachAnimationToContext(char* context, char* name, D3_ANIMATION_OPTIONS options)
{
	char* object;
	char* base;
	char* entry;
	char* scan;
	int slot;
	int table;

	if (context != 0) {
		object = d3_FindAnimByName(name);
		for (slot = 0, scan = context + 0x390; slot < 3; slot++, scan += 0x7c) {
			if (*(int*) scan == 0) {
				break;
			}
		}
		if (object != 0) {
			if (*(int*) (object + 0x140) == *(int*) (context + 0x310)) {
				if (slot < 3) {
					g_6b86d4++;
					entry = context + 0x328 + slot * 0x7c;
					table = *(int*) (context + 0x320);
					base = (char*) table;
					*(int*) (table + 0x40) = g_6b7fac;
					*(char*) (context + 0x4a0) = 1;
					*(char**) (entry + 0x68) = object;
					*(float*) (entry + 0x60) = 1.0f;
					*(int*) (entry + 0x64) = 0;
					*(int*) (entry + 0x3c) = 100;
					*(int*) (object + 0x14c) += 1;
					*(int*) (object + 0x158) = g_6b8008;
					if (*(char*) (object + 0x168) == 0) {
						if (*(int*) (context + 0x318) != 0) {
							fcn_00434ba0(object, *(char**) (context + 0x318));
							*(char*) (object + 0x168) = 1;
						}
					}
					*(D3_ANIMATION_OPTIONS*) (entry + 0x6c) = options;
					*(unsigned char*) (entry + 0x6d) &= 0xdf;
					*(unsigned char*) (entry + 0x74) = (*(unsigned char*) (entry + 0x74) & 0xb7) | 0x10;
					if (options.mode == 1) {
						*(unsigned char*) (entry + 0x6d) |= 0x10;
					}
					*(int*) (entry + 0x1c) = -1;
					*(int*) (entry + 0x18) = -1;
					*(int*) (entry + 0x14) = -1;
					*(int*) (entry + 0x30) = 0;
					*(int*) (entry + 0x38) = 0;
					*(int*) (entry + 0x34) = 0;
					*(float*) (entry + 0x48) = 1.0f;
					*(float*) (entry + 0x44) = 1.0f;
					*(float*) (entry + 0x40) = 1.0f;
					*(int*) (entry + 0x10) = 0;
					if (*(char*) (object + 0x169) != 0) {
						*(int*) (entry + 0xc) = 0;
					} else {
						*(int*) (entry + 0xc) = *(int*) (object + 0x150);
					}
					if (*(unsigned char*) (entry + 0x6d) & 2) {
						*(int*) entry = *(int*) (object + 0x148) - 1;
						*(int*) (entry + 8) = *(int*) (*(int*) (object + 0x15c) + *(int*) entry * 0xc0 + 4) - 1;
						*(int*) (entry + 4) = d3_StepAnimFrame(*(D3_ANIMATION_OPTIONS*) (entry + 0x6c), *(int*) entry,
							*(int*) (object + 0x150), *(int*) (object + 0x154), *(int*) (object + 0x148));
					} else {
						*(int*) (entry + 8) = 0;
						*(int*) entry = 0;
						*(int*) (entry + 4) = 1;
					}
					if (*(int*) (context + 0x318) != 0) {
						table = *(int*) (context + 0x318);
						if (*(int*) (table + 0x264) != 0) {
							if (*(unsigned char*) (table + 0x2a1) & 2) {
								if (*(int*) (table + 0x268) == 0) {
									*(int*) (*(int*) (context + 0x318) + 0x268) = d3_CreateObjectMesh(*(char**) (context + 0x318));
								}
							}
						}
					}

					d3_BindAnimTrackNodes(base);
					d3_UpdateObjectAnimPose((int) base);
					g_6b86d4--;
					return entry;
				}
			}
		}
	}
	return 0;
}
