extern char* g_772eb4;
extern int g_772e9c;
extern int g_772e98;
extern int g_772f08;
extern int g_9b9e40[];
extern int g_9b43e0[];
extern float g_662e64;
extern float g_664144;
extern float g_662a6c;
extern float g_6628cc;

char* __cdecl fcn_004cef30(int);
float __cdecl fcn_004ce8b0(char*);
int __cdecl fcn_0064d470(char*, void*);
void __cdecl fcn_00455350(char*, char*, float*);

/* ADDRESS: GOLDTL 0x004d3c60 */
int __cdecl fcn_004d3c60(int id)
{
	char* e;
	unsigned char flags;
	float sum_lo;
	float sum_hi;
	float ratio;
	float pos[4];
	int mode;
	int band;
	int i;
	int cnt;
	int ent;

	flags = *(unsigned char*) (g_772eb4 + 0x7c);
	mode = 6;
	if ((flags & 1) != 0 && g_772e9c == id) {
		mode = 0;
	} else if ((flags & 1) != 0 && g_772e98 == id) {
		mode = 1;
	} else if ((flags & 2) != 0 && g_772e9c == id) {
		mode = 2;
	} else if ((flags & 2) != 0 && g_772e98 == id) {
		mode = 3;
	} else if ((flags & 4) != 0 && g_772e9c == id) {
		mode = 4;
	} else if ((flags & 4) != 0 && g_772e98 == id) {
		mode = 5;
	}
	sum_lo = 0.0f;
	for (i = 0x80; i < 0xc0; i += 4) {
		ent = *(int*) (g_772eb4 + i);
		if (ent != -1) {
			e = fcn_004cef30(ent);
			if (e[8] != 0 && e[8] != 4) {
				sum_lo = (float) (fcn_004ce8b0(e) + sum_lo);
			}
		}
	}
	sum_hi = 0.0f;
	for (i = 0xc0; i < 0x100; i += 4) {
		ent = *(int*) (g_772eb4 + i);
		if (ent != -1) {
			e = fcn_004cef30(ent);
			if (e[8] != 0 && e[8] != 4) {
				sum_hi = (float) (fcn_004ce8b0(e) + sum_hi);
			}
		}
	}
	cnt = 0;
	for (i = 0; i < g_772f08; i++) {
		if (fcn_0064d470((char*) *(int*) ((char*) g_9b9e40 + i * 4), "sp_CONQUER")) {
			ent = *(int*) ((char*) g_9b9e40 + i * 4);
			fcn_00455350((char*) ent, (char*) (ent + 0x4c), pos);
			ent = *(int*) (*(int*) ((char*) g_9b9e40 + i * 4) + 0x204);
			if (ent != 0 && *(int*) (ent + 0x16c) == g_772e9c) {
				cnt++;
			}
		}
	}
	if (id == g_772e9c) {
		ratio = sum_hi / sum_lo;
	} else {
		ratio = sum_lo / sum_hi;
	}
	if (ratio >= g_662e64) {
		band = 4;
	} else if (ratio >= g_664144) {
		band = 3;
	} else if (ratio >= g_662a6c) {
		band = 2;
	} else if (ratio >= g_6628cc) {
		band = 1;
	} else {
		band = 0;
	}
	if (id == g_772e98) {
		if (cnt == 1) {
			band = cnt;
		} else {
			if (cnt == 2 || cnt == 3) {
				band = 0;
			}
		}
	}
	return (band + mode * 5) * 0x18 + (int) g_9b43e0;
}
