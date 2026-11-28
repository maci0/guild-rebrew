#include <math.h>
#include <stdio.h>
#include <string.h>

#include "Develop/DieGildeAddOn/game/ch_motion.h"
#include "Develop/DieGildeAddOn/game/ch_queue.h"

extern int __cdecl sprintf(char* buf, const char* fmt, ...);

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char ch_SceneDebugSwitch;
extern int g_6b5c2c;
extern int g_6b5c30;
extern unsigned int ch_LastUpdateTime;
extern int d3_ActiveScene;

extern int __cdecl d3sm_GetObjectSuperMap(char*);
extern void __cdecl d3_RemoveObjectAnim(char*);
extern int __cdecl d3_GetContextIndex(int);
extern int __cdecl fcn_0041db70(int, const char*);
extern void __cdecl d3_GridPointToWorld(char*, int, int, float*);
extern int __cdecl d3_FindAnimByName(char*);
extern void __cdecl d3_ReleaseAnim(int, int);
extern void __cdecl d3_RemoveObjectAnimation(int, char*);
extern char* __cdecl fcn_00404dc0(char*, char*, int);
extern void __cdecl vfs_ToSlashes(char*);
extern char* __cdecl ch_AdjustHeightToGround(char*);
extern void __cdecl ch_EnsureCharacterMeshes(char*);
extern void __cdecl d3snd_PlayObjectSound(char*, char*, int, float);
extern char* __cdecl sb_PrepareVoice(int, char*);
extern float __cdecl d3_ComputeYawToTarget(char*, float*);
extern void __cdecl d3_SetObjectEulerRotation(char*, int, int, int);
extern void __cdecl ch_FinishAni(char*);
extern void __cdecl fcn_0041ddd0(char*);

