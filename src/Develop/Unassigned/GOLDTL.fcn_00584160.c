extern int g_774a14;
extern char* g_665f08;
extern int g_774650;
extern unsigned int g_6b7fac;

void __cdecl fcn_0046f4c0(int);
int __cdecl fcn_00472170(int, int);
int __cdecl fcn_00469c30(int, int, int);
void __cdecl fcn_00469c40(int, int, int);
int __cdecl fcn_0046b2b0(int);

void __cdecl fcn_005840d0(float*, float*, float*, float*, float, float*);

/* ADDRESS: GOLDTL 0x00584160 */
void __cdecl fcn_00584160(int a0)
{
	char* o;
	char* hdr;
	char* frame;
	int v;
	int handle;
	int selection;
	float point[2];

	if (!g_774a14) {
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

	v = a0;
	if (*(int*) (hdr + 0x60) != 0) {
		selection = (*(int (__cdecl*)(int)) (hdr + 0x60))(a0);
		o = g_665f08;
		if (selection > -1) {
			if (selection >= 0 && selection < *(int*) (*(char**) (o + 0x18) + 0x5c) && selection != *(int*) (o + 0x54)) {
				*(int*) (o + 0x58) = 2;
				*(unsigned int*) (g_665f08 + 0x5c) = g_6b7fac;
				*(int*) (g_665f08 + 0x54) = selection;
			}
		} else {
			v = 2;
		}
	}

	o = g_665f08;
	handle = *(int*) (o + 0x60);
	if (handle != -1) {
		fcn_0046f4c0(handle);
		o = g_665f08;
		if (*(int*) (o + 0x64) != g_774650) {
			fcn_00472170(*(int*) (o + 0x60), 0);
		} else {
			fcn_00472170(*(int*) (o + 0x60), 1);
		}
		o = g_665f08;
	}

	if (v == 0) {
		*(int*) (o + 0x64) = g_774650;
		o = g_665f08;
		*(unsigned int*) (o + 0x5c) = g_6b7fac;
		o = g_665f08;
		*(int*) (o + 0x58) = 2;
		o = g_665f08;
		if (*(int*) (o + 0x60) == -1) {
			frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
			*(int*) (g_665f08 + 0x60) = fcn_00469c30((short) *(float*) frame, (short) *(float*) (frame + 4), 0x1d); o = g_665f08;
		}
		frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
		fcn_00469c40((short) *(float*) frame, (short) *(float*) (frame + 4), *(int*) (o + 0x60));
		return;
	}

	if (v != 1) {
		if (v == 2) {
			handle = *(int*) (o + 0x60);
			if (handle != -1) {
				fcn_0046b2b0(handle);
				o = g_665f08;
			}
			*(int*) (o + 0x60) = -1;
			*(int*) (g_665f08 + 0x58) = 1;
		}
		return;
	}

	o = g_665f08;
	if (*(int*) (o + 0x58) == 2) {
		frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
		if ((double) g_6b7fac < (double) *(unsigned int*) (o + 0x5c) + *(float*) (frame + 0x20)) {
			return;
		}
		*(int*) (o + 0x58) = 3;
		*(unsigned int*) (g_665f08 + 0x5c) = g_6b7fac;
		o = g_665f08;
	}
	if (*(int*) (o + 0x58) == 3) {
		frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
		
		if ((double) g_6b7fac < (double) *(unsigned int*) (o + 0x5c) + *(float*) (frame + 0x24)) {
			point[0] = (float) ((double) (unsigned int) (g_6b7fac - *(unsigned int*) (o + 0x5c)) / *(float*) (frame + 0x24));
			fcn_005840d0((float*) frame, (float*) (frame + 8), (float*) (frame + 0x10), (float*) (frame + 0x18), point[0], point);
			fcn_00469c40((short) point[0], (short) point[1], *(int*) (o + 0x60));
			return;
		}
		*(int*) (o + 0x58) = 4;
		*(unsigned int*) (g_665f08 + 0x5c) = g_6b7fac;
		o = g_665f08; frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
		fcn_00469c40((short) *(float*) (frame + 0x18), (short) *(float*) (frame + 0x1c), *(int*) (o + 0x60));
		o = g_665f08;
	}
	if (*(int*) (o + 0x58) == 4) {
		frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
		if (!((double) g_6b7fac < (double) *(unsigned int*) (o + 0x5c) + *(float*) (frame + 0x28))) {
			*(int*) (o + 0x58) = 2;
			*(unsigned int*) (g_665f08 + 0x5c) = g_6b7fac;
			o = g_665f08; frame = *(char**) (*(char**) (o + 0x18) + 0x64) + *(int*) (o + 0x54) * 0x2c;
			fcn_00469c40((short) *(float*) frame, (short) *(float*) (frame + 4), *(int*) (o + 0x60));
			return;
		}
	}
}
