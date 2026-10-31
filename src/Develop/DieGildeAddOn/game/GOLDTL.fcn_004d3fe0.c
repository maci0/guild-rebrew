extern char* g_772eb4;
extern unsigned short* g_772e9c;
extern char g_9b0e20[];
extern double g_662ad8;

float* __cdecl fcn_004d3c60(char*);
char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
float __cdecl fcn_004d3e90(void*, unsigned int);
float __cdecl fcn_004e6d20(void);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004d4250(char*, char*);

/* ADDRESS: GOLDTL 0x004d3fe0 */
void __cdecl fcn_004d3fe0(char* a0)
{
	char* rec;
	char* base;
	char* e;
	float* w;
	float best;
	float rnd;
	int n;
	float f;
	char* ent[16];
	int i;
	int k;
	int auswahl;
	int chosen;

	auswahl = 0;
	n = 0;
	chosen = 0;
	rec = 0;
	w = fcn_004d3c60(a0);
	for (i = 0; i < ((unsigned char*) g_772eb4)[0x30]; i++) {
		if (*(int*) (g_772eb4 + 0x34 + i * 4) == *(int*) (a0 + 4)) {
			rec = g_9b0e20 + i * 0x35c;
			break;
		}
	}
	if (a0 == (char*) g_772e9c) {
		base = g_772eb4 + 0xc0;
	} else {
		base = g_772eb4 + 0x80;
	}
	for (i = 0; i < 16; i++) {
		if (*(int*) (base + i * 4) != -1) {
			ent[i] = gm_LookupEntityRecordIn32SlotTable(*(int*) (base + i * 4));
			n++;
		} else {
			ent[i] = 0;
		}
	}
	if (n > 0) {
		k = n;
		do {
			rnd = gm_RandomFloat01();
			for (i = 0; i < 6; i++) {
				if (rnd <= w[i]) {
					break;
				}
			}
			if (i < 6) {
				auswahl = i;
			}
			best = -1.0f;
			for (i = 0; i < 16; i++) {
				if (ent[i] != 0) {
					f = fcn_004d3e90(ent[i], auswahl);
					if (f > best) {
						best = f;
						chosen = i;
					}
				}
			}
			e = ent[chosen];
			if (e[0x1c4] == 0 || fcn_004e6d20() > g_662ad8) {
				e[0x1c4] = (char) auswahl;
				ent[chosen] = 0;
			}
			k--;
		} while (k != 0);
	}
	for (i = 0; i < 16; i++) {
		if (*(int*) (base + i * 4) != -1) {
			fcn_004d4250(rec, gm_LookupEntityRecordIn32SlotTable(*(int*) (base + i * 4)));
		}
	}
}
