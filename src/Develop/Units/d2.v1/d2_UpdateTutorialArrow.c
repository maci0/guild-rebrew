extern int d2_TutorialActive;
extern char* d2_TutorialState;
extern int g_774650;
extern volatile unsigned int gm_GameTicks;

void __cdecl d2_ReorderControlStack(int);
int __cdecl d2_SetSlotVisibility(int, int);
int __cdecl d2_CreateElement(int, int, int);
void __cdecl d2_PositionControl(int, int, int);
int __cdecl d2_DestroyElement(int);

void __cdecl d2_EvalCubicBezier2D(float*, float*, float*, float*, float, float*);

/* ADDRESS: GOLDTL 0x00584160 */
void __cdecl d2_UpdateTutorialArrow(int a0)
{
	char* o;
	char* hdr;
	char* frame;
	int handle;

	if (!d2_TutorialActive) {
		return;
	}
	o = d2_TutorialState;
	hdr = *(char**) (o + 0x18);
	if (*(int*) (hdr + 0x64) == 0) {
		return;
	}
	if (*(int*) (hdr + 0x5c) < 1) {
		return;
	}

	{
		int (__cdecl* cb)(int);
		cb = *(int (__cdecl**)(int)) (hdr + 0x60);
		if (cb != 0) {
			int selection;
			selection = cb(a0);
			o = d2_TutorialState;
			if (selection <= -1) {
				a0 = 2;
			} else if (selection >= 0 && selection < *(int*) (*(char**) (o + 0x18) + 0x5c) && selection != *(int*) (o + 0x54)) {
				*(int*) (o + 0x58) = 2;
				*(unsigned int*) (d2_TutorialState + 0x5c) = gm_GameTicks;
				*(int*) (d2_TutorialState + 0x54) = selection;
				o = d2_TutorialState;
			}
		}
	}

	o = d2_TutorialState;
	handle = *(int*) (o + 0x60);
	if (handle != -1) {
		d2_ReorderControlStack(handle);
		o = d2_TutorialState;
		if (*(int*) (o + 0x64) != g_774650) {
			d2_SetSlotVisibility(*(int*) (o + 0x60), 0);
		} else {
			d2_SetSlotVisibility(*(int*) (o + 0x60), 1);
		}
		o = d2_TutorialState;
	}

	if (a0 == 0) {
		*(int*) (o + 0x64) = g_774650;
		*(unsigned int*) (d2_TutorialState + 0x5c) = gm_GameTicks;
		*(int*) (d2_TutorialState + 0x58) = 2;
		o = d2_TutorialState;
		if (*(int*) (o + 0x60) == -1) {
			frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
			*(int*) (d2_TutorialState + 0x60) = d2_CreateElement((short) *(float*) frame, (short) *(float*) (frame + 4), 0x1d); o = d2_TutorialState;
		}
		frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
		d2_PositionControl((short) *(float*) frame, (short) *(float*) (frame + 4), *(int*) (o + 0x60));
		return;
	}

	if (a0 == 1) {
		if (*(int*) (o + 0x58) == 2) {
			if ((float) *(unsigned int*) (o + 0x5c) + *(float*) (*(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c + 0x20) > (float) gm_GameTicks) {
				return;
			}
			*(int*) (o + 0x58) = 3;
			*(unsigned int*) (d2_TutorialState + 0x5c) = gm_GameTicks;
			o = d2_TutorialState;
		}
		if (*(int*) (o + 0x58) == 3) {
			frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
			if ((float) *(unsigned int*) (o + 0x5c) + *(float*) (frame + 0x24) > (float) gm_GameTicks) {
				float point[2];
				float f;
				f = (float) ((double) (unsigned int) (gm_GameTicks - *(unsigned int*) (o + 0x5c)) / *(float*) (frame + 0x24));
				d2_EvalCubicBezier2D((float*) frame, (float*) (frame + 8), (float*) (frame + 0x10), (float*) (frame + 0x18), f, point);
				d2_PositionControl((short) point[0], (short) point[1], *(int*) (o + 0x60));
				return;
			}
			*(int*) (o + 0x58) = 4;
			*(unsigned int*) (d2_TutorialState + 0x5c) = gm_GameTicks;
			frame = *(char**) (*(char**) (d2_TutorialState + 0x18) + 0x64) + *(int*) (d2_TutorialState + 0x54) * 0x2c;
			d2_PositionControl((short) *(float*) (frame + 0x18), (short) *(float*) (frame + 0x1c), *(int*) (d2_TutorialState + 0x60));
			o = d2_TutorialState;
		}
		if (*(int*) (o + 0x58) == 4) {
			if ((float) *(unsigned int*) (o + 0x5c) + *(float*) (*(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c + 0x28) > (float) gm_GameTicks) {
				return;
			}
			*(int*) (o + 0x58) = 2;
			*(unsigned int*) (d2_TutorialState + 0x5c) = gm_GameTicks;
			frame = *(char**) (*(char**) (d2_TutorialState + 0x18) + 0x64) + *(int*) (d2_TutorialState + 0x54) * 0x2c;
			d2_PositionControl((short) *(float*) frame, (short) *(float*) (frame + 4), *(int*) (d2_TutorialState + 0x60));
			return;
		}
	} else if (a0 == 2) {
		handle = *(int*) (o + 0x60);
		if (handle != -1) {
			d2_DestroyElement(handle);
			o = d2_TutorialState;
		}
		*(int*) (o + 0x60) = -1;
		*(int*) (d2_TutorialState + 0x58) = 1;
	}
}