/* ADDRESS: GOLDTL 0x0040aa00 */
void __cdecl ch_WalkOnPath58(char* obj)
{
	char* inst;
	char* o;
	char* p;
	char* table;
	char* q;
	int v;
	int state;
	int r;
	int i;
	int j;
	int t;
	float d;
	float f;
	float a;
	char buf[0x100];
	char name[0x80];

	v = d3sm_GetObjectSuperMap(*(char**) (obj + 0x14));
	inst = *(char**) (obj + 0x14);
	if (*(int*) (obj + 0x154) != -1) {
		if (ch_UpdateTime < *(int*) (obj + 0x154) + 200) {
			return;
		}
		if (*(int*) (inst + 0x70) != 0) {
			*(float*) (*(int*) (inst + 0x70) + 0x60) = 1.0f;
		}
		*(int*) (obj + 0x154) = -1;
	}
	if (*(int*) (obj + 0xc) == 0) {
		if (*(int*) (inst + 0x7c) != 0) {
			sprintf(buf, "morph_%i", (int) inst);
			d3_RemoveObjectAnimation(*(int*) (*(int*) (inst + 0x34) + 0x1ec) + 0xf4, buf);
			r = d3_FindAnimByName(buf);
			d3_ReleaseAnim(r, 1);
			*(int*) (inst + 0x7c) = 0;
		}
		d3_RemoveObjectAnim(*(char**) (inst + 0x34));
		*(float*) (inst + 0x1a4) = 1.0f;
		*(int*) (inst + 0x80) = 0;
		*(int*) (inst + 0x7c) = 0;
		*(int*) (inst + 0x70) = 0;
		*(unsigned char*) (*(int*) (obj + 0x14) + 0x8c) &= 0xf7;
		*(int*) (obj + 0xf4) = 0;
		memset((void*) (inst + 0x90), 0, 0x80);
		i = *(int*) (obj + 0x30);
		j = *(int*) (obj + 0x34);
		r = d3_GetContextIndex(*(int*) (inst + 0x88));
		if (r != *(int*) (obj + 0x38)) {
			ch_RemoveQueueEntry(obj);
			return;
		}
		r = fcn_0041db70(0x200, "ch_t:waypoints");
		*(int*) (obj + 0xf4) = r;
		if (!r) {
			__asm { int 3 }
		}
		*(int*) (obj + 0xf0) = 0x100;
		*(int*) (obj + 0xf8) = 0;
		*(int*) (obj + 0xfc) = -1;
		t = 0;
		do {
			*(unsigned char*) (t + *(int*) (obj + 0xf4)) = 0;
			*(unsigned char*) (t + 1 + *(int*) (obj + 0xf4)) = 0;
			t += 2;
		} while (t < 0x200);
		d3_GridPointToWorld((char*) v, *(unsigned char*) r, *(unsigned char*) (r + 1),
		             (float*) (obj + 0x124));
		d3_GridPointToWorld((char*) v, i, j, (float*) (obj + 0x124));
		*(int*) (obj + 0x104) = 0;
		return;
	}
	if (*(int*) (obj + 0x104) == 0) {
		p = *(char**) (inst + 0x70);
		if (p == 0 || (*(unsigned char*) (p + 0x6d) & 0x20) != 0) {
			*(int*) (inst + 0x80) = 0;
			if (*(int*) (inst + 0x7c) != 0) {
				sprintf(buf, "morph_%i", (int) inst);
				d3_RemoveObjectAnimation(*(int*) (*(int*) (inst + 0x34) + 0x1ec) + 0xf4, buf);
				r = d3_FindAnimByName(buf);
				d3_ReleaseAnim(r, 1);
				*(int*) (inst + 0x7c) = 0;
			}
			d3_RemoveObjectAnim(*(char**) (inst + 0x34));
			if (*(int*) (*(int*) (inst + 0x34) + 0x1cc) == 0) {
				ch_EnsureCharacterMeshes(inst);
			}
			p = fcn_00404dc0(inst,
			                 *(int*) (inst + 0x124) != 0 ? "bewegung/karren_ziehen"
			                                             : "bewegung/gehen",
			                 1);
			*(char**) (inst + 0x70) = p;
			if (p == 0) {
				if (ch_SceneDebugSwitch) {
					*(unsigned char*) (*(int*) (obj + 0x14) + 0x8c) |= 8;
				}
				goto remove;
			}
			*(unsigned char*) (p + 0x6d) &= 0xef;
			*(int*) (p + 0x70) = (*(int*) (p + 0x70) & 0xfffffffd) | 1;
			*(int*) (p + 0x4c) = *(int*) (obj + 0x124);
			*(int*) (p + 0x50) = *(int*) (obj + 0x128);
			*(int*) (p + 0x54) = *(int*) (obj + 0x12c);
			if (*(int*) (inst + 4) & 8) {
				*(float*) (p + 0x5c) = 30.0f;
			} else if (*(int*) (inst + 4) & 0x10) {
				*(float*) (p + 0x5c) = 60.0f;
			} else {
				*(float*) (p + 0x5c) = 15.0f;
			}
			*(unsigned char*) (p + 0x74) |= 2;
			*(unsigned char*) (p + 0x74) &= 0xf7;
			*(unsigned char*) (p + 0x74) |= 4;
			*(unsigned char*) (p + 0x6d) &= 0xdf;
			*(int*) (obj + 0x104) = 1;
		}
	}
	if (*(unsigned char*) (obj + 0x190) != 0) {
		sprintf(name, "%s_%s", "bewegung/gehen", inst + 0x130);
		vfs_ToSlashes(name);
		if (*(int*) (inst + 0x70) != 0) {
			d3_RemoveObjectAnimation(*(int*) (*(int*) (inst + 0x34) + 0x1ec) + 0xf4,
			             *(int*) (*(int*) (inst + 0x70) + 0x68));
		}
		*(int*) (inst + 0x70) = 0;
		ch_AdjustHeightToGround(obj);
		if (ch_SceneDebugSwitch) {
			*(unsigned short*) (*(int*) (obj + 0x14) + 0x8c) |= 8;
		}
		goto remove;
	}
	if (*(int*) (obj + 0x104) == 0) {
		if (*(int*) (inst + 0x70) != 0) {
			return;
		}
		if (ch_SceneDebugSwitch) {
			*(unsigned short*) (*(int*) (obj + 0x14) + 0x8c) |= 8;
		}
		goto remove;
	}
	state = ch_AdjustHeightToGround(obj);
	p = *(char**) (inst + 0x70);
	if (p != 0 && g_6b5c2c != 0 && d3_ActiveScene == *(int*) (inst + 0x88) &&
	    g_67530c == *(int*) (inst + 0x2c) &&
	    *(int*) p != *(unsigned char*) (obj + 0x100) &&
	    (*(int*) p == 4 || *(int*) p == 0x0c || *(int*) p == 0x12 ||
	     *(int*) p == 0x18)) {
		if ((*(unsigned char*) (inst + 4) & 1) && g_6b5c30 < 3 &&
		    d3_GetContextIndex(*(int*) (inst + 0x88)) != 0) {
			o = *(char**) (inst + 0x88);
			if (*(int*) (o + 0xac) == 0) {
				r = sb_PrepareVoice(g_6b5c2c, "normal_s");
			} else {
				strcpy(buf, "Normal_s");
				switch (state) {
				case 6:
				case 0x0b:
					strcpy(buf, "Stein_s");
					break;
				case 3:
					strcpy(buf, "Erde_s");
					break;
				case 4:
					strcpy(buf, "Wiese_s");
					break;
				case 8:
					strcpy(buf, "Stein_s");
					break;
				case 0x0a:
					strcpy(buf, "Pfuetze_s");
					break;
				}
				r = sb_PrepareVoice(g_6b5c2c, buf);
			}
			if (r != 0) {
				d3snd_PlayObjectSound(r, *(char**) (inst + 0x34), 0x28, 500.0f);
				g_6b5c30++;
			}
			*(unsigned char*) (obj + 0x100) = *p;
		}
	}
	if (*(float*) (inst + 0x1a4) < 1.0) {
		*(float*) (inst + 0x1a4) += 0.01f;
	}
	if (*(int*) (obj + 0xf8) == 0 ||
	    (*(int*) (inst + 0x70) != 0 &&
	     (*(unsigned char*) (*(int*) (inst + 0x70) + 0x74) & 8) != 0)) {
		table = *(char**) (obj + 0xf4);
		i = *(int*) (obj + 0xf8) + 1;
		if (*(unsigned char*) (table + i * 2) == 0 &&
		    *(unsigned char*) (table + i * 2 + 1) == 0 &&
		    i < *(int*) (obj + 0xf0)) {
			j = i;
			for (;;) {
				r = i + 0x20;
				if (r > 0x100) {
					r = 0x100;
				}
				if (j >= r) {
					if (j != i) {
						*(unsigned char*) (*(int*) (inst + 0x70) + 0x74) =
							(*(unsigned char*) (*(int*) (inst + 0x70) + 0x74) & 0xfd) | 8;
						*(unsigned char*) (*(int*) (inst + 0x70) + 0x6d) |= 0x20;
						return;
					}
					goto next;
				}
				if (*(unsigned char*) (table + j * 2) != 0 ||
				    *(unsigned char*) (table + j * 2 + 1) != 0) {
					break;
				}
				j++;
			}
			*(int*) (obj + 0xf8) = j - 1;
		}
next:
		i = *(int*) (obj + 0xf8) + 1;
		*(int*) (obj + 0xf8) = i;
		if (i >= *(int*) (obj + 0xf0)) {
			ch_FinishAni(inst);
			if (ch_SceneDebugSwitch) {
				*(unsigned char*) (*(int*) (obj + 0x14) + 0x8c) |= 8;
			}
			if (*(int*) (obj + 0xf4) != 0) {
				fcn_0041ddd0(*(char**) (obj + 0xf4));
				*(int*) (obj + 0xf4) = 0;
			}
			ch_RemoveQueueEntry(obj);
			return;
		}
		o = *(char**) (obj + 0x14);
		q = (char*) (obj + 0x124);
		d3_GridPointToWorld((char*) v, *(unsigned char*) (table + i * 2),
		             *(unsigned char*) (table + i * 2 + 1), (float*) q);
		d = d3_ComputeYawToTarget(*(char**) (o + 0x34), (float*) q);
		*(float*) (obj + 0x108) = d;
		o = *(char**) (*(int*) (obj + 0x14) + 0x34);
		a = (float) sqrt(
		    (*(float*) (o + 0x4c) - *(float*) (obj + 0x124)) *
		        (*(float*) (o + 0x4c) - *(float*) (obj + 0x124)) +
		    (*(float*) (o + 0x50) - *(float*) (obj + 0x128)) *
		        (*(float*) (o + 0x50) - *(float*) (obj + 0x128)) +
		    (*(float*) (o + 0x54) - *(float*) (obj + 0x12c)) *
		        (*(float*) (o + 0x54) - *(float*) (obj + 0x12c)));
		*(float*) (obj + 0x10c) = a;
		if (*(int*) (inst + 0x70) != 0) {
			if (*(int*) (obj + 0xf8) < *(int*) (obj + 0xf0) - 1 ||
			    *(int*) (obj + 0xf0) <= 1) {
				if (*(int*) (inst + 4) & 8) {
					f = 45.0f;
				} else if (*(int*) (inst + 4) & 0x10) {
					f = 60.0f;
				} else {
					f = 15.0f;
				}
			} else if (*(int*) (inst + 4) & 8) {
				f = 24.0f;
			} else if (*(int*) (inst + 4) & 0x10) {
				f = 45.0f;
			} else {
				f = 8.0f;
			}
			if (*(int*) (*(int*) (inst + 0x88) + 0xac) != 0) {
				f *= 3.0f;
			}
			p = *(char**) (inst + 0x70);
			*(int*) (p + 0x4c) = *(int*) (obj + 0x124);
			*(int*) (p + 0x50) = *(int*) (obj + 0x128);
			*(int*) (p + 0x54) = *(int*) (obj + 0x12c);
			*(float*) (p + 0x5c) = f;
			*(unsigned char*) (p + 0x74) |= 2;
			*(unsigned char*) (p + 0x74) &= 0xf7;
			*(unsigned char*) (p + 0x6d) &= 0xdf;
		}
	}
	if (*(float*) (obj + 0x108) < 0.0f) {
		o = *(char**) (*(int*) (obj + 0x14) + 0x34);
		d = d3_ComputeYawToTarget(o, (float*) (obj + 0x124));
		*(float*) (obj + 0x108) = d;
		if (d > 0.04 || d < -0.04) {
			t = ch_UpdateTime - ch_LastUpdateTime;
			f = t * 0.9090908765792847f;
			if (*(int*) (inst + 4) & 8) {
				f *= 0.4f;
			} else if (*(int*) (inst + 4) & 0x10) {
				f *= 1.4f;
			}
			if (fabs(d) > 2.094395160675049 && !(*(int*) (inst + 4) & 8)) {
				f *= 0.32f;
			} else if (fabs(d) > 1.5707963705062866) {
				f *= 0.19999998807907104f;
			} else if (fabs(d) > 1.0471975803375244) {
				f *= 0.14f;
			} else if (fabs(d) > 0.5235987901687622) {
				f *= 0.08f;
			} else {
				f *= 0.04f;
			}
			a = *(float*) (o + 0x88) - f;
			a = (float) fmod(a, 6.2831855f);
			if (a < 0.0) {
				a += 6.2831855f;
			}
			if (a < d + *(float*) (o + 0x88)) {
				a = d + *(float*) (o + 0x88);
			}
		} else {
			a = d + *(float*) (o + 0x88);
			*(int*) (obj + 0x108) = 0;
		}
		d3_SetObjectEulerRotation(o, *(int*) (o + 0x84), *(int*) &a, *(int*) (o + 0x8c));
	} else if (*(float*) (obj + 0x108) > 0.0f) {
		o = *(char**) (*(int*) (obj + 0x14) + 0x34);
		d = d3_ComputeYawToTarget(o, (float*) (obj + 0x124));
		*(float*) (obj + 0x108) = d;
		if (d > 0.04 || d < -0.04) {
			t = ch_UpdateTime - ch_LastUpdateTime;
			f = t * 0.9090908765792847f;
			if (*(int*) (inst + 4) & 8) {
				f *= 0.4f;
			} else if (*(int*) (inst + 4) & 0x10) {
				f *= 1.4f;
			}
			if (fabs(d) > 2.094395160675049 && !(*(int*) (inst + 4) & 8)) {
				a = *(float*) (o + 0x88) - f * 0.32f;
			} else if (fabs(d) > 1.5707963705062866) {
				a = f * 0.19999998807907104f + *(float*) (o + 0x88);
			} else if (fabs(d) > 1.0471975803375244) {
				a = f * 0.14f + *(float*) (o + 0x88);
			} else if (fabs(d) > 0.5235987901687622) {
				a = f * 0.08f + *(float*) (o + 0x88);
			} else {
				a = f * 0.04f + *(float*) (o + 0x88);
			}
			a = (float) fmod(a, 6.2831855f);
			if (a < 0.0) {
				a += 6.2831855f;
			}
			if (a > d + *(float*) (o + 0x88)) {
				a = d + *(float*) (o + 0x88);
			}
		} else {
			a = d + *(float*) (o + 0x88);
			*(int*) (obj + 0x108) = 0;
		}
		d3_SetObjectEulerRotation(o, *(int*) (o + 0x84), *(int*) &a, *(int*) (o + 0x8c));
	} else {
		o = *(char**) (*(int*) (obj + 0x14) + 0x34);
		a = (float) sqrt(
		    (*(float*) (o + 0x4c) - *(float*) (obj + 0x124)) *
		        (*(float*) (o + 0x4c) - *(float*) (obj + 0x124)) +
		    (*(float*) (o + 0x50) - *(float*) (obj + 0x128)) *
		        (*(float*) (o + 0x50) - *(float*) (obj + 0x128)) +
		    (*(float*) (o + 0x54) - *(float*) (obj + 0x12c)) *
		        (*(float*) (o + 0x54) - *(float*) (obj + 0x12c)));
		if (a > *(float*) (obj + 0x10c) * 1.2) {
			if (*(int*) (obj + 0xf8) >= *(int*) (obj + 0xf0) - 1) {
				ch_SetPosition(*(char**) (obj + 0x14), (float*) (obj + 0x124), 0);
			}
			if (*(int*) (inst + 0x70) != 0) {
				*(unsigned char*) (*(int*) (inst + 0x70) + 0x74) |= 8;
			}
			sprintf(buf,
			        "ch_WalkOnPath(): Have missed my treshhold... %s [%f %f]",
			        *(char**) (*(int*) (obj + 0x14) + 0x34),
			        *(float*) (obj + 0x124), *(float*) (obj + 0x12c));
		}
	}
	if (state == 0 || state == 0x0d || *(int*) (inst + 0x70) == 0) {
		return;
	}
	p = *(char**) (inst + 0x70);
	f = 0.7f;
	if (*(int*) (inst + 0x2c) == -1 &&
	    *(int*) (*(int*) (inst + 0x34) + 0x204) != 0) {
		f = 1.0f;
		if (*(int*) (inst + 0x124) == 0) {
			f += 0.2f;
		}
	}
	if (*(unsigned char*) (inst + 4) & 8) {
		if (state != 0x0b && state != 6) {
			*(float*) (p + 0x60) =
			    f * *(float*) (inst + 0x1a0) * *(float*) (inst + 0x1a4) * 1.7f;
			return;
		}
		*(float*) (p + 0x60) =
		    f * *(float*) (inst + 0x1a0) * *(float*) (inst + 0x1a4) * 1.9f;
	} else {
		if (state != 0x0b && state != 6) {
			*(float*) (p + 0x60) =
			    f * *(float*) (inst + 0x1a0) * *(float*) (inst + 0x1a4) * 2.2f;
			return;
		}
		*(float*) (p + 0x60) =
		    f * *(float*) (inst + 0x1a0) * *(float*) (inst + 0x1a4) * 2.5f;
	}
remove:
	if (*(int*) (obj + 0xf4) != 0) {
		fcn_0041ddd0(*(char**) (obj + 0xf4));
		*(int*) (obj + 0xf4) = 0;
	}
	ch_RemoveQueueEntry(obj);
}
