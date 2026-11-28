extern int g_14ce8d4;
extern int d3_SelectionBoxActive;
extern int g_14ce8e4;
extern int g_6772c4;
extern int d2_CurrentElementId;
extern int g_14ce8cc;
extern int io_RightButtonReleased;
extern char* ch_ContextCharacters[32];
extern unsigned short* cut_ActivePlayerEntity;
extern unsigned short* cut_CombatDefenderEntity;
extern int g_772ee4;
extern int g_772ee8;
extern char g_68b844[];

void __cdecl d3_ClearSelectionBox(void);
void __cdecl d3_BeginSelectionBox(void);
int __cdecl gm_GetEntityControlMask(int, char*);
char __cdecl cut_DispatchTacticalOrder(int, char*);
int __cdecl d3snd_PlaySoundEffect(int, int, int, int);
void __cdecl d3_SetObjectGreyTint(int, int);
void __cdecl cut_ClearStatusOverlaySlots(void);

/* ADDRESS: GOLDTL 0x004d1790 */
/* ADDRESS: GOLDDE 0x004bea80 */
void __cdecl cut_UpdateCombatSelectionBox(int a0)
{
	char** q;
	char* o;
	char* p;

	if (g_14ce8d4 == 0) {
		if (d3_SelectionBoxActive != 0)
			d3_ClearSelectionBox();
	}
	if (g_14ce8d4 != 0 && g_14ce8e4 == 0) {
		if (d3_SelectionBoxActive == 0 && g_6772c4 != 0 && d2_CurrentElementId == -1) {
			cut_ClearStatusOverlaySlots();
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
				if ((gm_GetEntityControlMask(*cut_ActivePlayerEntity, o) & 0x800) == 0)
					continue;
				if (*(int*) (o + 0x184) == 0)
					continue;
				if (*(char*) (o + 8) == 0)
					continue;
				if (!cut_DispatchTacticalOrder(a0, o))
					continue;
				if (cut_ActivePlayerEntity == cut_CombatDefenderEntity)
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
				d3_SetObjectGreyTint((int) p, 1);
		} else {
			if ((*(unsigned char*) (p + 0x215) & 0x80) == 0x80)
				d3_SetObjectGreyTint((int) p, 0);
		}
	}
	if (io_RightButtonReleased != 0)
		cut_ClearStatusOverlaySlots();
}
