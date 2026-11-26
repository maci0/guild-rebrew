extern int g_6b7d7c;
extern volatile int g_6b7fac;

int __cdecl sb_FindSampleBank(int* a0);
int __cdecl sb_LoadEntry(int a0, int* a1);
int __cdecl fcn_0064d3f8(void);
int __cdecl msx_SetSampleData(int a0, int a1, int a2, int a3);
void __cdecl fcn_0042a920(int a0, int a1);
void __cdecl fcn_0042a9a0(int a0, int a1);
void __cdecl msx_SetSampleLoopCount(int a0, int a1);
void __cdecl msx_StartSample(int a0);

/* ADDRESS: GOLDTL 0x00423670 */
int __cdecl fcn_00423670(int* voice, int a1, int a2)
{
	int result;
	char* ent;
	int* p2;
	char* entry;
	unsigned char type;
	int v;
	int index;
	int stamp;

	result = 0;
	if (g_6b7d7c == 0) {
		return 0;
	}
	ent = (char*) voice[1];
	if (*(int*) (ent + 0x38) == 0) {
		v = sb_FindSampleBank((int*) ent);
		if (v == 0) {
			result = -1;
			goto done;
		}
		result = sb_LoadEntry(v, (int*) ent);
		if (result != 0) {
			goto done;
		}
	}
	ent = (char*) voice[1];
	type = *(unsigned char*) (ent + 0x36);
	if (type == 1) {
		entry = (char*) *(int*) (ent + 0x38);
	} else if (type == 2) {
		p2 = (int*) *(int*) (ent + 0x38);
		if ((*(unsigned char*) ((char*) voice + 0x14) & 4) != 0) {
			index = voice[8];
		} else {
			index = fcn_0064d3f8() % p2[0];
		}
		entry = (char*) p2[1] + index * 0xc;
	} else {
		result = -1;
		goto done;
	}
	type = *(unsigned char*) entry;
	if (type == 1) {
		v = 0x678fb8;
	} else if (type == 2) {
		v = 0x678fb0;
	} else {
		result = -1;
		goto done;
	}
	if (msx_SetSampleData(*voice, v, *(int*) (entry + 8), *(int*) (entry + 4)) == -1) {
		result = -1;
		goto done;
	}
	if (a1 != 0) {
		voice[4] = (g_6b7fac * 2 + g_6b7fac) * 4
			+ g_6b7fac;
		voice[5] |= 1;
		fcn_0042a920(*voice, 0);
	} else {
		fcn_0042a920(*voice, voice[9]);
	}
	fcn_0042a9a0(*voice, voice[10]);
	if ((*(unsigned char*) ((char*) voice + 0x14) & 4) == 0 && a2 != 0) {
		msx_SetSampleLoopCount(*voice, 1);
		voice[7] = 0;
		voice[6] = a2;
	} else {
		msx_SetSampleLoopCount(*voice, voice[3]);
		voice[6] = 0;
	}
	stamp = (g_6b7fac * 2 + g_6b7fac) * 4
		+ g_6b7fac;
	((int*) voice[1])[0xf] = voice[2] = stamp;
	voice[5] &= ~8;
	msx_StartSample(*voice);
done:
	return result;
}
