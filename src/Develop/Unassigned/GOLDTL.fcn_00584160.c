extern int d2_TutorialActive;
extern char* g_665f08;
extern int g_774650;
extern volatile unsigned int g_6b7fac;

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
	o = g_665f08;
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
			o = g_665f08;
			if (selection <= -1) {
				a0 = 2;
			} else if (selection >= 0 && selection < *(int*) (*(char**) (o + 0x18) + 0x5c) && selection != *(int*) (o + 0x54)) {
				*(int*) (o + 0x58) = 2;
				*(unsigned int*) (g_665f08 + 0x5c) = g_6b7fac;
				*(int*) (g_665f08 + 0x54) = selection;
				o = g_665f08;
			}
		}
	}

	o = g_665f08;
	handle = *(int*) (o + 0x60);
	if (handle != -1) {
		d2_ReorderControlStack(handle);
		o = g_665f08;
		if (*(int*) (o + 0x64) != g_774650) {
			d2_SetSlotVisibility(*(int*) (o + 0x60), 0);
		} else {
			d2_SetSlotVisibility(*(int*) (o + 0x60), 1);
		}
		o = g_665f08;
	}

	if (a0 == 0) {
		*(int*) (o + 0x64) = g_774650;
		*(unsigned int*) (g_665f08 + 0x5c) = g_6b7fac;
		*(int*) (g_665f08 + 0x58) = 2;
		o = g_665f08;
		if (*(int*) (o + 0x60) == -1) {
			frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
			*(int*) (g_665f08 + 0x60) = d2_CreateElement((short) *(float*) frame, (short) *(float*) (frame + 4), 0x1d); o = g_665f08;
		}
		frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
		d2_PositionControl((short) *(float*) frame, (short) *(float*) (frame + 4), *(int*) (o + 0x60));
		return;
	}

	if (a0 == 1) {
		if (*(int*) (o + 0x58) == 2) {
			if ((float) *(unsigned int*) (o + 0x5c) + *(float*) (*(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c + 0x20) > (float) g_6b7fac) {
				return;
			}
			*(int*) (o + 0x58) = 3;
			*(unsigned int*) (g_665f08 + 0x5c) = g_6b7fac;
			o = g_665f08;
		}
		if (*(int*) (o + 0x58) == 3) {
			frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
			if ((float) *(unsigned int*) (o + 0x5c) + *(float*) (frame + 0x24) > (float) g_6b7fac) {
				float point[2];
				float f;
				f = (float) ((double) (unsigned int) (g_6b7fac - *(unsigned int*) (o + 0x5c)) / *(float*) (frame + 0x24));
				d2_EvalCubicBezier2D((float*) frame, (float*) (frame + 8), (float*) (frame + 0x10), (float*) (frame + 0x18), f, point);
				d2_PositionControl((short) point[0], (short) point[1], *(int*) (o + 0x60));
				return;
			}
			*(int*) (o + 0x58) = 4;
			*(unsigned int*) (g_665f08 + 0x5c) = g_6b7fac;
			frame = *(char**) (*(char**) (g_665f08 + 0x18) + 0x64) + *(int*) (g_665f08 + 0x54) * 0x2c;
			d2_PositionControl((short) *(float*) (frame + 0x18), (short) *(float*) (frame + 0x1c), *(int*) (g_665f08 + 0x60));
			o = g_665f08;
		}
		if (*(int*) (o + 0x58) == 4) {
			if ((float) *(unsigned int*) (o + 0x5c) + *(float*) (*(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c + 0x28) > (float) g_6b7fac) {
				return;
			}
			*(int*) (o + 0x58) = 2;
			*(unsigned int*) (g_665f08 + 0x5c) = g_6b7fac;
			frame = *(char**) (*(char**) (g_665f08 + 0x18) + 0x64) + *(int*) (g_665f08 + 0x54) * 0x2c;
			d2_PositionControl((short) *(float*) frame, (short) *(float*) (frame + 4), *(int*) (g_665f08 + 0x60));
			return;
		}
	} else if (a0 == 2) {
		handle = *(int*) (o + 0x60);
		if (handle != -1) {
			d2_DestroyElement(handle);
			o = g_665f08;
		}
		*(int*) (o + 0x60) = -1;
		*(int*) (g_665f08 + 0x58) = 1;
	}
}
