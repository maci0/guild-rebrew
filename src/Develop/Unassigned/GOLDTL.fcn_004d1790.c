extern int g_14ce8d4;
extern int d3_SelectionBoxActive;
extern int g_14ce8e4;
extern int g_6772c4;
extern int d2_CurrentElementId;
extern int g_14ce8cc;
extern int g_14ce8e0;
extern char* ch_ContextCharacters[32];
extern unsigned short* g_772f24;
extern unsigned short* g_772e9c;
extern int g_772ee4;
extern int g_772ee8;
extern char g_68b844[];

void __cdecl fcn_005345a0(void);
void __cdecl d3_BeginSelectionBox(void);
int __cdecl gm_GetEntityControlMask(int, char*);
char __cdecl fcn_004d15c0(int, char*);
int __cdecl d3snd_PlaySoundEffect(int, int, int, int);
void __cdecl fcn_00414c30(int, int);
void __cdecl fcn_004d1910(void);

/* ADDRESS: GOLDTL 0x004d1790 */
void __cdecl fcn_004d1790(int a0)
{
	char** q;
	char* o;
	char* p;

	if (g_14ce8d4 == 0) {
		if (d3_SelectionBoxActive != 0)
			fcn_005345a0();
	}
	if (g_14ce8d4 != 0 && g_14ce8e4 == 0) {
		if (d3_SelectionBoxActive == 0 && g_6772c4 != 0 && d2_CurrentElementId == -1) {
			fcn_004d1910();
			d3_BeginSelectionBox();
		}
	} else {
		if (g_14ce8cc != 0) {
			for (q = ch_ContextCharacters; (int) q < (int) (ch_ContextCharacters + 32); q++) {
				o = *q;
				if (o == 0)
					continue;
				if (*(char*) (o + 0x188) == 0)
					continue;
				if ((gm_GetEntityControlMask(*g_772f24, o) & 0x800) == 0)
					continue;
				if (*(int*) (o + 0x184) == 0)
					continue;
				if (*(char*) (o + 8) == 0)
					continue;
				if (!fcn_004d15c0(a0, o))
					continue;
				if (g_772f24 == g_772e9c)
					d3snd_PlaySoundEffect(*(unsigned short*) o, g_772ee4, (int) g_68b844, -1);
				else
					d3snd_PlaySoundEffect(*(unsigned short*) o, g_772ee8, (int) g_68b844, -1);
				*(char*) (o + 0x188) = 0;
			}
		}
	}
	for (q = ch_ContextCharacters; (int) q < (int) (ch_ContextCharacters + 32); q++) {
		o = *q;
		if (o == 0)
			continue;
		if (*(char*) (*(int*) (o + 0x184) + 0x8c) & 0x40)
			continue;
		p = (char*) *(int*) (*(int*) (o + 0x184) + 0x34);
		if (*(char*) (o + 0x188)) {
			if ((*(unsigned char*) (p + 0x215) & 0x80) == 0)
				fcn_00414c30((int) p, 1);
		} else {
			if ((*(unsigned char*) (p + 0x215) & 0x80) == 0x80)
				fcn_00414c30((int) p, 0);
		}
	}
	if (g_14ce8e0 != 0)
		fcn_004d1910();
}
